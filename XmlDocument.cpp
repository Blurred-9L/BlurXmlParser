/**
 *  @file   XmlDocument.cpp
 *  @author Blurred-9L
 */

#include "BlurParser/Tokenizer/Tokenizer.h"
#include "BlurParser/Tokenizer/KeywordSet.h"
#include "BlurParser/Core/LineFileReader.h"

#include "XmlDocument.h"
#include "TagNode.h"
#include "XmlAutomata.h"
#include "XmlObject.h"

#define MATRIX_FILE "Resources/matrix.csv"

/**
 *  @details    Constructs an XmlDocument. This method is private in order to force the
 *              user to use the static XmlDocument::open(). This way, if the xml file
 *              can't be opened or if an error occurs during parsing, the XmlDocument
 *              object is not left in an invalid state.
 *
 *  @param[in]  filename            A c-style string, the path to the xml file to open.
 */
XmlDocument::XmlDocument(const char * filename) :
    parser_(new Tokenizer(new XmlAutomata, new KeywordSet, new LineFileReader(filename))),
    contentManager_(filename),
    root(0)
{
}

/**
 *  @details    Frees resources used by XmlDocument.
 */
XmlDocument::~XmlDocument()
{
    if (root != 0) {
        delete root;
    }
}

/**
 *  @details    Get-method for the parser member.
 *
 *  @return     Reference to the parser member.
 */
const XmlParser & XmlDocument::parser() const
{
    return parser_;
}

/**
 *  @details    Get-method for the parser member.
 *
 *  @return     Reference to the parser member.
 */
XmlParser & XmlDocument::parser()
{
    return parser_;
}

/**
 *  @details    Get-method for the contentManager member.
 *
 *  @return     Reference to the contentManager member.
 */
const XmlContentManager & XmlDocument::contentManager() const
{
    return contentManager_;
}

/**
 *  @details    Get-method for the contentManager member.
 *
 *  @return     Reference to the contentManager member.
 */
XmlContentManager & XmlDocument::contentManager()
{
    return contentManager_;
}

/**
 *  @details    Builds a dictionary or similar XmlObject depending on the contents
 *              of the xml. This can be either a dictionary, an array or a value.
 *              Furthermore, the XmlObject returned can be wrapped using the XmlWrapper
 *              class for easier manipulation.
 *
 *  @return     A pointer XmlObject representing the root of the xml document.
 *
 *  @sa         TagNode::to_object()
 */
XmlObject * XmlDocument::getDictionary()
{
    return root->to_object();
}

/**
 *  @details    Creates an XmlDocument by parsing the file given as a parameter.
 *              This means that a parser will be initialized and a tree of TagNode
 *              elements will be created upon correct parsing. If the tree is
 *              created correctly, the content of all leaf nodes will be located
 *              by using the XmlContentManager. If an error occurs, the parsing will
 *              stop and no XmlDocument will be returned.
 *
 *  @param[in]                      A c-style string. The file to open.
 *
 *  @return     A pointer to the XmlDocument instance created or 0 if an error occured.
 *
 *  @sa         XmlParser::parse()
 *  @sa         TagNode::find_content()
 */
XmlDocument * XmlDocument::open(const char * filename)
{
    XmlDocument * document = new XmlDocument(filename);
    
    document->parser_.tokenizer().automata().loadMatrix(MATRIX_FILE);
    document->root = document->parser_.parse();
    if (document->root == 0) {
        delete document;
        document = 0;
    } else {
        document->root->find_content(document->contentManager_);
    }
    
    return document;
}
