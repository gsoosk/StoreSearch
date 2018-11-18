#include <vector>
#include <string>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <fstream>
#include "Tools.h"

class Presenter
{
  public:
    Presenter() ;
    ~Presenter() ;
    void getWorkersData();

  private:
    // Main Details from Balancer :
    int processCount;
    bool sort;
    bool ascend;
    std :: string sortValue ;
    // Details from workers :
    std :: vector < std :: vector < std :: string > > workersContent;
    
};