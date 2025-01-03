#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
#include "XML_to_graph.h"
// class post {
// public:
//     string body;
//     vector<string>topics;
// };
// class user {
// public:
//     int id;
//     string name;
//     vector<post>posts;
//     vector<int>followers;
//     user();
// };


vector<user> xmlToGraph(const string& inputname);
vector<pair<string,int>> MostInfluencer(vector<user> users);

vector<pair<string,int>> MutualUsers(vector<user>users,vector<string>v);

vector<pair<string,int>> MostActive(vector<user>users);

vector<pair<string,int>> SuggestFollowers(vector<user>users,string idd);
