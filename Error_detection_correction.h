#ifndef ERROR_DETECTION_CORRECTION_H
#define ERROR_DETECTION_CORRECTION_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;


vector<pair<string, size_t>> extractTags(const string& xmlContent);

vector<pair<string, size_t>> XML_detection(const string& xmlContent);

void saveXMLToFile(const string& fileName, const string& xmlContent);

void XML_correction(vector<pair<string,size_t>> errors, string& xmlContent) ;


#endif //ERROR_DETECTION_CORRECTION_H
