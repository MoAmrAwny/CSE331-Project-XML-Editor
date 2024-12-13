
#include "Error_detection_correction.h"

using namespace std;


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



vector<pair<string, size_t>> extractTags(const string& xmlContent) {
    vector<pair<string, size_t>> tags; 
    size_t lineNumber = 1;             
    size_t pos = 0;                    // Current parsing position

    while (pos < xmlContent.size()) {
        // Increment line number for newlines encountered while parsing
        if (xmlContent[pos] == '\n') {
            ++lineNumber;
            ++pos;
            continue;
        }

        // Find the next '<'
        size_t start = xmlContent.find('<', pos);
        if (start == string::npos) break; // No more tags

        // Handle any skipped newlines between the current position and the start of the tag
        for (size_t i = pos; i < start; ++i) {
            if (xmlContent[i] == '\n') ++lineNumber;
        }

        // Find the closing '>'
        size_t end = xmlContent.find('>', start);
        if (end != string::npos) {
            // Extract tag name without '<' and '>'
            string tag = xmlContent.substr(start + 1, end - start - 1);
            tags.push_back({tag, lineNumber}); // Store the tag and its current line number
            pos = end + 1; // Move position after the '>'
        } else {
            
            break;
        }
    }

    return tags;
}


vector<pair<string, size_t>> XML_detection(const string& xmlContent) {
    vector<pair<string, size_t>> tagsWithLines = extractTags(xmlContent); 
    stack<pair<string, size_t>> tagStack; // Stack for opening tags
    vector<pair<string, size_t>> errors; // Vector for error storage
    vector<pair<string, size_t>> missingopening; // Vector for error storage
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
                    tagStack.pop(); 
                } else {
                    // Push  and continue searching for a match
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
                        tagStack.pop(); 
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
                        missingopening.push_back(tagLine);
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
        cout << "Missing closing tag for: <" << tagStack.top().first << "> on line " << tagStack.top().second << endl;
        tagStack.pop();
        countErrors++;
    }
    int k=missingopening.size()-1;
    while (k >= 0) {
     errors.push_back(missingopening[k--]);
    }
    
    if (countErrors == 0) {
        cout << "No errors, all tags are properly matched!" << endl;
    } else {
        cout << "There are " << countErrors << " errors in the XML document." << endl;
    }

    return errors;
}





void XML_correction(vector<pair<string, size_t>> errors, string& xmlContent) {
    istringstream stream(xmlContent);  // Stream to read XML content line by line
    stringstream correctedContent;     // Stringstream to build the corrected content
    size_t lineNumber = 1;
    size_t errorIndex = 0;
    string line;

    // Process each line in the original xmlContent
    while (getline(stream, line)) {

        if (errorIndex < errors.size() && lineNumber == errors[errorIndex].second) {
            const string& tag = errors[errorIndex].first;

            // If it's an opening tag, add the corresponding closing tag at the end
            if (tag.substr(0, 1) != "/") {
                line = line + "</" + tag + ">";  // Closing tag
            }
            // If it's a closing tag, add the corresponding opening tag at the start
            else {
                line = "<" + tag.substr(1) + ">" + line;   // Opening tag
            }

            ++errorIndex; 
        }

        correctedContent << line <<"\n";  
        //if (stream.peek() != EOF) correctedContent << "\n";
        ++lineNumber;
    }

    
    xmlContent = correctedContent.str();
    saveXMLToFile("outputXML.xml", xmlContent); 

}
