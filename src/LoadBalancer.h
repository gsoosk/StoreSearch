#include <vector>
#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define ASCEND "ascend"
#define DESCEND "descend"
#define PROCESS_COUNT "prc_cnt"
#define DIRECTORY "dir"
#define DATABASE_FORMAT ".dms"
#define EXECUTE_WORKER_MESSAGE(i) ( "exceuting worker " + to_string(i));
#define EXECUTE_PRESENTER_MESSAGE "executing presenter"
#define WORKER_EXEC_PATH "bin/Worker"
#define PRESENTER_EXEC_PATH "bin/Presenter"
#define READ 0
#define WRITE 1




class LoadBalancer
{

  public:
    LoadBalancer(std :: string commmand);
    ~LoadBalancer();
    // Workers Management
    void createWorkerPipes();
    void writeOnWorkerPipes();
    void forkWorkers();
    // Presenter Mangement
    void forkPresenter();
    void sendPresenterDetails();

  private:
    // User Input management
    std :: string filters;
    std :: pair < std :: string , std :: string > sortValue ;
    bool sortOrNot;
    int processCount;
    std :: string filesDirectory; 
    // File management
    std :: vector< std :: string > fileNames;
    int filesCount;
    void setFiles();
    // Workers management
    std :: vector< std :: vector<int> > workerPipes;
    std :: vector< std :: vector<int> > backWorkerPipes;
    std :: vector< pid_t > workers;
    // Presenter management
    pid_t presenter;
    void createNamedPipe();
};
