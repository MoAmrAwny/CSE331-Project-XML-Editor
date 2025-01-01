#pragma once
#include "../generalHeader.h"

class post {
public:
    string body;
    vector<string>topics;
};
class user {
public:
    int id;
    string name;
    vector<post>posts;
    vector<int>followers;
    user();
};
vector<user> xmlToGraph(const string& inputName); //convert xml file to adjacency list
void dotFileInput( vector<user>users,const string& outputName);
void visualizeGraph(const string& dotFile, const string& outputFile);