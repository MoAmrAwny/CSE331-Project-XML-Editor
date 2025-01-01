//
// Created by Jana Aly on 12/27/2024.
//
#include <iostream>
#include <bits/stdc++.h>
#define endl "\n"
#include <fstream>
using namespace std;

class XmlNode {
public:
    string name;                   // Name of the node
    string value;                  // Value of the node (text content)
    vector<XmlNode*> children;      // Child nodes multiple children is possible
};

//helper functions
void debug_tree(XmlNode* node, int level);

string trim(const std::string& str);
//parsing xml into tree structure
XmlNode* parse_node(const vector<string>& s, int& idx);

void print_node(XmlNode* node, ostringstream& out, int level);

vector<string> ReadXml(ifstream& filename);

void PrettifyXML(vector<string> input_xml,ofstream &outputFile);
