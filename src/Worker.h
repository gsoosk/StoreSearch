#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include "Tools.h"
class Worker
{

  public:
    Worker(int pipeFd);
    void getFileContents();
    void filterFileContents();
    ~Worker();

  private:
    std :: vector< std :: pair <std :: string , std :: string> > filters;
    std :: vector< std :: string > files;
    void getFilters(std :: string allFilters);

    std :: vector < std :: vector < std :: string > > filesContent;
    int findFilterIndex(std :: string);
    
    
};