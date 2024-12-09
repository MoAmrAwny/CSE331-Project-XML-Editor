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
//    // Printing the token vector
//    for(int i = 0; i < xml.size(); i++)
//       cout << xml[i] << '\n';
//    for(int i = 0; i < xml.size(); i++) {
    for (const user& u:users) {
        cout<<"userrrrrrrrrrrrrrrrr"<<endl;
        cout<<u.id<<endl<<u.name<<endl;
        for (int f:u.followers) {
            cout<<f<<endl;
        } for (const post& p:u.posts) {
            cout<<p.body<<endl;
            for (string s:p.topics) {
                cout<<s<<endl;
            }
        }
        cout<<endl;
    }












//    stack<string>brackets;
//    vector<string> xml,json;
//    string xml1,temp;
//    //cin >> xml1;
////xml.push_back("");
////xml[0]+"";
////xml[0].push_back('{');
//xml1="<users><user><id>1</id><name>Ahmed Ali</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>economy</topic><topic>finance</topic></topics></post><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>solar_energy</topic></topics></post></posts><followers><follower><id>2</id></follower><follower><id>3</id></follower></followers></user><user><id>2</id><name>Yasser Ahmed</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>education</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user><user><id>3</id><name>Mohamed Sherif</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>sports</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user></users>"; json.push_back("{");
//    ifstream file( "sample.xml");
///*separate xml1 to vector of strings*/
//    // stringstream class check1
////    stringstream check1(xml1);
////    string intermediate;
////    // Tokenizing w.r.t. '>'
////    while(getline(check1, intermediate, '>'))
////    {
////        xml.push_back(intermediate);
////    }
//    string xmlstring;
//while(file>>xmlstring){
//    xml.push_back(xmlstring);
//}
//    // Printing the token vector
//    for(int i = 0; i < xml.size(); i++)
//       cout << xml[i] << '\n';
//    for(int i = 0; i < xml.size(); i++) {
//
//    }
//    for (int i = 0; i < xml.size(); ++i) {
//if (xml[i][0]=='<'){ //if object
//if(!brackets.empty()&&xml[i][1]=='/') {
//    json.push_back(brackets.top());
//    brackets.pop();
//    json.push_back(brackets.top());
//    brackets.pop();}
//else {         string str=xml[i].substr(1);
//    if(str==temp) { string s1=json[json.size() - 1];
//        json[json.size() - 1]="[";
//        size_t pos = s1.find(':'); //if sentence
//string a=s1.substr(0,pos+1);
//json.push_back(a);
//        json.push_back(s1.substr(pos+2)+",");
//         pos = xml[i+1].find('<'); //if sentence
//         str=xml[i+1].substr(0,pos);
//        json.push_back("\"" + str + "\"");
//        json.push_back("]");i++;}
//   else{ temp=str;
//    json.push_back("\""+str+"\": ");
//    if(xml[i+1][0]=='<') {
//        json.push_back("[");
//        json.push_back("{");
//        brackets.push("]");
//        brackets.push("}");
//    }
//   }
//}
//}else { size_t pos = xml[i].find('<'); //if sentence
//    string str=xml[i].substr(0,pos);
//    json[json.size()-1]+=("\"" + str + "\"");
//    //brackets.push(",");
//}
//    }
//
//
//    json.push_back("}");
//
//    for (string j:json) {
//        cout<<j<<endl;
//    }
//    cout<<brackets.empty();
}
