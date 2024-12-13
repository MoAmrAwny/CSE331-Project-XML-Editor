#include <fstream>
#include <bits/stdc++.h>
using namespace std;

ifstream file("sample.xml");
ofstream outputFile("sample.json");

string jsonString;
stack<char> st;
void indentate(int indentation){

    outputFile<<endl;
    if (indentation<0)return;
    while(indentation--)outputFile<<"    ";
}
void closeTag() {
    if (!st.empty()) {
        jsonString.push_back(st.top());
        st.pop();
    }
}

void arrayTag(string tagName) {
    jsonString.push_back('"');
    jsonString+= tagName;
    jsonString+="\": [";
    st.push(']');
}

void sentencearrayTag(string tagName, string sentence) {
    jsonString.push_back('"');
    jsonString+= tagName;
    jsonString+="\": [";
    jsonString.push_back('"');
    jsonString+= sentence;
    jsonString.push_back('"');
    st.push(']');
}

void sentenceTag(string tagName, string sentence) {
    jsonString.push_back('"');
    jsonString+= tagName;
    jsonString+="\": \"";
    jsonString+= sentence;
    jsonString.push_back('"');
}

void normalTag(string tagName) {
    jsonString.push_back('"');
    jsonString+= tagName;
    jsonString+="\": {";
    st.push('}');
}

void justsentence(string sentence) {
    jsonString.push_back('"');
    jsonString+= sentence;
    jsonString.push_back('"');
}

int main() {
    string xmlString, prevXML;         // whole strings
    string previousTag, tagName;      // tag names

    getline(file, prevXML);           // first tag
    size_t poss1 = prevXML.find('<');
    size_t poss2 = prevXML.find('>');
    previousTag = prevXML.substr(poss1 + 1, poss2 - poss1 - 1);

    // flags
    bool arr, sametagname, tagname1, tagname2, sentencetag1, sentencetag2, closingtag1, closingtag2, notasentence;
    jsonString+= "{\"";
    jsonString+= previousTag;
    jsonString+= "\": {";

    while (getline(file, xmlString)) {
        // locate tag names
        size_t pos1 = xmlString.find('<');
        size_t pos2 = xmlString.find('>');
        size_t pos3 = xmlString.find('/');
        poss1 = prevXML.find('<');
        poss2 = prevXML.find('>');
        size_t poss3 = prevXML.find('/');

        tagName = xmlString.substr(pos1 + 1, pos2 - pos1 - 1);
        previousTag = prevXML.substr(poss1 + 1, poss2 - poss1 - 1);

        // initialize flags at every iteration
        arr = false, sametagname = false, tagname1 = false, tagname2 = false;
        sentencetag1 = false, sentencetag2 = false, closingtag1 = false, closingtag2 = false;

        // extract sentence
        string sentence = xmlString.substr(pos2 + 1, pos3 - 1 - pos2 - 1);

        // for previous string
        if (poss3 != string::npos) {
            if (poss2 < poss3) {
                sentencetag1 = true;
            } else {
                closingtag1 = true;
            }
        } else {
            tagname1 = true;
        }

        // for current string
        if (pos3 != string::npos) {
            if (pos2 < pos3) {
                sentencetag2 = true;
            } else {
                closingtag2 = true;
            }
        } else {
            tagname2 = true;
        }

        if (tagName == previousTag.substr(0, previousTag.size() - 1)) arr = true;
        if (previousTag.substr(1) == tagName) sametagname = true;

        if (tagname1 && tagname2 && arr) {                // if array
            arrayTag(tagName);
            notasentence = true;

        } else if (tagname1 && sentencetag2 && arr) {
            sentencearrayTag(tagName, sentence);
            notasentence = true;

        } else if (tagname1 && tagname2) {                // not array
            if (notasentence) {
                st.push('}');
                jsonString.push_back('{');
            }
            normalTag(tagName);
            notasentence = false;

        } else if (tagname1 && sentencetag2) {            // <user> <id>2</id>
            if (notasentence) {
                st.push('}');
                jsonString.push_back('{');
            }
            sentenceTag(tagName, sentence);

        } else if (sentencetag1 && sentencetag2) {        // <id>2</id> <name>ahmed</name>
            jsonString.push_back(',');
            if (previousTag == tagName) {
                justsentence(sentence);                  // in an array
            } else {
                sentenceTag(tagName, sentence);
            }

        } else if (sentencetag1 && tagname2) {           // <body>2</body> <topics>
            jsonString.push_back(',');
            normalTag(tagName);

        } else if (closingtag1 && tagname2 && sametagname) { //</topic> <topic>
            if (!st.empty() && st.top() == ']') {
                jsonString.push_back(',');
            } else {
                if (!st.empty()) {
                    jsonString.push_back(st.top());
                    jsonString.push_back(',');
                    st.pop();
                }
            }

        } else if (closingtag1 && closingtag2) {          //</topics> </post>
            closeTag();

        } else if (closingtag1 && tagname2) {             //</posts> <followers>
            closeTag();
            closeTag();
            jsonString.push_back(',');
            normalTag(tagName);

        } else if (sentencetag1 && closingtag2) {         //<id>2</id> </follower>
            closeTag();
        }

        prevXML = xmlString;
    }

    while (!st.empty()) closeTag();
    jsonString+="}}";




    //prettifying



    int indentation=1,flag=0;
    cout<<jsonString;
    for (int i = 0; i < jsonString.size(); ++i) {
        outputFile<<jsonString[i];
        if(jsonString[i]=='\"' && (jsonString[i+1]==']'||jsonString[i+1]=='}') && flag){indentation--; indentate(indentation);  }
        else if(jsonString[i]=='\"' && (jsonString[i+1]==']'||jsonString[i+1]=='}')) {indentation-=2; indentate(indentation);  flag=1;}
        else if(jsonString[i]=='\"' && (jsonString[i+1]==',')) {outputFile<<",";  indentate(indentation-1);i++;  }
        else if(jsonString[i]=='}' && jsonString[i+1]==',') {outputFile<<jsonString[i+1]; indentate(indentation); i++;}
        else if(jsonString[i]=='{' || jsonString[i]=='[') { indentate(indentation); indentation++; }
        else if(jsonString[i]=='}' || jsonString[i]==']') {indentation--;indentate(indentation);  }
    }


}
