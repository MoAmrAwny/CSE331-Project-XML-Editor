#include "compression/function/comp.h"
#include "pretty/PrettifyXml.h"
#include "json/convertxmltojson.h"
#include "mini/Minifying.h"
#include "network/network_analysis.h"
#include "search/SearchByWordTopic.h"
#include "errorHandling/ErrorHandling.h"
#include "graphRepresentation/XML_to_graph.h"
#include "generalHeader.h"


vector<string> get_command() {
	cout << "please enter command\n";

	vector <string> command;
	string str;
	getline(cin, str);
	istringstream iss(str);
	string word;
	while (iss >> word) {
		command.push_back(word);
	}
	return command;
}

int main() {

	vector<string> command = get_command();


	ifstream file(command[3]);
	

	if (command[1] == "compress") {
		compress(command[3], command[5]);
	}

	else if (command[1] == "decompress") {
		decompress(command[3], command[5]);
	}

	else if (command[1] == "format"){
		ofstream outputFile(command[5]);
		PrettifyXML(ReadXml(file), outputFile);
	}
	else if (command[1] == "mini") {
		minifying(command[3], command[5]);
	}

	else if (command[1] == "json") {
		ofstream outputFile(command[5]);
		ofstream outputFile1("prettified");
		PrettifyXML(ReadXml(file), outputFile1);

		ifstream file1("prettified");
		
		convertXMLtoJSON(file1, outputFile);
		cout << "XML file converted successfully";
	}
	else if (command[1] == "verify") {

		ofstream outputFile(command[6]);
		error_handling(file, outputFile);

	}else if(command[1] == "draw"){
        dotFileInput(xmlToGraph(command[3]),"dotFile");
        visualizeGraph("dotFile",command[5]);
    }
	else if (command[1] == "suggest") {
		vector<user> users = xmlToGraph(command[3]);
		vector<pair<string, int>> suggestedFollowers = SuggestFollowers(users, command[5]);

		if (suggestedFollowers.empty()) {
			cout << "No Followers To Suggest!" << endl;
		}
		else {
			cout << "Name" << " " << "id" << endl;
			for (auto i : suggestedFollowers) {
				cout << i.first << " " << i.second << endl;
			}
		}
		
	}
	else if (command[1] == "most_influencer") {
		vector<user> users = xmlToGraph(command[3]);
		vector<pair<string, int>>mostInfluencer = MostInfluencer(users);
		cout << "Name" << " " << "id" << endl;
		for (auto i : mostInfluencer) {
			cout << i.first << " " << i.second << endl;
		}
	}
	else if (command[1] == "most_active") {
		vector<user> users = xmlToGraph(command[3]);
		vector<pair<string, int>> Active_Users = MostActive(users);

		cout << "Name" << " " << "id" << endl;
		for (auto i : Active_Users) {
			cout << i.first << " " << i.second << endl;
		}
	}
	else if (command[1] == "mutual") {

		vector<user> users = xmlToGraph(command[3]);
		vector<string>ids;
		stringstream ss(command[5]);
		string token;
		while (getline(ss, token, ',')) {
			ids.push_back(token);
		}
		vector<pair<string, int>> Mutual_Users = MutualUsers(users, ids);
		if (Mutual_Users.empty()) {
			cout << "No Mutual Found!" << endl;
		}
		else {
			cout << "Name" << " " << "id" << endl;
			for (auto i : Mutual_Users) {
				cout << i.first << " " << i.second << endl;
			}
		}
	}
	else if (command[1] == "search") {
		ifstream in(command[5]);
		if (command[2] == "-w") {
			vector<pair<int, string>> WordsFound = SearchByWord(ReadXmlToTree(in), command[3]);
			if (WordsFound.empty()) {
				cout << "No Words Found!" << endl;
			}
			else {
				cout << "ID:" << " " << "Post where the word is mentioned:" << endl;
				for (auto i : WordsFound) {
					cout << i.first << " " << i.second << endl;
				}
			}
		}
		else if (command[2] == "-t") {
			vector<pair<int, string>> TopicsFound = SearchByTopic(ReadXmlToTree(in), command[3]);
			if (TopicsFound.empty()) {
				cout << "No Topics Found!" << endl;
			}
			else {
				cout << "ID:" << " " << "Post where the topic is mentioned:" << endl;
				for (auto i : TopicsFound) {
					cout << i.first << " " << i.second << endl;
				}
			}
		}
	}
	else {
		cout << "Invalid command";
		return 1;
	}
		

	return 0;
}




//part1

//xml_editor json -i input_file.xml -o output_file_json.json

//xml_editor mini -i input_file.xml -o output_file_minified.xml

//xml_editor compress -i input_file.xml -o output_file_compressed.comp

//xml_editor decompress -i output_file_compressed.comp -o output_file_decompressed.xml

//xml_editor format -i inputPrettify.xml -o output_file_prettified.xml

//xml_editor verify -i inputErrorHandling.xml -f -o output_file_without_errors.xml



//part2

//xml_editor draw -i inputNetworkAnalysis.xml -o output_file_graphviz.jpg

//xml_editor suggest -i inputNetworkAnalysis.xml -id 1

//xml_editor most_influencer -i inputNetworkAnalysis.xml

//xml_editor mutual -i inputNetworkAnalysis.xml -ids 1,2

//xml_editor mutual -i inputNetworkAnalysis.xml -ids 1,2,3

//xml_editor most_active -i inputNetworkAnalysis.xml

//xml_editor search -w word -i inputNetworkAnalysis.xml

//xml_editor search -t topic -i inputNetworkAnalysis.xml

//xml_editor search -w lorem -i inputNetworkAnalysis.xml

//xml_editor search -t economy -i inputNetworkAnalysis.xml

