#define Minifying.h

string minifying(const string& str) {
    string result;
    bool insideTag = false;
    bool previousCharWasSpace = false;

    for (char ch : str) {
        if (ch == '<') {
            insideTag = true;
            previousCharWasSpace = false;
            result += ch;
        } else if (ch == '>') {
            insideTag = false;
            result += ch;
        } else if (insideTag) {
            result += ch;
        } else if (!isspace(ch)) {
            result += ch;
            previousCharWasSpace = false;
        } else if (!previousCharWasSpace) {
            result += ' ';
            previousCharWasSpace = true;
        }
    }

    return result;}
