#include <iostream>

#include "../XmlDocument.h"
#include "../XmlObject.h"
#include "../XmlDictionary.h"
#include "../XmlArray.h"
#include "../XmlValue.h"
#include "../XmlWrapper.h"

#define INPUT_FILE "Resources/extratest.xml"

using namespace std;

int main()
{
    XmlDocument * document = XmlDocument::open(INPUT_FILE);
    XmlObject * rootObject = 0;
    
    if (document != 0) {
        cout << "File opened correctly!" << endl;
        rootObject = document->getDictionary();
        cout << "Dictionary obtained!" << endl;
        cout << "Trying to get title..." << endl;
        cout << dynamic_cast<XmlDictionary *>(rootObject)->size() << endl;
        XmlWrapper wrapper(*rootObject);
        // inputtest.txt *** General test
        /*cout << wrapper["channel"]["title"].get() << endl;
        cout << wrapper["channel"]["link"].get() << endl;
        cout << wrapper["channel"]["description"].get() << endl;
        cout << wrapper["channel"]["item"]["title"].get() << endl;
        cout << wrapper["channel"]["item"]["link"].get() << endl;
        cout << wrapper["channel"]["item"]["description"].get() << endl;*/
        // extratest.xml *** Testing for array
        cout << wrapper["nombre"].get() << endl;
        cout << wrapper["clave"].get() << endl;
        for (int i = 0; i < wrapper["horarios"].size(); i++) {
            cout << wrapper["horarios"][i]["dia"].get() << endl;
            cout << wrapper["horarios"][i]["hora"].get() << endl;
            cout << wrapper["horarios"][i]["duracion"].get() << endl;
        }
        for (int i = 0; i < wrapper["alumnos"].size(); i++) {
            cout << wrapper["alumnos"][i]["numero_lista"].get() << endl;
            cout << wrapper["alumnos"][i]["nombre"].get() << endl;
            cout << wrapper["alumnos"][i]["apellidos"].get() << endl;
            cout << wrapper["alumnos"][i]["codigo"].get() << endl;
        }
        // extratest2.xml *** Testing for mixed dictionary
        /*cout << wrapper["nombre"].get() << endl;
        cout << wrapper["clave"].get() << endl;
        for (int i = 0; i < wrapper["horarios"].size(); i++) {
            cout << wrapper["horarios"][i]["dia"].get() << endl;
            cout << wrapper["horarios"][i]["hora"].get() << endl;
            cout << wrapper["horarios"][i]["duracion"].get() << endl;
        }
        cout << wrapper["alumnos"]["num_alumnos"].get() << endl;
        for (int i = 0; i < wrapper["alumnos"]["alumno"].size(); i++) {
            cout << wrapper["alumnos"]["alumno"][i]["numero_lista"].get() << endl;
            cout << wrapper["alumnos"]["alumno"][i]["nombre"].get() << endl;
            cout << wrapper["alumnos"]["alumno"][i]["apellidos"].get() << endl;
            cout << wrapper["alumnos"]["alumno"][i]["codigo"].get() << endl;
        }*/
        delete rootObject;
        delete document;
    }
    
    return 0;
}
