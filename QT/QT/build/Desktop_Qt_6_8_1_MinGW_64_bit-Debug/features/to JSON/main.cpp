#include "convertxmltojson.h"

int main() {
    ifstream file("sample.xml");
    ofstream outputFile("sample.json");
  convertXMLtoJSON(file,outputFile);
}
