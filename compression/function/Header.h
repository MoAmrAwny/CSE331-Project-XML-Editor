#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>


using namespace std;
//Compression and decrompression using LZW algorithm
vector<unsigned short int> compress(vector<char> uncompressed_file);

vector<char> decompress(vector<unsigned short> compressed_file);

vector<char> parse_xml(vector<string>& command);
vector<unsigned short> parse_comp(vector<string>& command);

void save_compressed_file(const vector<unsigned short>& compressed_data, const string& filename);

void save_decompressed_xml(vector<char> decmpressed_file, const std::string& filename);
void comp_decomp_mode(vector<string> command);
//bool check_error(vector<string>& command);
vector<string> get_command(void);

