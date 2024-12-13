#include <fstream>
#include <bits/stdc++.h>
using namespace std;

ifstream file("sample.xml");
ofstream outputFile("sample.json");

stack<char> st;

void closeTag() {
    if (!st.empty()) {
        outputFile << st.top();
        st.pop();
    }
}

void arrayTag(string tagName) {
    outputFile << "\"" << tagName << "\": [";
    st.push(']');
}

void sentencearrayTag(string tagName, string sentence) {
    outputFile << "\"" << tagName << "\": [";
    outputFile << "\"" << sentence << "\"";
    st.push(']');
}

void sentenceTag(string tagName, string sentence) {
    outputFile << "\"" << tagName << "\": \"" << sentence << "\"";
}

void normalTag(string tagName) {
    outputFile << "\"" << tagName << "\": {";
    st.push('}');
}

void justsentence(string sentence) {
    outputFile << "\"" << sentence << "\"";
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

    outputFile << "{\"" << previousTag << "\": {";

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
                outputFile << '{';
            }
            normalTag(tagName);
            notasentence = false;

        } else if (tagname1 && sentencetag2) {            // <user> <id>2</id>
            if (notasentence) {
                st.push('}');
                outputFile << "{";
            }
            sentenceTag(tagName, sentence);

        } else if (sentencetag1 && sentencetag2) {        // <id>2</id> <name>ahmed</name>
            outputFile << ",";
            if (previousTag == tagName) {
                justsentence(sentence);                  // in an array
            } else {
                sentenceTag(tagName, sentence);
            }

        } else if (sentencetag1 && tagname2) {           // <body>2</body> <topics>
            outputFile << ",";
            normalTag(tagName);

        } else if (closingtag1 && tagname2 && sametagname) { //</topic> <topic>
            if (!st.empty() && st.top() == ']') {
                outputFile << ",";
            } else {
                if (!st.empty()) {
                    outputFile << st.top();
                    outputFile << ",";
                    st.pop();
                }
            }

        } else if (closingtag1 && closingtag2) {          //</topics> </post>
            closeTag();

        } else if (closingtag1 && tagname2) {             //</posts> <followers>
            closeTag();
            closeTag();
            outputFile << ",";
            normalTag(tagName);

        } else if (sentencetag1 && closingtag2) {         //<id>2</id> </follower>
            closeTag();
        }

        prevXML = xmlString;
    }

    while (!st.empty()) closeTag();
    outputFile << "}}";
    cout << st.size();
}
