#include "Tools.h"
#include <iostream>
using namespace std;
vector<string> Tools :: splitByCharacter (string line, char character)
{
	vector<string> output;
	bool there_is_char = Tools :: doesStringContainsChar(line, character);
	while(there_is_char == true)
	{
		int characterPosition = line.find(character);
		string subString = line.substr(0,characterPosition);
		string newLine = line.substr(characterPosition+1);
		line = newLine;
		if(subString != EMPTY_STRING)
			output.push_back(subString);
		there_is_char = (line.find(character) != string::npos);
	} 
	if(line != EMPTY_STRING)
		output.push_back(line);
	return output;
}
bool Tools :: doesStringContainsChar(string line, char character)
{
	size_t found = line.find(character);
	return (found != string::npos);
}

string Tools :: removeAllSpaces(string line)
{
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	return line;
}

bool Tools :: compare(string first, string second)
{
	bool res; 
	if(isNumber(first))
		return stoi(first) < stoi(second);
	return first < second;
}
bool Tools :: isNumber(string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
int Tools :: findSortValueIndex(vector < string > workerDetails, string sortValue)
{
    cerr << sortValue << "#"<<endl;
    for(int i = 0 ; i < workerDetails.size() ; i++)
    {
        cerr << workerDetails[i] << "*" << endl;
        if(workerDetails[i] == sortValue)
            return i;
    }
    cerr << endl;
    return -1;
}
