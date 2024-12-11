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
    ofstream outputFile( "sample.json");

    string xmlstring;
    vector<user>users;
while(getline(file,xmlstring)) {
    //cout << xmlstring << endl;

    if (xmlstring == "<users>") {
        while (getline(file, xmlstring)) {
            //cout << xmlstring << endl;
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
                            //cout << xmlstring << endl;

                            pos1 = xmlstring.find('<');
                            pos2 = xmlstring.find('>');
                            checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                            if (checkObject == "/posts")break;
                            else if (checkObject == "post") {
                                post post;
                                while (getline(file, xmlstring)) {
                                    //cout << xmlstring << endl;

                                    pos1 = xmlstring.find('<');
                                    pos2 = xmlstring.find('>');
                                    string chechObjTopic = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                    if (chechObjTopic == "/post")break;
                                    else if (chechObjTopic == "body") {
                                        while (getline(file, xmlstring)) {
                                            //cout << xmlstring << endl;

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
                                            //cout << xmlstring << endl;

                                            pos1 = xmlstring.find('<');
                                            pos2 = xmlstring.find('>');
                                            checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                            if (checkObject == "/topics")break;
                                            else if (checkObject == "topic") {
                                                while (getline(file, xmlstring)) {
                                                    //cout << xmlstring << endl;

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
                            //cout << xmlstring << endl;

                            pos1 = xmlstring.find('<');
                            pos2 = xmlstring.find('>');
                            checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                            if (checkObject == "/followers")break;
                            else if (checkObject == "follower") {
                                while (getline(file, xmlstring)) {
                                    //cout << xmlstring << endl;

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

int indentation=0;


outputFile<<"{"<<endl;
indentation++;

int temp=indentation;
    while (temp--)outputFile<<"    ";
    indentation++;
outputFile<<R"("users": [)"<<endl;

    for (int i=0;i<users.size();i++) {
        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<"{"<<endl;
        indentation++;

         temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<R"("id": ")"<<users[i].id<<"\","<<endl;
        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<R"("name": ")"<<users[i].name<<"\","<<endl;
        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<R"("posts": )"<<"["<<endl;
        indentation++;

        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<"{"<<endl;

        indentation++;

        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<R"("post": )"<<"["<<endl;
        indentation++;
            for (int j = 0; j < users[i].posts.size(); ++j) {

                temp=indentation;
                while (temp--)outputFile<<"    ";
            outputFile<<"{"<<endl;
                indentation++;

                temp=indentation;
                while (temp--)outputFile<<"    ";
            outputFile<<R"("body": ")";
           string body= users[i].posts[j].body;
                std::reverse(body.begin(), body.end());
                while(body.back()==' ')body.pop_back();
                std::reverse(body.begin(), body.end());

            outputFile<<body<<"\","<<endl;


                temp=indentation;
                while (temp--)outputFile<<"    ";
            outputFile<<R"("topics": )"<<"["<<endl;
                indentation++;

                temp=indentation;
                while (temp--)outputFile<<"    ";
            outputFile<<"{"<<endl;
                indentation++;

                temp=indentation;
                while (temp--)outputFile<<"    ";
                outputFile<<R"("topic": )";
                if(users[i].posts[j].topics.size()==1) {  outputFile<<"\"";

                    string topic= users[i].posts[j].topics[0];
                    std::reverse(topic.begin(), topic.end());
                    while(topic.back()==' ')topic.pop_back();
                    std::reverse(topic.begin(), topic.end());


                    outputFile<<topic<<"\""<<endl;}
                else{
                    outputFile << "[" << endl;
                indentation++;

            for (int k=0;k<users[i].posts[j].topics.size();k++) {
                temp=indentation;
                while (temp--)outputFile<<"    ";
                outputFile<<"\"";

                string topic= users[i].posts[j].topics[k];
                std::reverse(topic.begin(), topic.end());
                while(topic.back()==' ')topic.pop_back();
                std::reverse(topic.begin(), topic.end());


                outputFile<<topic<<"\"";
                if(k<users[i].posts[j].topics.size()-1)outputFile<<",";
                outputFile<<endl;
            }
                }

                if(users[i].posts[j].topics.size()>1) {  indentation--;
                    temp=indentation;
                    while (temp--)outputFile<<"    ";
                    outputFile << "]" << endl; }
                indentation--;
                temp=indentation;
                while (temp--)outputFile<<"    ";
            outputFile<<"}"<<endl;
                indentation--;
                temp=indentation;
                while (temp--)outputFile<<"    ";
            outputFile<<"]"<<endl;
                indentation--;
                temp=indentation;
                while (temp--)outputFile<<"    ";
            outputFile<<"}";
            if(j<users[i].posts.size()-1)outputFile<<",";
            outputFile<<endl;
        }         indentation--;
        temp=indentation;
        while (temp--)outputFile<<"    ";   outputFile<<"]"<<endl;


        indentation--;
        temp=indentation;
        while (temp--)outputFile<<"    ";

        outputFile<<"}"<<endl;
        indentation--;
        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<"],"<<endl;


        temp=indentation;
        while (temp--)outputFile<<"    ";

        outputFile<<R"("followers": )"<<"["<<endl;
        indentation++;

        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<"{"<<endl;
        indentation++;

        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<R"("follower": )"<<"["<<endl;
        indentation++;


        for (int l=0;l<users[i].followers.size();l++) {
            temp=indentation;
            while (temp--)outputFile<<"    ";
            outputFile<<"{"<<endl;
            indentation++;
            temp=indentation;
            while (temp--)outputFile<<"    ";
            outputFile<<R"("id": ")"<<users[i].followers[l]<<"\""<<endl;
            indentation--;
            temp=indentation;
            while (temp--)outputFile<<"    ";
            outputFile<<"}";
            if(l<users[i].followers.size()-1)outputFile<<",";

            outputFile<<endl;
        }

        indentation--;
        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<"]"<<endl;
        indentation--;
        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<"}"<<endl;
        indentation--;
        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<"]"<<endl;
        indentation--;
        temp=indentation;
        while (temp--)outputFile<<"    ";
        outputFile<<"}";
        if(i<users.size()-1)outputFile<<",";
        outputFile<<endl;
    }
    indentation--;
    temp=indentation;
    while (temp--)outputFile<<"    ";
    outputFile<<"]"<<endl;
    indentation--;
    temp=indentation;
    while (temp--)outputFile<<"    ";
    outputFile<<"}";
    //cout<<"indent"<<indentation;

}
