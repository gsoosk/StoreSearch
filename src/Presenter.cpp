#include "Presenter.h"
#include <iostream>
using namespace std;
Presenter ::Presenter()
{
    index = -1;
    int fd = open(FIFO_FILE_PATH, O_RDONLY);
    char buff[2048];
    read(fd, buff, 2048);
    close(fd);
    string balancerDataStr = buff;
    vector<string> balancerData = Tools ::splitByCharacter(balancerDataStr, '\n');
    processCount = stoi(balancerData[0]);
    for(int i = 1 ; i <= processCount; i++)
        workersPid.push_back(stoi(balancerData[i]));
    sortOrNot = balancerData[1 + processCount] == "1" ? 1 : 0;
    if (sortOrNot)
    {
        vector<string> sortValues = Tools ::splitByCharacter(balancerData[2 + processCount], '=');
        sortValue = sortValues[0];
        ascend = sortValues[1] == "ascend" ? true : false;
    }
}

Presenter ::~Presenter() {}


void Presenter ::getWorkersDataAndSort() 
{
    for (int i = 0 ; i < processCount ; i++)
    {
        
        string receiveFromWorker = this -> getWorkerData(i);
        vector < vector <string> > workerDetails = this -> getWorkerDetailsFromStr(receiveFromWorker);
        
        
        if(sortOrNot)
        {
            if(ascend)
                this -> insertAscend(workerDetails);
            else
                this -> insertDescend(workerDetails);
        }
        else
            this -> insert(workerDetails);
    }


}
void Presenter :: insertAscend(vector < vector < string > > workersDetails)
{
    int sortIndex = index ==-1 ? this -> findSortValueIndex(workersDetails[0]) : index;
    for( int i = 1 ; i < workersDetails.size() ; i++)
    {
        int insertIndex = 0;
        for(int j = 0 ; j < workersContent.size() ; j++)
        {
            if (!(Tools :: compare(workersDetails[i][sortIndex], workersContent[j][sortIndex])))
                insertIndex ++;
            else
                break;
        }
        workersContent.insert(workersContent.begin() + insertIndex, workersDetails[i]);
    }

}
void Presenter :: insertDescend(vector < vector < string > > workersDetails)
{
     int sortIndex = index ==-1 ? this -> findSortValueIndex(workersDetails[0]) : index;
    for( int i = 1 ; i < workersDetails.size() ; i++)
    {
        int insertIndex = 0;
        for(int j = 0 ; j < workersContent.size() ; j++)
        {
            if ((Tools :: compare(workersDetails[i][sortIndex], workersContent[j][sortIndex])))
                insertIndex ++;
            else
                break;
        }
        workersContent.insert(workersContent.begin() + insertIndex, workersDetails[i]);
    }
}
void Presenter :: insert(vector < vector < string > > workersDetails)
{
    for( int i = 1 ; i < workersDetails.size() ; i++)
    {
        workersContent.insert(workersContent.end(), workersDetails[i]);
    }
}
string Presenter :: getWorkerData(int i)
{
    string receiveFromWorker;
    string fifoPath = FIFO_FILE_PATH + to_string(workersPid[i]);
    ifstream file(fifoPath.c_str(), O_NONBLOCK);
     
    string line ;
    getline(file, line);
    while(line.length() < 3)
    {
        cerr << line << endl;
        getline(file, line);
    }

    while (getline(file, line))
        receiveFromWorker += (line + "\n");
    file.close(); 
    cerr << receiveFromWorker << endl;
    return receiveFromWorker;
}

vector < vector < string > > Presenter :: getWorkerDetailsFromStr(string detailsStr)
{
    vector < string > everyWorkerStr = Tools :: splitByCharacter(detailsStr, '\n');
    vector < vector < string > > workerDetails;
    int size = 0;
    for(int i = 0 ; i < everyWorkerStr.size() ; i++)
    {
        vector < string > x = Tools :: splitByCharacter(everyWorkerStr[i], ' ');
        if(size ==0 || x.size() == size)
        {
            size = x.size();
            workerDetails.push_back(x) ;
        }   
    
    }
       
    return workerDetails;
}  
int Presenter :: findSortValueIndex(vector < string > workerDetails)
{
    for(int i = 0 ; i < workerDetails.size() ; i++)
    {
        if(workerDetails[i] == sortValue)
        {
            index = i;
            return i;
        }
            
    }
    cerr << endl;
    return -1;
}

void Presenter :: showSortedData()
{

     for( int i = 0 ; i < workersContent.size() ; i++)
    {
        for(int j = 0 ; j < workersContent[i].size() ; j++)
            cout << workersContent[i][j] << " " ;
        cout << endl;
    } 
}