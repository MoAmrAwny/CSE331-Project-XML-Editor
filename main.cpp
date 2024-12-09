#include <fstream>
#include <bits/stdc++.h>
using namespace std;
int main() {
    stack<string>brackets;
    vector<string> xml,json;
    string xml1,temp;
    //cin >> xml1;
//xml.push_back("");
//xml[0]+"";
//xml[0].push_back('{');
xml1="<users><user><id>1</id><name>Ahmed Ali</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>economy</topic><topic>finance</topic></topics></post><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>solar_energy</topic></topics></post></posts><followers><follower><id>2</id></follower><follower><id>3</id></follower></followers></user><user><id>2</id><name>Yasser Ahmed</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>education</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user><user><id>3</id><name>Mohamed Sherif</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>sports</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user></users>"; json.push_back("{");
    /*separate xml1 to vector of strings*/
    // stringstream class check1
    stringstream check1(xml1);
    string intermediate;
    // Tokenizing w.r.t. '>'
    while(getline(check1, intermediate, '>'))
    {
        xml.push_back(intermediate);
    }

    // Printing the token vector
    for(int i = 0; i < xml.size(); i++)
       cout << xml[i] << '\n';

    for (int i = 0; i < xml.size(); ++i) {
if (xml[i][0]=='<'){ //if object
if(!brackets.empty()&&xml[i][1]=='/') {
    json.push_back(brackets.top());
    brackets.pop();
    json.push_back(brackets.top());
    brackets.pop();}
else {         string str=xml[i].substr(1);
    if(str==temp) { string s1=json[json.size() - 1];
        json[json.size() - 1]="[";
        size_t pos = s1.find(':'); //if sentence
string a=s1.substr(0,pos+1);
json.push_back(a);
        json.push_back(s1.substr(pos+2)+",");
         pos = xml[i+1].find('<'); //if sentence
         str=xml[i+1].substr(0,pos);
        json.push_back("\"" + str + "\"");
        json.push_back("]");i++;}
   else{ temp=str;
    json.push_back("\""+str+"\": ");
    if(xml[i+1][0]=='<') {
        json.push_back("[");
        json.push_back("{");
        brackets.push("]");
        brackets.push("}");
    }
   }
}
}else { size_t pos = xml[i].find('<'); //if sentence
    string str=xml[i].substr(0,pos);
    json[json.size()-1]+=("\"" + str + "\"");
    //brackets.push(",");
}
    }


    json.push_back("}");

    for (string j:json) {
        cout<<j<<endl;
    }
    cout<<brackets.empty();
}
