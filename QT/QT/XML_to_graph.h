#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

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


void xmlToGraph_abdo(const string& inputname, const string& outputname);

void visualizeGraph(const string& dotFile, const string& outputFile);
