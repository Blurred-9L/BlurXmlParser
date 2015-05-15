/**
 *  @file   XmlParser.cpp
 *  @author Blurred-9L
 */

#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <iostream>
using std::cout;
using std::endl;

#include "BlurParser/Tokenizer/Tokenizer.h"
#include "BlurParser/Core/Token.h"

#include "XmlParser.h"
#include "XmlAutomata.h"
#include "TagNode.h"
#include "AttrNode.h"
#include "ContentData.h"
#include "XmlSyntaxError.h"
#include "XmlNestingError.h"
#include "XmlOutOfTokens.h"

/**
 *  @details    Constructs an XmlParser object.
 *
 *  @param[in]  tokenizer           The Tokenizer object to use.
 */
XmlParser::XmlParser(Tokenizer * tokenizer) : tokenizer_(tokenizer),
    curIndex(-1)
{
}

/**
 *  @details    Releases resources used by the XmlParser object.
 */
XmlParser::~XmlParser()
{
    if (tokenizer_ != 0) {
        delete tokenizer_;
    }
}

/**
 *  @details    Get-method for the tokenizer member.
 *
 *  @return     A reference to the tokenizer member.
 */
const Tokenizer & XmlParser::tokenizer() const
{
    return *tokenizer_;
}

/**
 *  @details    Get-method for the tokenizer member.
 *
 *  @return     A reference to the tokenizer member.
 */
Tokenizer & XmlParser::tokenizer()
{
    return *tokenizer_;
}

/**
 *  @details    Set-method for the tokenizer member.
 *
 *  @param[in]  tokenizer           The new tokenizer object to use.
 */
void XmlParser::setTokenizer(Tokenizer * tokenizer)
{
    if (tokenizer != 0) {
        if (tokenizer_ != 0) {
            delete tokenizer_;
        }
        tokenizer_ = tokenizer;
    }
}

/**
 *  @details    Parses the plain text of an xml file. This means tokenizing the
 *              input and then trying to match necessary tags and tag attributes
 *              if there are any.
 *              There are 3 possible errors that can happen during the parsing, which are
 *              syntax errors, nesting errors and out-of-tokens errors. The first two usually
 *              mean that the XmlParser cannot properly parse the current structure of the
 *              xml text because it was misconstructed or uses xml features not yet supported
 *              by this parser. Out-of-tokens errors usually happen due to an error during the
 *              tokenizing, though they can also happen if the xml was not completed, for instance
 *              forgetting to close the root tag. If you get an out-of-tokens error and you have
 *              a correct xml, the most likely reason is that a character symbol could not be
 *              properly identified by the tokenizer.
 *
 *  @return     A pointer to the root of the xml tree or 0 if there was any error.
 */
TagNode * XmlParser::parse()
{
    TagNode * root = 0;
    Token * curToken;
    bool ok, exceptionCaught = false;
    int size;
    
    curToken = tokenizer_->getToken();
    while (curToken != 0) {
        tokens.push_back(curToken);
        curToken = tokenizer_->getToken();
    }
    curIndex = 0;
    size = tokens.size();
    cout << "Number of tokens: " << size << endl;
    
    try {
        root = matchTag();
        ok = getAllChildren(root);
        if (!ok) throw XmlOutOfTokens();
    } catch (XmlSyntaxError & error) {
        cout << error.what() << endl;
        cout << "Last token: " << tokens[curIndex]->symbol() << endl;
        exceptionCaught = true;
    } catch (XmlNestingError & error) {
        cout << error.what() << endl;
        exceptionCaught = true;
    } catch (XmlOutOfTokens & error) {
        cout << error.what() << endl;
        exceptionCaught = true;
    }
    if (exceptionCaught) {
        if (root != 0) {
            delete root;
            root = 0;
        }
    }
    
    for (int i = 0; i < size; i++) {
        delete tokens[i];
    }
    tokens.clear();
    
    return root;
}

/////////////
// Private //
/////////////

/**
 *  @details    Consumes tokens in order to find all the children of the given node.
 *              This is a recursive method, getting called every time a new node
 *              is found. It stops once the closing tag for a node has been found or
 *              if an error has occurred, for example, running out of tokens or finding
 *              an improperly nested tag.
 *
 *  @param[in,out]  root            The current node being processed.
 *
 *  @return     A boolean value indicating if all children could be properly found.
 *
 *  @throw      XmlOutofTokens
 *  @throw      XmlNestingError
 *  @throw      XmlSyntaxError
 */
