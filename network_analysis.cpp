#include "network_analysis.h"



vector<user> xmlToGraph(const string& inputname) {
    ifstream inputfile(inputname);
    // ofstream outputfile("xmlToGraph/files/"+ outputname);
    // outputfile << "digraph test{" << endl;
    string xmlstring;
    vector<user> users(1000);
    while (getline(inputfile, xmlstring)) {
        //cout << xmlstring << endl;

        if (xmlstring == "<users>") {
            while (getline(inputfile, xmlstring)) {
                //cout << xmlstring << endl;
                size_t pos1 = xmlstring.find('<');
                size_t pos2 = xmlstring.find('>');
                if (xmlstring.substr(pos1 + 1, pos2 - pos1 - 1) == "user") {
                    user user;
                    while (getline(inputfile, xmlstring)) {
                        //cout << xmlstring << endl;

                        pos1 = xmlstring.find('<');
                        pos2 = xmlstring.find('>');
                        size_t pos3 = xmlstring.find('/');
                        string checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);

                        if (checkObject == "/user")break;
                        else if (checkObject == "id") {
                            user.id = stoi(xmlstring.substr(pos2 + 1, pos3 - pos2 - 1 - 1));

                        }
                        else if (checkObject == "name") {
                            user.name = xmlstring.substr(pos2 + 1, pos3 - pos2 - 1 - 1);

                        }
                        else if (checkObject == "posts") {
                            while (getline(inputfile, xmlstring)) {
                                //cout << xmlstring << endl;

                                pos1 = xmlstring.find('<');
                                pos2 = xmlstring.find('>');
                                checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                if (checkObject == "/posts")break;
                                else if (checkObject == "post") {
                                    post post;
                                    while (getline(inputfile, xmlstring)) {
                                        //cout << xmlstring << endl;

                                        pos1 = xmlstring.find('<');
                                        pos2 = xmlstring.find('>');
                                        string chechObjTopic = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                        if (chechObjTopic == "/post")break;
                                        else if (chechObjTopic == "body") {
                                            pos3 = xmlstring.find('/');
                                            post.body = xmlstring.substr(pos2 + 1, pos3 - pos2 - 1 - 1);


                                        }
                                        else if (chechObjTopic == "topics") {
                                            while (getline(inputfile, xmlstring)) {
                                                //cout << xmlstring << endl;

                                                pos1 = xmlstring.find('<');
                                                pos2 = xmlstring.find('>');
                                                checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                                if (checkObject == "/topics")break;
                                                else if (checkObject == "topic") {
                                                    pos3 = xmlstring.find('/');
                                                    post.topics.push_back(xmlstring.substr(pos2 + 1, pos3 - pos2 - 1 - 1));
                                                }
                                            }
                                        }
                                    }
                                    user.posts.push_back(post);
                                }
                            }
                        }
                        else if (checkObject == "followers") {
                            while (getline(inputfile, xmlstring)) {
                                //cout << xmlstring << endl;

                                pos1 = xmlstring.find('<');
                                pos2 = xmlstring.find('>');
                                checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                if (checkObject == "/followers")break;
                                else if (checkObject == "follower") {
                                    while (getline(inputfile, xmlstring)) {
                                        //cout << xmlstring << endl;

                                        pos1 = xmlstring.find('<');
                                        pos2 = xmlstring.find('>');
                                        pos3 = xmlstring.find('/');
                                        if (xmlstring.substr(pos1 + 1, pos2 - pos1 - 1) == "/follower") { break; }
                                        user.followers.push_back(stoi(xmlstring.substr(pos2 + 1, pos3 - 1 - 1 - pos2)));
                                    }

                                }
                            }
                        }
                    }
                    users[user.id] = user;
                }
            }
        }
    }
    return users;
}

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
}

vector<pair<string,int>> MutualUsers(vector<user>users,vector<string>v) {
    //vector<string>v={"1","2","3"};
    vector<pair<string,int>>Mutual_Users;
    map<int,int>mp; //i.second should contain the number of ids given in the commend to be mutual
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
        // id_followers().push_back(users[id].followers[i]);
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


