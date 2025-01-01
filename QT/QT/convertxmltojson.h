
#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

void indentate(int indentation, ofstream &outputFile);
void closeTag(string &jsonString,stack<char>&st);
void arrayTag(string tagName,string &jsonString,stack<char>&st);
void sentencearrayTag(string tagName, string sentence,string &jsonString,stack<char>&st) ;
void sentenceTag(string tagName, string sentence,string &jsonString);
void normalTag(string tagName,string &jsonString,stack<char>&st);
void justsentence(string sentence,string &jsonString);
void convertXMLtoJSON(ifstream &file, ofstream &outputFile );
void couthamada();