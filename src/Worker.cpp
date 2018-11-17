#include "Worker.h"
using namespace std;
Worker :: Worker (int pipeFd)
{
    char buff[2048];
    read(pipeFd, buff, 2048);
    close(pipeFd);
    string input = buff;
    vector < string > inputs = Tools :: splitByCharacter(input, '\n');
    int i = 0 ;
    while(inputs[i] != END_OF_FILES)
    {
        files.push_back(inputs[i]);
        i++;
    }
    i++;
    this -> getFilters(inputs[i]);
}
void Worker :: getFilters( string allFilters )
{
    vector <string> filtersStr = Tools :: splitByCharacter(allFilters , '-');
    for (int j = 0 ; j < filtersStr.size() ; j++)
    {
        vector <string> singleFilter = Tools :: splitByCharacter(filtersStr[j], '=');
        pair < string , string > filter;
        filter.first = singleFilter[0];
        filter.second = singleFilter[1];
        filters.push_back(filter); 
    }
}

void Worker :: getFileContents()
{
    bool headerAdded = false;
    for (int i = 0 ; i < files.size() ; i++)
    {
        string line ;
        ifstream file(files[i]);
        getline(file, line);
        if(!headerAdded)
        {
            filesContent.push_back( Tools :: splitByCharacter(line, ' '));
            headerAdded = true;
        }   
        while(getline(file, line))
            filesContent.push_back( Tools :: splitByCharacter(line, ' '));
        file.close();
    }
   
}

void Worker :: filterFileContents()
{
    for(int i = 0 ; i < filters.size() ; i++)
    {
        int j = this -> findFilterIndex(filters[i].first);
    }
}

int Worker :: findFilterIndex(string filterName)
{
    for(int i = 0 ; i < filesContent[0].size() ; i++)
    {
        
    }
}
Worker :: ~Worker()
{

}