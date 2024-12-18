#include <iostream>
#include "Error_detection.h"
using namespace std;

vector<pair<string, size_t>> extractTags(const string& xmlContent) {
    vector<pair<string, size_t>> tags; // Vector to store tag names and their line numbers
    size_t lineNumber = 1;             // Start with line 1
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
    vector<pair<string, size_t>> tagsWithLines = extractTags(xmlContent); // Extract tags and line numbers
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
                    tagStack.pop(); // Proper match, remove the opening tag from stack
                } else {
                    // Push it in errors and continue searching for a match
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
                        cout << "Missing opening tag for: </" << closingTag << "> on line " << line << endl; //line refers to no.of line of the existed tag 
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
    // Summary of errors
    if (countErrors == 0) {
        cout << "No errors, all tags are properly matched!" << endl;
    } else {
        cout << "There are " << countErrors << " errors in the XML document." << endl;
    }

    return errors;
}
