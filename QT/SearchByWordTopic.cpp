//
// Created by Jana Aly on 12/29/2024.
//
#include "SearchByWordTopic.h"

// //helper functions
// void debug_tree(XmlNode* node, int level = 0) {
//     if (!node) return;
//     // Indentation for hierarchy
//     for (int i = 0; i < level; ++i) {
//         cout << "  ";
//     }
//     // Print node details
//     cout << "Node: " << node->name;
//     if (!node->value.empty()) {
//         cout << ", Value: " << node->value;
//     }
//     cout << endl;
//     // Recurse for children
//     for (XmlNode* child : node->children) {
//         debug_tree(child, level + 1);
//     }
// }

// string trim(const std::string& str) {
//     auto start = str.begin();
//     while (start != str.end() && isspace(*start)) {
//         ++start;
//     }
//     auto end = str.end();
//     do {--end;
//     } while (distance(start, end) > 0 && isspace(*end));
//     return string(start, end+1);
// }

// //parsing xml into tree structure
// XmlNode* parse_node(const vector<string>& s, int& idx) {
//     if (idx >= s.size() || s[idx].empty()) {
//         return nullptr; // End of input or empty line
//     }
//     XmlNode* xmlNode = new XmlNode();
//     // Parse the opening tag
//     if (s[idx][0] == '<' && s[idx][1] != '/') {
//         string temp = "";
//         int i = 1;
//         // Extract the tag name
//         while (s[idx][i] != '>') {
//             temp += s[idx][i];
//             i++;
//         }
//         xmlNode->name = temp;
//         cout << "Tag name: " << xmlNode->name << endl;
//         // Check for inline value
//         i++; // Move past '>'
//         if (i < s[idx].length() && s[idx][i] != '<') {
//             temp = "";
//             while (i < s[idx].length() && s[idx][i] != '<') {
//                 temp += s[idx][i];
//                 i++;
//             }
//             xmlNode->value = trim(temp);
//             cout << "Inline value: " << xmlNode->value << endl;
//             cout<<s[idx][i]<<endl;
//             if(s[idx][i]=='<') {
//                 cout << "Closing tag: " << s[idx] << endl;
//                 idx++;
//                 return xmlNode;
//             }
//         }
//         else idx++; // Move to the next line
//     }
//     // Handle value on its own line
//    if(idx<s.size() && s[idx][0]!='<') {
//        xmlNode->value=s[idx];
//        cout<<"own line value "<<xmlNode->value<<endl;
//        idx++;
//    }
//    else if (idx<s.size() && s[idx][1] == '/') {
//        cout << "Closing tag: " << s[idx] << endl;
//        idx++; // Move past the closing tag
//    }

//     // Parse child nodes
//     while (idx<s.size()&&!(s[idx][0] == '<' && s[idx][1] == '/')) {  //not closing tag
//         XmlNode* child = parse_node(s, idx);
//         if (child) {
//             xmlNode->children.push_back(child);
//             //cout << "Added child to " << xmlNode->name << ": " << child->name << endl;
//         }
//     }
//     if (idx<s.size() &&  s[idx][1] == '/') {
//         cout << "Closing tag: " << s[idx] << endl;
//         idx++; // Move past the closing tag
//         return xmlNode;
//     }
//     // Handle closing tag
//     return xmlNode;
// }

vector<pair<int,string>> SearchByWord(vector<string>input_xml,string word) {
    vector<pair<int,string>>WordsFound;
    vector<vector<string>>xml_users_posts(10000);
    for(int i=0;i<input_xml.size();i++) {
        int idx;
        if(input_xml[i]=="<followers>") {
            while(true) {
                i++;
                if(input_xml[i]=="</followers>") {
                    break;
                }
            }
        }
        if(input_xml[i]=="<id>") {
            idx=stoi(input_xml[i+1]);
        }
        if(input_xml[i]=="<body>") {
            xml_users_posts[idx].push_back(input_xml[i+1]);
        }
    }
    //string word="farha";
    int flag=0;
    for(int i=0;i<xml_users_posts.size();i++) {
        for(auto j:xml_users_posts[i]) {
            if(j.find(word)!=std::string::npos) {
                flag=1;
                size_t pos = j.find(word);
                if (pos != string::npos) {
                    // Insert "{" before the target word
                    j.insert(pos, "{");
                    // Insert "}" after the target word
                    j.insert(pos + word.length() + 1, "}");
                }
                WordsFound.push_back({i,j});
            }
        }
    }
    return WordsFound;
}

vector<string> ReadXmlToTree(ifstream &in) {
    vector<string>input_xml;
    string line,xmlContent="";
    while (getline(in, line)) {
        transform(line.begin(), line.end(), line.begin(),::tolower);
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

vector<pair<int,string>> SearchByTopic(vector<string>input_xml,string topic) {
    vector<pair<int,string>>TopicsFound;
     vector<vector<string>>xml_users_posts(10000);
    for(int i=0;i<input_xml.size();i++) {
        int idx;
        if(input_xml[i]=="<followers>") {
            while(true) {
                i++;
                if(input_xml[i]=="</followers>") {
                    break;
                }
            }
        }
        if(input_xml[i]=="<id>") {
            idx=stoi(input_xml[i+1]);
        }
        if(input_xml[i]=="<body>") {
            xml_users_posts[idx].push_back(input_xml[i+1]);
        }
    }
    vector<vector<vector<string>>>xml_users_topics(1000, vector<vector<string>>(1000));
    int idx,idx2;
    for(int i=0;i<input_xml.size();i++) {
        if(input_xml[i]=="<followers>") {
            while(true) {
                i++;
                if(input_xml[i]=="</followers>") {
                    break;
                }
            }
        }
        if(input_xml[i]=="<id>") {
            idx=stoi(input_xml[i+1]);
            idx2=-1;
        }
        if(input_xml[i]=="<body>") {
            idx2++;
        }
            if(input_xml[i]=="<topic>") {
                xml_users_topics[idx][idx2].push_back(input_xml[i+1]);
            }
    }
   // string topic="education";
    int flag=0;
    for(int i=0;i<xml_users_topics.size();i++) {
        for(int j=0;j<xml_users_posts[i].size();j++) {
            for(auto k:xml_users_topics[i][j]) {
                if(k.find(topic)!=std::string::npos) {
                    flag=1;
                    size_t pos = k.find(topic);
                    if (pos != string::npos) {
                        // Insert "{" before the target word
                        k.insert(pos, "{");
                        // Insert "}" after the target word
                        k.insert(pos + topic.length() + 1, "}");
                    }
                    TopicsFound.push_back({i,xml_users_posts[i][j]+endl+k});
                   // cout<<i<<endl<<xml_users_posts[i][j]<<endl<<k<<endl;
                }
            }
        }
    }
    return TopicsFound;
}

