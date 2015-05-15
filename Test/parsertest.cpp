#include <iostream>

#include "../BlurParser/Tokenizer/Tokenizer.h"
#include "../BlurParser/Tokenizer/KeywordSet.h"
#include "../BlurParser/Core/LineFileReader.h"

#include "../XmlParser.h"
#include "../TagNode.h"
#include "../XmlAutomata.h"
#include "../XmlContentManager.h"

using namespace std;

#define INPUT_FILE "Resources/testinput.txt"
#define TRANS_FILE "Resources/matrix.csv"

int main()
{
    XmlParser parser(new Tokenizer(new XmlAutomata, new KeywordSet, new LineFileReader(INPUT_FILE)));
    XmlContentManager contentManager(INPUT_FILE);
    TagNode * root = 0;
    
    cout << parser.tokenizer().automata().loadMatrix(TRANS_FILE) << endl;
    
    root = parser.parse();
    if (root != 0) {
        cout << "ok" << endl;
        root->find_content(contentManager);
        root->print(0);
        delete root;
    } else {
        cout << "not ok?" << endl;
    }
    
    return 0;
}
