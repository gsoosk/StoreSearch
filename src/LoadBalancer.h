#include <vector>
#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>

#define ASCEND "ascend"
#define DESCEND "descend"
#define PROCESS_COUNT "prc_cnt"
#define DIRECTORY "dir"
#define DATABASE_FORMAT ".dms"
#define EXECUTE_WORKER_MESSAGE(i) ( "exceuting worker " + to_string(i));
#define WORKER_EXEC_PATH "bin/Worker"




class LoadBalancer
{

  public:
    LoadBalancer(std :: string commmand);
    ~LoadBalancer();
    void setFiles();

    void forkWorkers();

  private:
    std :: vector< std :: pair <std :: string , std :: string> > filters;
    std :: pair < std :: string , std :: string > sortValue ;
    bool sortOrNot;
    int processCount;
    std :: string filesDirectory; 

    std :: vector< std :: string > fileNames;
    int filesCount;

    std :: vector< pid_t > workers;
};
