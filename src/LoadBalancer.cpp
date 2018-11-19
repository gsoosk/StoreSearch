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
            if(filters != "")
                filters += "-";
            filters += config[0];
            filters += "=";
            filters += config[1];
        }
    }
    this -> setFiles();
    this -> createNamedPipe();
}
void LoadBalancer :: createNamedPipe()
{
    mkfifo(FIFO_FILE_PATH, 0666);
}
LoadBalancer :: ~LoadBalancer()
{
    for(int i = 0 ; i < workers.size() ; i++)
        waitpid(workers[i], NULL, WNOHANG);
    waitpid(presenter, NULL, WNOHANG);
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
            cout << EXECUTE_WORKER_MESSAGE(i) ;
            close(workerPipes[i][WRITE]);
            close(backWorkerPipes[i][READ]);
            char * argv[4];
            argv[0] = (char*) WORKER_EXEC_PATH;
            argv[1] = (char*) to_string(workerPipes[i][READ]).c_str();
            argv[2] = (char*) to_string(backWorkerPipes[i][WRITE]).c_str();
            argv[3] = NULL;
            execv(argv[0], argv);
        }
        else
        {
            close(workerPipes[i][READ]);
            close(backWorkerPipes[i][WRITE]);
            workers.push_back(pid);
        }
    }
}

void LoadBalancer :: createWorkerPipes()
{
    for(int i = 0 ; i < processCount ; i++)
    {
        int fd[2];
        int bfd[2];
        if( pipe(fd) < 0 )
        {
            cerr << "can not create pipe " << i << endl ;
            return ;
        }
        if( pipe(bfd) < 0 )
        {
            cerr << "can not create pipe " << i << endl ;
            return ;
        }
        vector < int > fds;
        fds.push_back(fd[0]);
        fds.push_back(fd[1]);
        vector < int > bfds;
        bfds.push_back(bfd[0]);
        bfds.push_back(bfd[1]);
        workerPipes.push_back(fds);
        backWorkerPipes.push_back(bfds);
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
    // writing filters
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

void LoadBalancer :: forkPresenter()
{
    pid_t pid = fork();
    if(pid < 0)
        cerr << "unable to fork presenter" << endl;
    else if(pid == 0)
    {
        execv(PRESENTER_EXEC_PATH, NULL);
    }
    else if(pid > 0)
    {
        presenter = pid;
    }
}

void LoadBalancer :: sendPresenterDetails()
{
    /* format : 
        <process count> 
        <1/0> // means sort or not
        <sortvalue = ascend / descend > */
    
    string toSend  = to_string(workers.size()) + "\n";
    for(int i = 0 ; i < workers.size(); i++)
        toSend += to_string(workers[i]) + "\n";
    toSend += sortOrNot ? "1\n" : "0\n";
    if(sortOrNot)
        toSend += (sortValue.first + "=" + sortValue.second + "\n");
    int fd = open(FIFO_FILE_PATH, O_WRONLY);
    write(fd, toSend.c_str() , strlen(toSend.c_str()) + 1);
    close(fd); 
}