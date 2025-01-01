#pragma once
#include "../generalHeader.h"
#include "../graphRepresentation/XML_to_graph.h"


vector<pair<string,int>> MostInfluencer(vector<user> users);

vector<pair<string,int>> MutualUsers(vector<user>users,vector<string>v);

vector<pair<string,int>> MostActive(vector<user>users);

vector<pair<string,int>> SuggestFollowers(vector<user>users,string idd);
