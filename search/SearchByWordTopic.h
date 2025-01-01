#pragma once
#include"../pretty/PrettifyXml.h"
#include "../generalHeader.h"

using namespace std;

vector<pair<int,string>> SearchByWord(vector<string>input_xml,string word);

vector<string> ReadXmlToTree(ifstream &in);

vector<pair<int,string>> SearchByTopic(vector<string>input_xml,string topic);

