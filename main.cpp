#include "Minifying.h"

int main() {
    string fileName = "sample (1).xml"; // Name of the XML input file
    string outputFileName = "minified.xml";  // Name of the output file
    ifstream xmlFile(fileName);

    if (!xmlFile.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return 1;
    }

    string xmlContent, line;

    // Read the file line by line
    while (getline(xmlFile, line)) {
        xmlContent += line + "\n"; // Append each line to the xmlContent string
    }

    xmlFile.close(); // Close the file

    // Output the read XML content
    cout << "Read XML Content:\n" << xmlContent << endl;

  
   /* string rawXml = R"(
               <root>
                   <child> Value 1                               </child>

                   <child>
                       <subchild> Value 2 </subchild>
                   </child>
               </root>)";  to test the function */

           cout << "Original XML:\n" << xmlContent  << "\n";

           // Minify the XML
           string minifiedXml = minifying(xmlContent);
           cout << "\nMinified XML:\n" << minifiedXml << "\n";

    ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open file " << outputFileName << " for writing." << endl;
        return 1;
    }

    outputFile << minifiedXml; // Write the minified content to the file
    outputFile.close();        // Close the output file

    cout << "The XML file has been minified and saved to " << outputFileName << endl;

    return 0;
}
