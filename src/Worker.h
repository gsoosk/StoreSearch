#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h> 
#include <fstream>
#include <stdlib.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include "Tools.h"
class Worker
{

  public:
    Worker(int pipeFd);
    void getFileContents();
    void filterFilesContent();
    void sendContentsToPresenter();

    bool havePermissionToWrite();
    void getPermissionToWrite();
    void givePermissonToWrite();
    
    ~Worker();

  private:
    std :: vector< std :: pair <std :: string , std :: string> > filters;
    std :: vector< std :: string > files;
    void getFilters(std :: string allFilters);

    std :: vector < std :: vector < std :: string > > filesContent;
    int findFilterIndex(std :: string, int row);
    
    
};