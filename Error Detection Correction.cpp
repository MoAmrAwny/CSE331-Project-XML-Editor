
#include "Error_detection_correction.h"

using namespace std;

vector<pair<string, size_t>> extractTags(const string& xmlContent) {
    vector<pair<string, size_t>> tags; // Vector to store tag names and their line numbers
    size_t pos = 0;

    char s = '/'; // Character to check for closing tags
    size_t lineNumber = 0; // Start with line 1

    while (pos < xmlContent.size()) {
        // Count line breaks before finding a tag
        while (pos < xmlContent.size() && xmlContent[pos] == '\n') {
            ++lineNumber;
            ++pos;
        }

        // Find the next '<'
        pos = xmlContent.find('<', pos);
        if (pos == string::npos) break; // No more tags

        size_t endPos = xmlContent.find('>', pos); // Find closing '>'
        if (endPos != string::npos) {
            string fullTag = xmlContent.substr(pos + 1, endPos - pos - 1); // Extract tag name without '<' and '>'
            tags.push_back(make_pair(fullTag, lineNumber)); // Store the tag name and its line number
            pos = endPos + 1; // Move the position after the closing '>'
        } else {
            break; // Malformed XML
        }
    }

    return tags;


}

vector<pair<string, size_t>> XML_detection(const string& xmlContent) {
    vector<pair<string, size_t>> tagsWithLines = extractTags(xmlContent); // Extract tags and line numbers
    stack<pair<string, size_t>> tagStack; // Stack for opening tags
    vector<pair<string, size_t>> errors; // Vector for error storage
    int countErrors = 0;
    bool found = false;

    for (const auto& tagLine : tagsWithLines) {
        const string& tag = tagLine.first;
        size_t line = tagLine.second;

        if (tag.substr(0, 1) != "/") { // Opening tag
            tagStack.push(tagLine);
        } else { // Closing tag
            string closingTag = tag.substr(1); // Remove '/' from the closing tag

            if (!tagStack.empty()) {
                string openingTag = tagStack.top().first;

                if (closingTag == openingTag) {
                    tagStack.pop(); // Proper match, remove the opening tag
                } else {
                    // Push error and continue searching for a match
                    errors.push_back(tagStack.top());
                    tagStack.pop();

                    while (!tagStack.empty()) {
                        if (tagStack.top().first == closingTag) {
                            found = true;
                            break; // Match found
                        } else {
                            errors.push_back(tagStack.top());
                            tagStack.pop();
                        }
                    }

                    if (found) {
                        tagStack.pop(); // Remove the matched tag
                        // Push back the unmatched tags to the stack
                        for (int j = errors.size() - 1; j >= 0; --j) {
                            tagStack.push(errors[j]);
                        }
                        errors.clear();
                        found = false;
                    } else {
                        // No matching opening tag
                        cout << "Missing opening tag for: </" << closingTag << "> on line " << line << endl;
                        countErrors++;
                        for (int j = errors.size() - 1; j >= 0; --j) {
                            tagStack.push(errors[j]);
                        }
                        errors.clear();
                    }
                }
            } else {
                // Closing tag without any opening tag
                cout << "No matching opening tag for: </" << closingTag << "> on line " << line << endl;
                countErrors++;
            }
        }
    }

    // Collect unbalanced opening tags
    while (!tagStack.empty()) {
        auto unmatchedTag = tagStack.top();
        errors.push_back(unmatchedTag);
        cout << "Missing closing tag for: <" << unmatchedTag.first << "> on line " << unmatchedTag.second << endl;
        tagStack.pop();
        countErrors++;
    }

    // Summary of errors
    if (countErrors == 0) {
        cout << "No errors, all tags are properly matched!" << endl;
    } else {
        cout << "There are " << countErrors << " errors in the XML document." << endl;
    }

    return errors;
}



void saveXMLToFile(const string& fileName, const string& xmlContent) { // to turn the string to the xmlfile
    ofstream file(fileName);
    if (file.is_open()) {
        file << xmlContent;
        file.close();
        cout << "XML content saved to " << fileName << endl;
    } else {
        cout << "Error: Unable to open file " << fileName << endl;
    }
}


// void XML_correction(vector<pair<string,size_t>> errors, string& xmlContent) {
//
//     istringstream stream(xmlContent); // Stream for processing lines
//     size_t lineNumber = 0;
//     string line;
//     size_t errorIndex = 0;
//     while (getline(stream, line)) {
//         if (errorIndex < errors.size() && lineNumber == errors[errorIndex].second) {
//
//             const string& tag = errors[errorIndex].first;
//             if (tag.substr(0, 1) != "/") { // Opening tag
//                 line = line + "</" + tag + ">";
//             } else {
//                 line = "<" + tag + ">" + line ;
//             }
//             ++errorIndex;
//         }
//         ++lineNumber;
//     }
//     saveXMLToFile("outputXML",xmlContent);
// }

void XML_correction(vector<pair<string, size_t>> errors, string& xmlContent) {
    istringstream stream(xmlContent);  // Stream to read XML content line by line
    stringstream correctedContent;     // Stringstream to build the corrected content
    size_t lineNumber = 0;
    size_t errorIndex = 0;
    string line;

    // Process each line in the original xmlContent
    while (getline(stream, line)) {
        // Check if there's an error to fix on the current line
        if (errorIndex < errors.size() && lineNumber == errors[errorIndex].second) {
            const string& tag = errors[errorIndex].first;

            // If it's an opening tag, add the corresponding closing tag at the end
            if (tag.substr(0, 1) != "/") {
                line = line + "</" + tag + ">";  // Closing tag
            }
            // If it's a closing tag, add the corresponding opening tag at the start
            else {
                line = "<" + tag + ">" + line;   // Opening tag
            }

            ++errorIndex;  // Move to the next error
        }

        correctedContent << line << "\n";  // Add the (corrected) line to the result
        ++lineNumber;
    }

    // Now update the original xmlContent with corrected content
    xmlContent = correctedContent.str();
    saveXMLToFile("outputXML.xml", xmlContent);  // Save corrected content to file
}
