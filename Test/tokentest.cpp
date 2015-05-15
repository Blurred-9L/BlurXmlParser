#include <iostream>

#include "../XmlAutomata.h"
#include "../BlurParser/Tokenizer/KeywordSet.h"
#include "../BlurParser/Tokenizer/Tokenizer.h"
#include "../BlurParser/Core/Token.h"
#include "../BlurParser/Core/LineFileReader.h"

#define INPUT_FILE "Resources/testinput.txt"
#define TRANS_FILE "Resources/matrix.csv"

using namespace std;

int main()
{
    Tokenizer tokenizer(new XmlAutomata, new KeywordSet,
                        new LineFileReader(INPUT_FILE));
    Token * token = 0;
    
    cout << "Load? " << tokenizer.automata().loadMatrix(TRANS_FILE) << endl;
    token = tokenizer.getToken();
    while (token != 0) {
        cout << "Symbol: " << token->symbol() << " Type: "
             << tokenizer.automata().getTokenName(token->type()) << endl;
        delete token;
        token = tokenizer.getToken();
    }
    
    return 0;
}


