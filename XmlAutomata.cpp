/**
 *  @file   XmlAutomata.cpp
 *  @author Blurred-9L
 */

#include <algorithm>
#include <cctype>

#include "XmlAutomata.h"

/**
 *  @details    Constructs a XmlAutomata object by loading the matrix at the
 *              given path.
 *
 *  @param[in]  filename            The name of the file containing the transitions matrix.
 */
XmlAutomata::XmlAutomata(const char * filename) : AbstractAutomata(filename)
{
}

/**
 *  @details    Releases resources used by a XmlAutomata object.
 */
XmlAutomata::~XmlAutomata()
{
}

/**
 *  @details    Gets the next state given a current state and a current
 *              input.
 *
 *  @param[in]  state               The current state.
 *  @param[in]  input               The current symbol.
 *
 *  @return     The value of the next state.
 */
int XmlAutomata::nextState(int state, char input) const
{
    int new_state;
    
    switch (input) {
    case '<':
        new_state = transitions[state][LT];
        break;
    case '>':
        new_state = transitions[state][GT];
        break;
    case '/':
        new_state = transitions[state][SLASH];
        break;
    case '=':
        new_state = transitions[state][EQUALS];
        break;
    case '\"':
        new_state = transitions[state][QUOTE];
        break;
    case '_':
        new_state = transitions[state][LETTER];
        break;
    case ':':
        new_state = transitions[state][LETTER];
        break;
    case '-':
        new_state = transitions[state][HYPHEN];
        break;
    case '.':
        new_state = transitions[state][PERIOD];
        break;
    default:
        if (isalpha(input)) {
            new_state = transitions[state][LETTER];
        } else if (isdigit(input)) {
            new_state = transitions[state][DIGIT];
        } else if (isspace(input)) {
            new_state = transitions[state][WHITESPACE];
        } else {
            new_state = transitions[state][ANY];
        }
        break;
    }
    
    return new_state;
}

/**
 *  @details    Checks if the given state is a state at which a valid token might end.
 *
 *  @param[in]  state               The state to check
 *
 *  @return     A boolean value indicating if the given state can be accepted.
 */
bool XmlAutomata::isAcceptState(int state) const
{
    int accepted_states [] = {1, 2, 3, 4, 5, 7, 8};
    
    return std::binary_search(accepted_states, accepted_states + nTerminalStates_, state);
}

/**
 *  @details    Gets the token type depending on the given state.
 *
 *  @param[in]  state           The state to check.
 *
 *  @return     The type a token would have if it was accepted at the given state.
 */
int XmlAutomata::getTokenType(int state)
{
    int token_type = -1;
    
    switch (state) {
    case 1:
        token_type = NAME_TOK;
        break;
    case 2:
        token_type = LT_TOK;
        break;
    case 3:
        token_type = GT_TOK;
        break;
    case 4:
        token_type = SLASH_TOK;
        break;
    case 5:
        token_type = EQ_TOK;
        break;
    case 7:
        token_type = STR_TOK;
        break;
    case 8:
        token_type = CONTENT_TOK;
        break;
    }
    
    return token_type;
}

/**
 *  @details    Gets a string representing the name of a token by its given type.
 *
 *  @param[in]  tokenType           The type of the token.
 *
 *  @return     A string with the name of the token.
 */
const char * XmlAutomata::getTokenName(int tokenType)
{
    const char * token_names [] = {"Name", "<", ">", "/", "=", "String", "Content"};
    
    return token_names[tokenType];
}
