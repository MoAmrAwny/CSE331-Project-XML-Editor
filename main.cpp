#include "SearchByWordTopic.h"
int main()
{
    vector<string>command(6);
    ifstream in(command[5]);
    if(command[1]=="search") {
        if(command[2]=="-w") {
            vector<pair<int,string>> WordsFound=SearchByWord(ReadXmlToTree(in),command[3]);
            for(auto i:WordsFound) {
            }
        }
        else if(command[2]=="-t") {
            vector<pair<int,string>> TopicsFound=SearchByTopic(ReadXmlToTree(in),command[3]);
        }
    }
    return 0;
}
