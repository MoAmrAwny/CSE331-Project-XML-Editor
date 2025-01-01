#include "network_analysis.h"

vector<pair<string,int>> MostInfluencer(vector<user> users) {
    int mx=0;
    vector<pair<string,int>>MostInfluencer;
    string user_name;
    for (int i = 0; i < users.size(); i++) {
        if(users[i].followers.size()>mx) {
            mx=users[i].followers.size();
        }

    }
    for(int i=0;i<users.size();i++) {
        if(mx==users[i].followers.size()) {
            MostInfluencer.push_back({users[i].name,users[i].id});
        }

    }
    return MostInfluencer;
}

vector<pair<string,int>> MutualUsers(vector<user>users,vector<string>v) {
    vector<pair<string,int>>Mutual_Users;
    map<int,int>mp; //i.second should contain the number of ids given in the command to be mutual
    for (int i = 0; i < users.size(); i++) {
        auto it=find(v.begin(),v.end(),to_string(users[i].id));
        if(it!=v.end())
            for (int l = 0; l < users[i].followers.size(); l++) {
                mp[users[i].followers[l]]++;
            }
    }
    for(auto i:mp) {
        if(i.second==v.size()) {
            Mutual_Users.push_back({users[i.first].name,users[i.first].id});
        }
    }
    return Mutual_Users;
}

vector<pair<string,int>> MostActive(vector<user>users) {
    map<int,int>mp;
    vector<pair<string,int>>MostActive;
    for (int i = 0; i < users.size(); i++) {
        for (int l = 0; l < users[i].followers.size(); l++) {
            mp[users[i].id]++;
            mp[users[i].followers[l]]++;
        }
    }
    int mx=0;
    for(auto i: mp) {
        if(i.second>mx) {
            mx=i.second;  //4
        }
    }
    for(auto i:mp) {
        if(i.second==mx) {
            MostActive.push_back({users[i.first].name,users[i.first].id});
        }
    }
    return MostActive;
}

vector<pair<string,int>> SuggestFollowers(vector<user>users,string idd) {
    map<int,int>mp;
    // vector<int>id_followers();
    int id=stoi(idd);
    for(int i=0;i<users[id].followers.size();i++) {
        mp[users[id].followers[i]]++;
    }
    vector<pair<string,int>>suggested_users;
    for (int i = 0; i < users[id].followers.size(); i++) {
        int follower_id = users[id].followers[i]; // Get the ID of the current follower
        if (follower_id < users.size()) { // Ensure the ID is valid
            for (int j : users[follower_id].followers) { // Access followers of the follower
                if (mp.find(j) != mp.end()) {
                    continue; // Already in map
                }
                else if(j==id) {
                    continue;
                }
                else {
                    suggested_users.push_back({users[j].name, j}); // Add suggested user
                }
            }
        }
    }
    return suggested_users;
}


