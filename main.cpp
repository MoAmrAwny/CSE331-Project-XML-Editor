#include "PrettifyXml.h"

int main()
{
    vector<string>command(6);
    for(int i=0;i<6;i++) {
        cin>>command[i];
    }
    if(command[1]=="format") {
        vector<string>input_xml=ReadXml(command[3]);
        ofstream outputFile(command[5]);
        PrettifyXML(input_xml,outputFile);
    }
    return 0;
}


