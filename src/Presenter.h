#include <vector>
#include <string>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include "Tools.h"

class Presenter
{
  public:
    Presenter() ;
    ~Presenter() ;

  private:
    int processCount;
    bool sort;
    bool ascend;
    std :: string sortValue ;
    
};