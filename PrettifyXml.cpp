//
// Created by Jana Aly on 12/27/2024.
//
#include "PrettifyXml.h"

//helper functions
void debug_tree(XmlNode* node, int level = 0) {
    if (!node) return;
    // Indentation for hierarchy
    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }
    // Print node details
    cout << "Node: " << node->name;
    if (!node->value.empty()) {
        cout << ", Value: " << node->value;
    }
    cout << endl;
    // Recurse for children
    for (XmlNode* child : node->children) {
        debug_tree(child, level + 1);
    }
}

string trim(const std::string& str) {
    auto start = str.begin();
    while (start != str.end() && isspace(*start)) {
        ++start;
    }
    auto end = str.end();
    do {--end;
    } while (distance(start, end) > 0 && isspace(*end));
    return string(start, end+1);
}

//parsing xml into tree structure
XmlNode* parse_node(const vector<string>& s, int& idx) {
    // Base case: If we've reached the end of the input or the line is empty, return nullptr
    if (idx >= s.size() || s[idx].empty()) {
        return nullptr; // End of input or empty line
    }
    XmlNode* xmlNode = new XmlNode(); // Create a new XmlNode instance for the current element
    if (s[idx][0] == '<' && s[idx][1] != '/') { // Check if the current line contains an opening tag
        string temp = "";
        int i = 1;
        // Extract the tag name from within the opening tag
        while (s[idx][i] != '>') {
            temp += s[idx][i];
            i++;
        }
        xmlNode->name = temp; // Assign the extracted tag name to the node
        // Move past the closing '>' of the opening tag
        i++;
        // Check if there is an inline value after the opening tag
        if (i < s[idx].length() && s[idx][i] != '<') {
            temp = "";
            // Extract the inline value until the next '<'
            while (i < s[idx].length() && s[idx][i] != '<') {
                temp += s[idx][i];
                i++;
            }
            xmlNode->value = trim(temp); // Assign the trimmed value to the node
            if (s[idx][i] == '<') {  // If the next character is '<', it might be a closing tag or child node
                idx++; // Move to the next line
                return xmlNode; // Return the node as it has an inline value and no children
            }
        } else {
            idx++; // Move to the next line if there's no inline value
        }
    }
    if (idx < s.size() && s[idx][0] != '<') {     // Handle cases where the value is on its own line
        xmlNode->value = s[idx]; // Assign the value to the node
        idx++; // Move to the next line
    }
    else if (idx < s.size() && s[idx][1] == '/') { // Handle the closing tag if encountered
        idx++; // Move past the closing tag
    }
    // Parse child nodes if any
    while (idx < s.size() && !(s[idx][0] == '<' && s[idx][1] == '/')) { // Loop until a closing tag is encountered
        XmlNode* child = parse_node(s, idx); // Recursively parse the child node
        if (child) {
            xmlNode->children.push_back(child); // Add the child node to the children vector
        }
    }
    // Handle the closing tag of the current node
    if (idx < s.size() && s[idx][1] == '/') {
        idx++; // Move past the closing tag
        return xmlNode; // Return the constructed node
    }
    // Return the constructed XmlNode
    return xmlNode;
}

void print_node(XmlNode* node, ostringstream& out, int level =0) {
    if (!node) return; // Base case: If the node is null, return immediately
    // Indent the output based on the current tree depth (level)
    for (int i = 0; i < level; ++i) {
        out << "   "; // Add spaces for pretty-printing
    }
    // Print the opening tag of the current XML node
    out << "<" << node->name << ">";
    // If the node has a value, print it directly after the opening tag
    if (!node->value.empty()) {
        out << node->value;
    }
    // If the node has children, handle them recursively
    if (!node->children.empty()) {
        out << endl; // Add a newline after the opening tag for better readability
        // Recursively print each child node, increasing the depth level
        for (XmlNode* child : node->children) {
            print_node(child, out, level + 1);
        }
        // Indent the closing tag to align with the opening tag
        for (int i = 0; i < level; ++i) {
            out << "   ";
        }
    }
    // Print the closing tag of the current XML node
    out << "</" << node->name << ">" << endl;
}

vector<string> ReadXml(ifstream& in) {
    vector<string>input_xml;
    string line,xmlContent="";
    //ifstream in(filename);  //command[3]
    //in here is command[3]
    //
    // read file into input_xml
    // Read the entire file into a single string
    while (getline(in, line)) {
        xmlContent += trim(line);  // Concatenate each line into xmlContent
    }
    in.close();
    string temp = "";
    // Iterate through the string and split at each tag boundary
    for (int i = 0; i < xmlContent.length(); ++i) {
        if (xmlContent[i] == '<') {
            if (!temp.empty()) {
                input_xml.push_back(temp);
                temp = "";  // Clear the temp string
            }
            temp += '<';
        }
        else if (xmlContent[i] == '>') {
            temp += '>';
            input_xml.push_back(temp);
            temp = "";  // Clear temp to handle next value or tag
        }
        else if (xmlContent[i] == '/' && xmlContent[i + 1] == '>') {
            temp += "</";  //self closing tags? <tag/>
            ++i;  // Skip the '/' character
        }
        else {
            temp += xmlContent[i];
        }
    }
    if (!temp.empty()) {
        input_xml.push_back(temp);
    }
    return input_xml;
}

void PrettifyXML(vector<string> input_xml,ofstream &outputFile) {
    XmlNode* rootNode;
    int idx=0;
    rootNode = parse_node(input_xml,idx);
    ostringstream xmlOutput;
    print_node(rootNode, xmlOutput);

    //Save the collected output directly to an XML file
    //ofstream outputFile("");  //command[5]
    if (!outputFile.is_open()) {
        cerr << "Failed to open output file for writing!" << endl;
        //return 1;
    }
    outputFile << xmlOutput.str();
    outputFile.close();

    cout << "XML file successfully saved to output.xml" << endl;
}
