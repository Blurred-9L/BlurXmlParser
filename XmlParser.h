/**
 *  @file   XmlParser.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_PARSER_H
#define XML_PARSER_XML_PARSER_H

#include <vector>
using std::vector;

class Tokenizer;
class Token;
class TagNode;
class AttrNode;

/**
 *  @class  XmlParser
 *
 *  @brief  The XmlParser class is used to transform the plain-text xml data
 *          into a tree representation.
 */
class XmlParser {
private:
    /// The tokenizer to use
    Tokenizer * tokenizer_;
    /// The tokens found when parsing
    vector<Token *> tokens;
    /// The current token's index
    int curIndex;
    
public:
    /// Constructor
    explicit XmlParser(Tokenizer * tokenizer);
    /// Destructor
    ~XmlParser();
    /// Gets tokenizer
    const Tokenizer & tokenizer() const;
    /// Gets tokenizer
    Tokenizer & tokenizer();
    /// Sets tokenizer
    void setTokenizer(Tokenizer * tokenizer);
    /// Parses input file
    TagNode * parse();
    
private:
    /// Gets the children of the XmlNode
    bool getAllChildren(TagNode * root);
    /// Gets next token and check if type matches
    bool check(int tokenType);
    /// Tries to match a tag, closing tag or void tag
    TagNode * matchTag();
    /// Tries to match a list of attributes
    AttrNode * matchAttrList();
    /// Tries to match an attribute
    AttrNode * matchAttr();
};

#endif /// NOT XML_PARSER_XML_PARSER_H