bool XmlParser::getAllChildren(TagNode * root)
{
    TagNode * nextNode;
    int size = tokens.size();
    int start_line, start_index, end_line, end_index;
    bool done = false;
    bool ok;
    
    start_line = tokens[curIndex - 1]->lineNumber();
    start_index = tokens[curIndex - 1]->start() + 1;
    cout << "Current node: " << root->name() << " " << start_line << " " << start_index << endl;
    while (curIndex < size && !done) {
        while (curIndex < size && tokens[curIndex]->type() != XmlAutomata::LT_TOK) {
            curIndex++;
        }
        nextNode = matchTag();
        cout << "\tFound node: " << nextNode->name() << " " << nextNode->isCloseTag()
             << " " << nextNode->isVoid() << endl;
        if (!nextNode->isCloseTag()) {
            root->addChild(nextNode);
            if (!nextNode->isVoid()) {
                ok = getAllChildren(nextNode);
                if (!ok) throw XmlOutOfTokens();
            }
        } else if (nextNode->name() == root->name()) {
            done = true;
            end_line = tokens[curIndex - 4]->lineNumber();
            end_index = tokens[curIndex - 4]->start();
            root->setContentData(ContentData(start_line, start_index, end_line, end_index));
            delete nextNode;
        } else {
            delete nextNode;
            throw XmlNestingError();
        }
    }
    cout << "Exiting: " << root->name() << " " << done << endl;
    
    return done;
}

/**
 *  @details    Checks that the current token matches the given token type.
 *              If this is true, then the current-token pointer is moved ahead.
 *
 *  @param[in]  tokenType           The type of the token to check for.
 *
 *  @return     A boolean value indicating if the operation was successful.
 */
bool XmlParser::check(int tokenType)
{
    int size = tokens.size();
    bool ok = false;
    
    if (curIndex < size && tokens[curIndex]->type() == tokenType) {
        ok = true;
        curIndex++;
    }
    
    return ok;
}

/**
 *  @details    Consumes tokens in order to try to match an XML tag.
 *              The possible tags to be matched are an open tag, a closing tag
 *              and a void tag. If at any moment, the current token does not match
 *              the expected token, a syntax error is raised and the parsing stops.
 *              If the operation is successful, a TagNode object is instantiated.
 *
 *  @return     The TagNode of the matching tag.
 *
 *  @throw      XmlSyntaxError
 */
TagNode * XmlParser::matchTag()
{
    TagNode * tag = 0;
    AttrNode * attrs = 0;
    string name;
    bool isVoid = false;
    bool isClosing = false;
    
    if (!check(XmlAutomata::LT_TOK)) {
        throw XmlSyntaxError();
    }
    if (tokens[curIndex]->type() == XmlAutomata::SLASH_TOK) {
        curIndex++;
        isClosing = true;
    }
    if (!check(XmlAutomata::NAME_TOK)) {
        throw XmlSyntaxError();
    }
    name = tokens[curIndex - 1]->symbol();
    if (!isClosing) {
        attrs = matchAttrList();
        if (tokens[curIndex]->type() == XmlAutomata::SLASH_TOK) {
            curIndex++;
            isVoid = true;
        }
        if (!check(XmlAutomata::GT_TOK)) {
            delete attrs;
            throw XmlSyntaxError();
        }
    } else if (!check(XmlAutomata::GT_TOK)) {
        throw XmlSyntaxError();
    }
    tag = new TagNode(name, attrs, isVoid, isClosing);
    
    return tag;
}

/**
 *  @details    Consumes tokens to try to match the attribute list inside a tag.
 *              As with tags, this method can also raise a syntax error, however,
 *              it can only be raised if the current token matches the start of an
 *              attribute and the method to match a single attribute is called.
 *              If the tag has no attributes, nothing happens.
 *              The matching performed by this function is recursive, as such, the
 *              AttrNode object returned at the end is a linked list of attributes.
 *
 *  @return     A pointer to an AttrNode or 0 if no further attributes were found.
 *
 *  @throw      XmlSyntaxError
 */
AttrNode * XmlParser::matchAttrList()
{
    AttrNode * attr = 0;

    if (tokens[curIndex]->type() == XmlAutomata::NAME_TOK) {
        attr = matchAttr();
        if (attr != 0) {
            attr->setNext(matchAttrList());
        }
    }
    
    return attr;
}

/**
 *  @details    Consumes tokens to try to match a single attribute inside a tag.
 *
 *  @return     The AttrNode with the information on the attribute.
 *
 *  @throw      XmlSyntaxError
 */
AttrNode * XmlParser::matchAttr()
{
    AttrNode * attr = 0;
    string name, value;
    
    if (!check(XmlAutomata::NAME_TOK)) {
        throw XmlSyntaxError();
    }
    name = tokens[curIndex - 1]->symbol();
    if (!check(XmlAutomata::EQ_TOK)) {
        throw XmlSyntaxError();
    }
    if (!check(XmlAutomata::STR_TOK)) {
        throw XmlSyntaxError();
    }
    value = tokens[curIndex - 1]->symbol();
    attr = new AttrNode(name, value);
    
    return attr;
}
