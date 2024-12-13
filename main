#include "Error_detection_correction.h"


using namespace std;

int main() {
    string fileName = "bgrb wlahy.txt"; // Name of the XML file
    ifstream xmlFile(fileName); // Open the file

    if (!xmlFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return 1; // Exit with error code
    }

    string xmlContent, line;

    // Read the file line by line
    while (getline(xmlFile, line)) {
        xmlContent += line + "\n"; // Append each line to the xmlContent string
    }

    xmlFile.close(); // Close the file
    vector<pair<string,size_t>>errors=XML_detection(xmlContent);
    sort(errors.begin(), errors.end(), [](const pair<string, size_t>& a, const pair<string, size_t>& b) {
        return a.second < b.second; // Compare based on line number
    });
    if (errors.empty()) {
            cout << "No errors, all tags are properly matched!" << endl;
        } else {
            cout << "Errors detected:\n";
            for (const auto& error : errors) {
                cout << "Tag: <" << error.first << "> on line " << error.second << endl;
            }
        }



        XML_correction(errors,xmlContent);


        return 0;

}



