#include "LoadBalancer.h"
#include "Tools.h"
#include <iostream>
using namespace std;


LoadBalancer :: LoadBalancer (string command)
{
    filesCount = 0;
    command = Tools :: removeAllSpaces(command);
    vector < string > configs =  Tools :: splitByCharacter(command , '-');
    for (int i = 0 ; i < configs.size() ; i++)
    {
        vector< string > config = Tools :: splitByCharacter(configs[i], '=');
        if(config[0] == PROCESS_COUNT)
            processCount = stoi(config[1]);
        else if(config[0] == DIRECTORY)
            filesDirectory = config[1];
        else if(config[1] == ASCEND || config[1] == DESCEND)
        {
            sortOrNot = true;
            sortValue.first = config[0];
            sortValue.second = config[1];
        }
        else 
        {
            pair < string, string > filter;
            filter.first = config[0];
            filter.second = config[1];
            filters.push_back(filter);
        }
    }
    this -> setFiles();
    // cerr << processCount << endl;
    // cerr << filesDirectory << endl;
    // for(int i = 0  ; i < filters.size() ; i++)
    //     cerr << filters[i].first << "  " << filters[i].second << endl;
    // cerr << sortOrNot << endl;
    // cerr << sortValue.first << " " << sortValue.second << endl;
}

LoadBalancer :: ~LoadBalancer()
{

}


void LoadBalancer :: setFiles()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (filesDirectory.c_str())) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
        string fileName;
        fileName = ent -> d_name;
        size_t found;
        found = fileName.find(DATABASE_FORMAT);
        if (found != string::npos) 
        {
            fileNames.push_back(fileName);   
            filesCount ++ ;
        }
        
    }
    closedir (dir);
    } else {
        cerr << "could not open directory" << endl;
    } 
}
