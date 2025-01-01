#include "Minifying.h"


void minifying(const string& fileName , string output) {
    // Read the XML content from the file
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return; // Exit the function
    }

    string xmlContent, line;
    while (getline(inputFile, line)) {
        xmlContent += line + "\n"; // Append each line to the xmlContent string
    }
    inputFile.close(); // Close the input file

    // Minify the content
    string result;
    bool insideTag = false;
    bool previousCharWasSpace = false;

    for (char ch : xmlContent) {
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

    // Overwrite the original file with the minified content
    ofstream outputFile(output);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open file " << output << " for writing." << endl;
        return; // Exit the function
    }
    outputFile << result; // Write the minified content back to the file
    outputFile.close();   // Close the output file

    cout << "File '" << output << "' has been minified successfully.\n";
}

