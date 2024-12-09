#include <fstream>
#include <bits/stdc++.h>
using namespace std;

class post{
public:
    string body;
    vector<string>topics;
};
class user{
public:
    int id;
    string name;
    vector<post>posts;
    vector<int>followers;
    user(){
        id=0;
        name="";
    }
};



int main() {

    ifstream file( "sample.xml");

    string xmlstring;
    vector<user>users;
while(getline(file,xmlstring)) {
    cout << xmlstring << endl;

    if (xmlstring == "<users>") {
        while (getline(file, xmlstring)) {

            size_t pos1 = xmlstring.find('<');
            size_t pos2 = xmlstring.find('>');
            if (xmlstring.substr(pos1 + 1, pos2 - pos1 - 1) == "user") {
                user user;
                while (getline(file, xmlstring)) {
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
                        while (getline(file, xmlstring)) {
                            cout << xmlstring << endl;

                            pos1 = xmlstring.find('<');
                            pos2 = xmlstring.find('>');
                            checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                            if (checkObject == "/posts")break;
                            else if (checkObject == "post") {
                                post post;
                                while (getline(file, xmlstring)) {
                                    cout << xmlstring << endl;

                                    pos1 = xmlstring.find('<');
                                    pos2 = xmlstring.find('>');
                                    string chechObjTopic = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                    if (chechObjTopic == "/post")break;
                                    else if (chechObjTopic == "body") {
                                        while (getline(file, xmlstring)) {
                                            cout << xmlstring << endl;

                                            pos1 = xmlstring.find('<');
                                            pos2 = xmlstring.find('>');
                                            checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                            if (checkObject == "/body")break;
                                            else {
                                                post.body = xmlstring;
                                            }
                                        }
                                    } else if (chechObjTopic == "topics") {
                                        while (getline(file, xmlstring)) {
                                            cout << xmlstring << endl;

                                            pos1 = xmlstring.find('<');
                                            pos2 = xmlstring.find('>');
                                            checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                            if (checkObject == "/topics")break;
                                            else if (checkObject == "topic") {
                                                while (getline(file, xmlstring)) {
                                                    cout << xmlstring << endl;

                                                    pos1 = xmlstring.find('<');
                                                    pos2 = xmlstring.find('>');
                                                    checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                                    if (checkObject == "/topic")break;
                                                    post.topics.push_back(xmlstring);
                                                }
                                            }
                                        }
                                    }
                                }
                                user.posts.push_back(post);

                            }
                        }
                    } else if (checkObject == "followers") {
                        while (getline(file, xmlstring)) {
                            cout << xmlstring << endl;

                            pos1 = xmlstring.find('<');
                            pos2 = xmlstring.find('>');
                            checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                            if (checkObject == "/followers")break;
                            else if (checkObject == "follower") {
                                while (getline(file, xmlstring)) {
                                    cout << xmlstring << endl;

                                    pos1 = xmlstring.find('<');
                                    pos2 = xmlstring.find('>');
                                    pos3 = xmlstring.find('/');
                                    if (xmlstring.substr(pos1 + 1, pos2-pos1-1) == "/follower") { break; }
                                    user.followers.push_back(stoi(xmlstring.substr(pos2 + 1, pos3 - 1 - 1 - pos2)));
                                }

                            }
                        }
                    }
                }
                users.push_back(user);

            }
        }
    }
}
cout<<"{"<<endl;
cout<<R"("users": [)"<<endl;

    for (int i=0;i<users.size();i++) {
        cout<<"{"<<endl;
        cout<<R"("id": ")"<<users[i].id<<"\","<<endl;
        cout<<R"("name": ")"<<users[i].name<<"\","<<endl;
        cout<<R"("posts": )"<<"["<<endl;
        cout<<"{"<<endl;


        cout<<R"("post": )"<<"["<<endl;

            for (int j = 0; j < users[i].posts.size(); ++j) {


            cout<<"{"<<endl;
            cout<<R"("body": ")";
           string body= users[i].posts[j].body;
                std::reverse(body.begin(), body.end());
                while(body.back()==' ')body.pop_back();
                std::reverse(body.begin(), body.end());

            cout<<body<<"\","<<endl;
            cout<<R"("topics": )"<<"["<<endl;

            cout<<"{"<<endl;
                cout<<R"("topic": )";
                if(users[i].posts[j].topics.size()>1)cout<<"["<<endl;

            for (int k=0;k<users[i].posts[j].topics.size();k++) {
                cout<<"\"";

                string topic= users[i].posts[j].topics[k];
                std::reverse(topic.begin(), topic.end());
                while(topic.back()==' ')topic.pop_back();
                std::reverse(topic.begin(), topic.end());

                cout<<topic<<"\"";
                if(k<users[i].posts[j].topics.size()-1)cout<<",";
                cout<<endl;
            }
                if(users[i].posts[j].topics.size()>1)cout<<"]"<<endl;

            cout<<"}"<<endl;
            cout<<"]"<<endl;
            cout<<"}";
            if(j<users[i].posts.size()-1)cout<<",";
            cout<<endl;
        }            cout<<"]"<<endl;




        cout<<"}"<<endl;
        cout<<"],"<<endl;




        cout<<R"("followers": )"<<"["<<endl;
        cout<<"{"<<endl;
        cout<<R"("follower": )"<<"["<<endl;
        for (int l=0;l<users[i].followers.size();l++) {
            cout<<"{"<<endl;
            cout<<R"("id": ")"<<users[i].followers[l]<<"\""<<endl;
            cout<<"}";
            if(l<users[i].followers.size()-1)cout<<",";
            cout<<endl;
        }cout<<"]"<<endl;
        cout<<"}"<<endl;
        cout<<"]"<<endl;
        cout<<"}";
        if(i<users.size()-1)cout<<",";
        cout<<endl;
    }
    cout<<"]"<<endl;
    cout<<"}";
    ofstream outputFile( "sample.json");

}
