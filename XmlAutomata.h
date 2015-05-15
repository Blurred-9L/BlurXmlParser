/**
 *  @file   XmlAutomata.h
 *  @author Blurred-9L
 */

#ifndef XML_PARSER_XML_AUTOMATA_H
#define XML_PARSER_XML_AUTOMATA_H

#include "BlurParser/Tokenizer/AbstractAutomata.h"

/**
 *  @class  XmlAutomata
 *
 *  @brief  The XmlAutoamta class is used to hold the automata used by a
 *          tokenizer in order to convert into tokens a xml document.
 */
class XmlAutomata : public AbstractAutomata {
public:
    /**
     *  @enum   InputType
     */
    enum InputType {
        LETTER,
        DIGIT,
        LT,
        GT,
        SLASH,
        EQUALS,
        QUOTE,
        ANY,
        HYPHEN,
        PERIOD,
        WHITESPACE
    };
    
    /**
     *  @enum   TokenType
     */
    enum TokenType {
        NAME_TOK,
        LT_TOK,
        GT_TOK,
        SLASH_TOK,
        EQ_TOK,
        STR_TOK,
        CONTENT_TOK
    };
    
    /// Constructor
    explicit XmlAutomata(const char * filename = 0);
    /// Destructor
    virtual ~XmlAutomata();
    /// Gets the next state
    virtual int nextState(int state, char input) const;
    /// Checks if state is accept state
    virtual bool isAcceptState(int state) const;
    /// Gets token type based on final state
    virtual int getTokenType(int state);
    /// Gets token name based on type
    virtual const char * getTokenName(int tokenType);
};

#endif /// NOT XML_PARSER_XML_AUTOMATA_H
