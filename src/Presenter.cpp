#include "Presenter.h"
#include <iostream>
using namespace std;
Presenter :: Presenter() 
{
    int fd = open(FIFO_FILE_PATH, O_RDONLY);
    char buff[1024];
    read(fd, buff, 1024);
    close(fd);
    string balancerDataStr = buff;
    vector < string > balancerData = Tools :: splitByCharacter(balancerDataStr , '\n');
    if(balancerData.size() < 2)
    {
        cerr << "corrupt data from balancer" << endl;
        return ;
    }
    processCount = stoi(balancerData[0]);
    sort = balancerData[1] == "1" ? 1 : 0;
    if(sort)
    {
        vector< string > sortValues = Tools :: splitByCharacter(balancerData[2], '=');
        sortValue = sortValues[0];
        ascend = sortValues[1] == "ascend" ? true : false;
    }
    // cerr << processCount << " " << sort << " " << sortValue << " " << ascend << endl;
}

Presenter :: ~Presenter() {}