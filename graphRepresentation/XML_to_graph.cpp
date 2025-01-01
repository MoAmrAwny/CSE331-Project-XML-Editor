
#include"XML_to_graph.h"

user::user() {
        id = 0;
        name = "";
}
// the following function parses the xml line by line to extract the data of the social network and returns a vector of users
// where every user has a name, id, vector of integers representing followers ids, vector of posts and each post has a body and a vector of strings representing topics
//after getting all the data we input the undirected graph between all users and use the file to visualize the graph using graphviz
vector<user> xmlToGraph(const string& inputName) {
    ifstream inputFile(inputName);
    string XML_String;
    vector<user> users(100);
    while (getline(inputFile, XML_String)) {

        if (XML_String == "<users>") {
            while (getline(inputFile, XML_String)) {
                
                size_t pos1 = XML_String.find('<');
                size_t pos2 = XML_String.find('>');
                if (XML_String.substr(pos1 + 1, pos2 - pos1 - 1) == "user") {
                    user user;
                    while (getline(inputFile, XML_String)) {
                        

                        pos1 = XML_String.find('<');
                        pos2 = XML_String.find('>');
                        size_t pos3 = XML_String.find('/');
                        string checkObject = XML_String.substr(pos1 + 1, pos2 - pos1 - 1);

                        if (checkObject == "/user")break;
                        else if (checkObject == "id") {
                            user.id = stoi(XML_String.substr(pos2 + 1, pos3 - pos2 - 1 - 1));

                        }
                        else if (checkObject == "name") {
                            user.name = XML_String.substr(pos2 + 1, pos3 - pos2 - 1 - 1);
                        }
                        else if (checkObject == "posts") {
                            while (getline(inputFile, XML_String)) {
                                

                                pos1 = XML_String.find('<');
                                pos2 = XML_String.find('>');
                                checkObject = XML_String.substr(pos1 + 1, pos2 - pos1 - 1);
                                if (checkObject == "/posts")break;
                                else if (checkObject == "post") {
                                    post post;
                                    while (getline(inputFile, XML_String)) {
                                       

                                        pos1 = XML_String.find('<');
                                        pos2 = XML_String.find('>');
                                        string checkObjTopic = XML_String.substr(pos1 + 1, pos2 - pos1 - 1);
                                        if (checkObjTopic == "/post")break;
                                        else if (checkObjTopic == "body") {
                                            pos3 = XML_String.find('/');
                                            post.body = XML_String.substr(pos2 + 1, pos3 - pos2 - 1 - 1);


                                        }
                                        else if (checkObjTopic == "topics") {
                                            while (getline(inputFile, XML_String)) {
                                             

                                                pos1 = XML_String.find('<');
                                                pos2 = XML_String.find('>');
                                                checkObject = XML_String.substr(pos1 + 1, pos2 - pos1 - 1);
                                                if (checkObject == "/topics")break;
                                                else if (checkObject == "topic") {
                                                    pos3 = XML_String.find('/');
                                                    post.topics.push_back(XML_String.substr(pos2 + 1, pos3 - pos2 - 1 - 1));
                                                }
                                            }
                                        }
                                    }
                                    user.posts.push_back(post);
                                }
                            }
                        }
                        else if (checkObject == "followers") {
                            while (getline(inputFile, XML_String)) {
                               

                                pos1 = XML_String.find('<');
                                pos2 = XML_String.find('>');
                                checkObject = XML_String.substr(pos1 + 1, pos2 - pos1 - 1);
                                if (checkObject == "/followers")break;
                                else if (checkObject == "follower") {
                                    while (getline(inputFile, XML_String)) {
                                    

                                        pos1 = XML_String.find('<');
                                        pos2 = XML_String.find('>');
                                        pos3 = XML_String.find('/');
                                        if (XML_String.substr(pos1 + 1, pos2 - pos1 - 1) == "/follower") { break; }
                                        user.followers.push_back(stoi(XML_String.substr(pos2 + 1, pos3 - 1 - 1 - pos2)));
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

void dotFileInput( vector<user>users,const string& outputName){
     ofstream outputFile(outputName);
    outputFile << "digraph test{" << endl;
    for (int i = 0; i < users.size(); i++) {
        for (int l = 0; l < users[i].followers.size(); l++) {
            outputFile << "\"" << users[i].name << "\"" << " -> " << "\"" << users[users[i].followers[l]].name << "\"" << endl;
        }
    }
    outputFile << "}";
    outputFile.close();
}

void visualizeGraph(const string& dotFile, const string& outputFile) {
    

    string command = "dot -Tjpg " + dotFile + " -o " + outputFile;
    if (system(command.c_str()) == 0) {
        cout << "Graph visualized: " << outputFile << endl;
    }
    else {
        cerr << "Error visualizing graph." << endl;
    }
}

