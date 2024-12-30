
#include"XML_to_graph.h"

user::user() {
        id = 0;
        name = "";
}

void xmlToGraph(const string& inputname, const string& outputname) {
    ifstream inputfile(inputname);
    ofstream outputfile(outputname);


    outputfile << "digraph test{" << endl;
    string xmlstring;
    vector<user> users(100);
    while (getline(inputfile, xmlstring)) {

        if (xmlstring == "<users>") {
            while (getline(inputfile, xmlstring)) {
                
                size_t pos1 = xmlstring.find('<');
                size_t pos2 = xmlstring.find('>');
                if (xmlstring.substr(pos1 + 1, pos2 - pos1 - 1) == "user") {
                    user user;
                    while (getline(inputfile, xmlstring)) {
                        

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
                                

                                pos1 = xmlstring.find('<');
                                pos2 = xmlstring.find('>');
                                checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                if (checkObject == "/posts")break;
                                else if (checkObject == "post") {
                                    post post;
                                    while (getline(inputfile, xmlstring)) {
                                       

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
                               

                                pos1 = xmlstring.find('<');
                                pos2 = xmlstring.find('>');
                                checkObject = xmlstring.substr(pos1 + 1, pos2 - pos1 - 1);
                                if (checkObject == "/followers")break;
                                else if (checkObject == "follower") {
                                    while (getline(inputfile, xmlstring)) {
                                    

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
    for (int i = 0; i < users.size(); i++) {
        for (int l = 0; l < users[i].followers.size(); l++) {
            outputfile << "\"" << users[i].name << "\"" << " -> " << "\"" << users[users[i].followers[l]].name << "\"" << endl;
        }
    }
    outputfile << "}";
    outputfile.close();
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

