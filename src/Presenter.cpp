#include "Presenter.h"
#include <iostream>
using namespace std;
Presenter ::Presenter()
{
    int fd = open(FIFO_FILE_PATH, O_RDONLY);
    char buff[1024];
    read(fd, buff, 1024);
    close(fd);
    string balancerDataStr = buff;
    vector<string> balancerData = Tools ::splitByCharacter(balancerDataStr, '\n');
    if (balancerData.size() < 2)
    {
        cerr << "corrupt data from balancer" << endl;
        return;
    }
    processCount = stoi(balancerData[0]);
    sort = balancerData[1] == "1" ? 1 : 0;
    if (sort)
    {
        vector<string> sortValues = Tools ::splitByCharacter(balancerData[2], '=');
        sortValue = sortValues[0];
        ascend = sortValues[1] == "ascend" ? true : false;
    }
    // cerr << processCount << " " << sort << " " << sortValue << " " << ascend << endl;
}

Presenter ::~Presenter() {}

void Presenter ::getWorkersData()
{
    // int i = 0;
    // ifstream fifo(FIFO_FILE_PATH);
    // string received;
    // if (fifo.is_open())
    // {
    //     string line;
    //     getline(fifo, line);
    //     while (i < processCount )
    //     {   
            
    //         if(line.length() > 2)
    //             cerr << line << endl;
    //         if(line == "-process-details-")
    //         {
    //             i++;
    //             cerr << "one process";
    //         }
    //         else 
    //             received += (line + "\n");

    //         getline(fifo, line);
    //     }
    // }
    // // cerr << received << endl;
    // fifo.close();


    string recived = "";
    char buff[1024];
    int fd = open(FIFO_FILE_PATH, O_RDONLY);
    while(true)
    {
        int readed = read(fd, buff, 1025);
        if(readed > 0)
        {
            recived += buff;
            cerr << buff;
        }
    }
    close(fd);
    
    // string recivied = "";
    // for (int i = 0 ; i < processCount ; i++)
    // {
    //     char buff[2048];
    //     int fd = open(FIFO_FILE_PATH, O_RDONLY);
    //     read(fd, buff, 2048);
    //     close(fd);
    //     cerr << buff;
    // }
}
