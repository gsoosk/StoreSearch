#include "LoadBalancer.h"
#include "Tools.h"
#include <iostream>
using namespace std;


LoadBalancer :: LoadBalancer (string command)
{
    filesCount = 0;
    filters = "";
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
            // pair < string, string > filter;
            // filter.first = config[0];
            // filter.second = config[1];
            // filters.push_back(filter);
            if(filters != "")
                filters += "-";
            filters += config[0];
            filters += "=";
            filters += config[1];
        }
    }
    this -> setFiles();
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
    for( int i = 0 ; i < workerPipes.size() ; i++)
    {
        pid_t pid = fork();
        if(pid < 0)
        {
            cerr << "can not fork" << endl;
        }
        else if(pid == 0)
        {
            close(workerPipes[i][WRITE]);
            cout << EXECUTE_WORKER_MESSAGE(i) ;
            char * argv[3];
            argv[0] = (char*) WORKER_EXEC_PATH;
            argv[1] = (char*) to_string(workerPipes[i][READ]).c_str();
            argv[2] = NULL;
            execv(argv[0], argv);
        }
        else
        {
            close(workerPipes[i][READ]);
            workers.push_back(pid);
        }
    }
}

void LoadBalancer :: createWorkerPipes()
{
    for(int i = 0 ; i < processCount ; i++)
    {
        int fd[2];
        if( pipe(fd) < 0 )
        {
            cerr << "can not create pipe " << i << endl ;
            return ;
        }
        vector < int > fds;
        fds.push_back(fd[0]);
        fds.push_back(fd[1]);
        workerPipes.push_back(fds);
    }
}

void LoadBalancer :: writeOnWorkerPipes()
{
    vector < string > fileNamesToSend = fileNames;
    int pipesSize = workerPipes.size();
    int i = 0 ;
    vector <string> toSend(pipesSize);
    for(int j = 0 ; j < toSend.size(); j++)
        toSend[j] = "";
    // writing file names
    while(fileNamesToSend.size() > 0 )
    {
        if ( i == pipesSize)
            i = 0;
        toSend[i] += filesDirectory;
        toSend[i] += "/";
        toSend[i] += fileNamesToSend[fileNamesToSend.size() - 1]; 
        toSend[i] += "\n";
        fileNamesToSend.pop_back();
        i++;
    }
    //writing filters
    for( i = 0 ; i < pipesSize ; i++)
    {
        toSend[i] += END_OF_FILES; 
        toSend[i] += "\n";
        toSend[i] += filters;
        char* buff = (char*) toSend[i].c_str();
        write(workerPipes[i][WRITE], buff, strlen(buff) + 1 );
        close(workerPipes[i][WRITE]);
    }
   
}