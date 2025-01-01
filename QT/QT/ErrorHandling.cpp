#include "ErrorHandling.h"


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

void error_handling(ifstream & inputfile,ofstream &outputfile) {

    if (!inputfile.is_open()) {
        cerr << "Error: Could not open file "  << endl;

    }

    string xmlContent, line;

    // Read the file line by line
    while (getline(inputfile, line)) {
        xmlContent += line + "\n"; // Append each line to the xmlContent string
    }

    inputfile.close(); // Close the file

    vector<string>line_by_line;

    char startchar='<';
    char endchar='>';
    int count_errors=0;
    int current_line=1;
    vector<int>line_number;
    string tag;

    vector<string>opening_tags;
    size_t startind=-1,endind=-1;

    size_t pos=0;
    while (pos < xmlContent.size()) {

        if(xmlContent[pos]=='\n')
            current_line++;

        startind = xmlContent.find(startchar, pos); // search for '<'
        if (startind==string::npos) { // there is no opening tag,logical error
            break;
        }
        // found a tag
        endind = xmlContent.find(endchar, startind);
        if (endind==string::npos) { // there is no closing tag,logical error
            cout<<"MALFORMED XML FILE";
            break;
        }
        tag = xmlContent.substr(startind , endind - startind + 1); // extract tag with <>

        if (tag[1] != '/') // it is an opening tag
        {
            opening_tags.push_back(tag);
            line_number.push_back(current_line);

        }

        else if (tag[1] == '/') // it is a closing tag
        {
            if (!opening_tags.empty()){
                string closing_tag_name = tag.substr(2, tag.size() - 3); // Extract tag name without "</" and ">"
                string opening_tag_name = opening_tags.back().substr(1, opening_tags.back().size() - 2); // Extract tag name from "<tag>"

                if (closing_tag_name == opening_tag_name) { // Match found
                    opening_tags.pop_back();

                }
                else if (closing_tag_name != opening_tag_name) { // not equal

                    bool found = false;
                    auto it2=line_number.begin();
                    for (auto it = opening_tags.begin(); it != opening_tags.end(); ++it, ++it2) {
                        if (tag.substr(2) == it->substr(1)) {   // Compare the closing tag with the opening tags in vector
                            found = true;
                            size_t opening_tag_pos = xmlContent.find(*it); // Find the position of the opening tag
                            size_t closing_of_thisTag = xmlContent.find('>',opening_tag_pos);

                            // Find the next meaningful character after the closing tag
                            size_t next_char_pos = closing_of_thisTag + 1;
                            while (next_char_pos < xmlContent.size() && isspace(xmlContent[next_char_pos]))  {
                                next_char_pos++;
                            }
                            if(xmlContent[next_char_pos]!='<') {
                                size_t endofcontent=xmlContent.find('<',closing_of_thisTag);
                                xmlContent.insert(endofcontent-1,tag);
                                cout<<"There is a missing closing tag for "<<*it<<"on line "<<*it2<<endl;
                                opening_tags.erase(it); // Erase the matched opening tag from vector
                                line_number.erase(it2);
                                count_errors++;



                            }
                            else {
                                opening_tags.erase(it); // we don't need to insert anything in file
                                line_number.erase(it2);

                            }

                        }
                    }
                    if (!found) { // we didn't find a matching opening tag
                        // Generate the missing opening tag
                        string opening_tag = "<" + tag.substr(2);

                        // Start from the given index and move backward while skipping spaces
                        size_t check_pos = startind;
                        while (check_pos > 0 && isspace(xmlContent[check_pos])) {
                            check_pos--;
                        }
                        if(check_pos > 0 && xmlContent[check_pos] != '>') {
                            size_t start=xmlContent.rfind('>',check_pos);
                            xmlContent.insert(start + 1, opening_tag);
                        }
                        else
                            xmlContent.insert(check_pos+1, opening_tag);

                        cout<<"There is a missing opening tag for "<<tag<<" on line "<<current_line<<endl;
                        count_errors++;
                    }

                }
            }
            else { // no opening tags in stack vector

                string opening_tag = "<" + tag.substr(2); // Generate the opening tag
                size_t pos2 = xmlContent.rfind('>', startind);
                if (pos != string::npos) {
                    xmlContent.insert(pos2+1, opening_tag); // Insert the opening tag before the closing tag
                }
                cout<<"There is a missing closing tag for "<<tag<<" on line "<<current_line<<endl;
                count_errors++;
            }

        }

        pos = endind + 1;
    }

    while (!opening_tags.empty()) {
        string opening_tag = opening_tags.back();
        string closing_tag = "</" + opening_tag.substr(1); // Generate corresponding closing tag

        size_t start_pos = 0;

        // Loop to find all occurrences of the opening tag in the XML content
        while ((start_pos = xmlContent.find(opening_tag, start_pos)) != string::npos) {
            // Find the position of the closing '>' for the opening tag
            size_t closing_of_thisTag = xmlContent.find('>', start_pos);

            if (closing_of_thisTag != string::npos) {
                // Check if there is already a corresponding closing tag after the opening tag
                size_t next_tag_pos = xmlContent.find('<', closing_of_thisTag + 1);

                if (next_tag_pos != string::npos) {
                    string next_tag = xmlContent.substr(next_tag_pos, xmlContent.find('>', next_tag_pos) - next_tag_pos + 1);

                    // If the next tag is not the expected closing tag, insert the closing tag
                    if (next_tag != closing_tag) {
                        xmlContent.insert(closing_of_thisTag + 1, closing_tag);
                    }
                } else {
                    // If no next tag is found, insert the closing tag
                    xmlContent.insert(closing_of_thisTag + 1, closing_tag);
                }
            }

            // Move the start position forward to avoid infinite loop
            start_pos = closing_of_thisTag + 1;

        }

        // Remove the opening tag from the stack
        cout<<"There is a missing closing tag for "<<opening_tags.back()<<" on line "<<line_number.back()<<endl;
        opening_tags.pop_back();
        line_number.pop_back();
        count_errors++;


    }
    // cout<<"There are "<<count_errors<<" errors."<<endl;

    outputfile<< xmlContent; // Write the corrected XML content to the new file
    outputfile.close(); // Close the file


}
