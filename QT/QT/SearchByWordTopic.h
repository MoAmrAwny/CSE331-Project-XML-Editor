//
// Created by Jana Aly on 12/29/2024.
//
#include <iostream>
#include <bits/stdc++.h>
#define endl "\n"
#include <fstream>
using namespace std;

// class XmlNode {
// public:
//     string name;                   // Name of the node
//     string value;                  // Value of the node (text content)
//     vector<XmlNode*> children;      // Child nodes multiple children is possible
// };

//helper functions
// void debug_tree(XmlNode* node, int level);

string trim(const std::string& str);

// XmlNode* parse_node(const vector<string>& s, int& idx);

vector<pair<int,string>> SearchByWord(vector<string>input_xml,string word);

vector<string> ReadXmlToTree(ifstream &in);

vector<pair<int,string>> SearchByTopic(vector<string>input_xml,string topic);

