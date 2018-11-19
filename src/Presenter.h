#include <vector>
#include <string>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <fstream>
#include <algorithm>
#include "Tools.h"

class Presenter
{
  public:
    Presenter() ;
    ~Presenter() ;
    void getWorkersDataAndSort();
    void showSortedData();
    
  private:
    // Main Details from Balancer :
    int processCount;
    bool sortOrNot;
    bool ascend;
    std :: string sortValue ;
    int sortValueIndex;
    // Details from workers :
    std :: vector < std :: vector < std :: string > > workersContent;
    std :: vector < int > workersPid;
    std :: vector < std :: vector < std :: string > > getWorkerDetailsFromStr(std :: string detailsStr);
    std :: string getWorkerData(int i);
    int index;
    int findSortValueIndex(std :: vector <std :: string> workerDetails);
    void insertAscend(std :: vector < std :: vector < std :: string > > workersDetails);
    void insertDescend(std :: vector < std :: vector < std :: string > > workersDetails);
    void insert(std :: vector < std :: vector < std :: string > > workersDetails);
    

    
};