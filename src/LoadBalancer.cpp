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
    for(int i = 0 ; i < workers.size() ; i++)
        waitpid(workers[i], NULL, WNOHANG);
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

void LoadBalancer :: forkWorkers()
{
    for( int i = 0 ; i < processCount ; i++)
    {
        pid_t pid = fork();
        if(pid < 0)
        {
            cerr << "can not fork" << endl;
        }
        else if(pid == 0)
        {
            cout << EXECUTE_WORKER_MESSAGE(i) ;
            execv(WORKER_EXEC_PATH, NULL);
        }
        else
        {
            workers.push_back(pid);
        }
    }
}