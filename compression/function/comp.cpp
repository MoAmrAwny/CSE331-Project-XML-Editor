#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"Header.h"

using namespace std;

class my_pair {
private:
	string seq;
	unsigned short int key;
public:
	my_pair(string seq, unsigned short int key) {
		this->key = key;
		this->seq = seq;
	}
	string get_seq(void) {
		return this->seq;
	}
	unsigned short int get_key(void) {
		return this->key;
	}
};
class dictionary {
private:
	vector<my_pair> dict;
public:
	dictionary() {
		for (int i = 0; i < 256; i++) {

			string s(1, static_cast<char>(i));

			this->dict.push_back(my_pair(s, static_cast<unsigned short int>(i))); // Add the pair to the dictionary
		}

	}

	size_t get_size(void) {
		return dict.size();
	}
	string get_seq(unsigned short code) {
		for (int i = 0; i < dict.size(); i++)
		{
			if (dict[i].get_key() == code) {
				return dict[i].get_seq();
			}
		}
	}
	void add_to_dict(string s) {
		dict.push_back(my_pair(s, dict.back().get_key() + 1));
	}

	unsigned short int get_code(string s) {
		for (int i = 0; i < dict.size(); i++)
		{
			if (dict[i].get_seq() == s) {
				return dict[i].get_key();
			}
		}
	}
	bool exists(string s) {
		for (int i = 0; i < dict.size(); i++)
		{
			if (dict[i].get_seq() == s) {
				return 1;
			}
		}
		return 0;
	}

};



//Compression and decrompression using LZW algorithm
vector<unsigned short int> compress(vector<char> uncompressed_file)
{
	dictionary x;
	vector<unsigned short int> compressed_file;

	string s = ""; // string

	for (size_t i = 0; i < uncompressed_file.size(); i++)
	{
		char c = uncompressed_file[i];
		string new_s = s + c;  // concatenate the current string with the new character

		if (x.exists(new_s)) {
			// if the sequence exists in the dictionary, extend the string
			s = new_s;
		}
		else {
			// if the sequence doesn't exist in the dictionary, output the code for the current string
			compressed_file.push_back(x.get_code(s));

			// add the new sequence (s + c) to the dictionary
			x.add_to_dict(new_s);

			// start a new string starting with the current character
			s = string(1, c);
		}
	}
	if (!s.empty()) {
		compressed_file.push_back(x.get_code(s));
	}

	return compressed_file;
}
vector<char> decompress(vector<unsigned short> compressed_file) {
	dictionary x;
	vector<char> decompressed_file;
	string s = "";

	for (size_t i = 0; i < compressed_file.size(); i++) {
		unsigned short k = compressed_file[i];

		if (k > x.get_size()) {
			cout << "corrupted file\n";
			return{};
		}

		string sequence;
		if (k == x.get_size() && !s.empty()) {
			sequence = s + s[0];
		}
		else {
			sequence = x.get_seq(k);
			//x.add_to_dict(s + x.get_seq(k));
		}

		decompressed_file.insert(decompressed_file.end(), sequence.begin(), sequence.end());
		if (!s.empty()) {
			x.add_to_dict(s + sequence[0]);
		}
		s = sequence;
	}
	return decompressed_file;
}

vector<char> parse_xml(const string& file_name) {
	// specify the file path
	string filepath = "compression/files/" + file_name;

	ifstream file(filepath, ios::binary);
	if (!file) {
		cerr << "error: cannot open file " << filepath << endl;
	}
	vector<char> filecontent((istreambuf_iterator<char>(file)),
		istreambuf_iterator<char>());
	file.close();

	if (filecontent.size() >= 3 &&
		static_cast<unsigned char>(filecontent[0]) == 0xef &&
		static_cast<unsigned char>(filecontent[1]) == 0xbb &&
		static_cast<unsigned char>(filecontent[2]) == 0xbf) {
		// remove the bom by erasing the first three characters
		filecontent.erase(filecontent.begin(), filecontent.begin() + 3);
	}
	return filecontent;
}
vector<unsigned short> parse_comp(const string& file_name) {
	// specify the file path
	string filepath = "compression/files/" + file_name;

	ifstream inputfile(filepath, ios::binary);
	if (!inputfile) {
		cerr << "error: cannot open file " << filepath << endl;
	}
	vector<unsigned short> data;

	// read the file as unsigned short integers
	unsigned short value;
	while (inputfile.read(reinterpret_cast<char*>(&value), sizeof(unsigned short))) {
		data.push_back(value);
	}
	inputfile.close();
	return data;
}

void save_compressed_file(const vector<unsigned short>& compressed_data, const string& filename) {
	ofstream out_file("compression/files/" +filename, ios::binary);

	if (!out_file) {
		cerr << "error: unable to open file for writing!" << endl;
		return;
	}

	for (unsigned short code : compressed_data) {
		out_file.write(reinterpret_cast<const char*>(&code), sizeof(code));
	}

	out_file.close();
}
void save_decompressed_xml(vector<char> decmpressed_file, const std::string& filename) {

	// open a file in write mode
	std::ofstream outfile("compression/files/" + filename);

	// check if the file is open
	if (!outfile.is_open()) {
		cerr << "failed to open the file for writing: " << filename << endl;
		return;
	}
	// write the vector contents
	for (size_t i = 0; i < decmpressed_file.size(); ++i) {
		outfile << decmpressed_file[i];  // output character as integer (ascii value)	
	}

	// close the file
	outfile.close();

}

vector<string> get_command(void) {
	cout << "please enter command\n";

	vector<string> command(7);

	for (int i = 0; i < command.size(); i++)
	{
		cin >> command[i];
	}
	return command;
}

void comp_decomp_mode(vector<string> command) {
	if (command[1] == "compress") {
		vector<char> filecontent = parse_xml(command[3]);
		vector<unsigned short int> filecompressed = compress(filecontent);
		save_compressed_file(filecompressed, command[5]);
		cout << "compressed successfully";
	}
	else if (command[1] == "decompress") {
		vector<unsigned short> data = parse_comp(command[3]);
		vector<char> decompressedfile = decompress(data);
		save_decompressed_xml(decompressedfile,command[5]);
		cout << "decompressed successfully";
	}
}
