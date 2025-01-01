#include "convertxmltojson.h"

void indent(int indentation, ofstream &outputFile){
    outputFile<<endl;
    if (indentation<0)return;
    while(indentation--)outputFile<<"    ";
}
void closeTag(string &jsonString,stack<char>&st) {
    if (!st.empty()) {
        jsonString.push_back(st.top());
        st.pop();
    }
}

void arrayTag(const string& tagName,string &jsonString,stack<char>&st) {
    jsonString.push_back('"');
    jsonString+= tagName;
    jsonString+="\": [";
    st.push(']');
}

void sentenceArrayTag(const string& tagName, const string& sentence, string &jsonString, stack<char>&st) {
    jsonString.push_back('"');
    jsonString+= tagName;
    jsonString+="\": [";
    jsonString.push_back('"');
    jsonString+= sentence;
    jsonString.push_back('"');
    st.push(']');
}

void sentenceTag(const string& tagName, const string& sentence,string &jsonString) {
    jsonString.push_back('"');
    jsonString+= tagName;
    jsonString+="\": \"";
    jsonString+= sentence;
    jsonString.push_back('"');
}

void normalTag(const string& tagName,string &jsonString,stack<char>&st) {
    jsonString.push_back('"');
    jsonString+= tagName;
    jsonString+="\": {";
    st.push('}');
}

void justSentence(const string& sentence, string &jsonString) {
    jsonString.push_back('"');
    jsonString+= sentence;
    jsonString.push_back('"');
}
void convertXMLtoJSON(ifstream &file, ofstream &outputFile ){

    string jsonString;
    string xmlString, prevXML;         // whole strings
    string previousTag, tagName;      // tag names
    stack<char>st;
    getline(file, prevXML);           // first tag
    size_t poss1 = prevXML.find('<');
    size_t poss2 = prevXML.find('>');
    previousTag = prevXML.substr(poss1 + 1, poss2 - poss1 - 1);

    // flags
    bool arr, sameTagName, tagName1, tagName2, sentenceTag1, sentenceTag2, closingTag1, closingTag2, notSentence;
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
        arr = false, sameTagName = false, tagName1 = false, tagName2 = false;
        sentenceTag1 = false, sentenceTag2 = false, closingTag1 = false, closingTag2 = false;

        // extract sentence
        string sentence = xmlString.substr(pos2 + 1, pos3 - 1 - pos2 - 1);

        // for previous string
        if (poss3 != string::npos) {
            if (poss2 < poss3) {
                sentenceTag1 = true;
            } else {
                closingTag1 = true;
            }
        } else {
            tagName1 = true;
        }

        // for current string
        if (pos3 != string::npos) {
            if (pos2 < pos3) {
                sentenceTag2 = true;
            } else {
                closingTag2 = true;
            }
        } else {
            tagName2 = true;
        }

        if (tagName == previousTag.substr(0, previousTag.size() - 1)) arr = true;
        if (previousTag.substr(1) == tagName) sameTagName = true;

        if (tagName1 && tagName2 && arr) {                // if array  <users> <user>
            arrayTag(tagName,jsonString,st);
            notSentence = true;

        } else if (tagName1 && sentenceTag2 && arr) {
            sentenceArrayTag(tagName, sentence, jsonString, st);
            notSentence = true;

        } else if (tagName1 && tagName2) {                // not array
            if (notSentence) {
                st.push('}');
                jsonString.push_back('{');
            }
            normalTag(tagName,jsonString,st);
            notSentence = false;

        } else if (tagName1 && sentenceTag2) {            // <user> <id>2</id>
            if (notSentence) {
                st.push('}');
                jsonString.push_back('{');
            }
            sentenceTag(tagName, sentence,jsonString);

        } else if (sentenceTag1 && sentenceTag2) {        // <id>2</id> <name>ahmed</name>
            jsonString.push_back(',');
            if (previousTag == tagName) {
                justSentence(sentence, jsonString);                  // in an array
            } else {
                sentenceTag(tagName, sentence,jsonString);
            }

        } else if (sentenceTag1 && tagName2) {           // <body>2</body> <topics>
            jsonString.push_back(',');
            normalTag(tagName,jsonString,st);

        } else if (closingTag1 && tagName2 && sameTagName) { //</topic> <topic>
            if (!st.empty() && st.top() == ']') {
                jsonString.push_back(',');
            } else {
                if (!st.empty()) {
                    jsonString.push_back(st.top());
                    jsonString.push_back(',');
                    st.pop();
                }
            }

        } else if (closingTag1 && closingTag2) {          //</topics> </post>
            closeTag(jsonString,st);

        } else if (closingTag1 && tagName2) {             //</posts> <followers>
            closeTag(jsonString,st);
            closeTag(jsonString,st);
            jsonString.push_back(',');
            normalTag(tagName,jsonString,st);

        } else if (sentenceTag1 && closingTag2) {         //<id>2</id> </follower>
            closeTag(jsonString,st);
        }

        prevXML = xmlString;
    }

    while (!st.empty()) closeTag(jsonString,st);
    jsonString+="}}";




    //prettifying the json file

    int indentation=1,flag=0;
    for (int i = 0; i < jsonString.size(); ++i) {
        outputFile<<jsonString[i];
        if(jsonString[i]=='\"' && (jsonString[i+1]==']'||jsonString[i+1]=='}') && flag){indentation--; indent(indentation,outputFile);  }
        else if(jsonString[i]=='\"' && (jsonString[i+1]==']'||jsonString[i+1]=='}')) {indentation-=2; indent(indentation,outputFile);  flag=1;}
        else if(jsonString[i]=='\"' && (jsonString[i+1]==',')) {outputFile<<",";  indent(indentation-1,outputFile);i++;  }
        else if(jsonString[i]=='}' && jsonString[i+1]==',') {outputFile<<jsonString[i+1]; indent(indentation,outputFile); i++;}
        else if(jsonString[i]=='{' || jsonString[i]=='[') { indent(indentation,outputFile); indentation++; }
        else if(jsonString[i]=='}' || jsonString[i]==']') {indentation--;indent(indentation,outputFile);  }
    }
    file.close();
outputFile.close();

}
