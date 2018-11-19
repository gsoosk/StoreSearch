#include "Worker.h"
using namespace std;
Worker :: Worker (int pipeFd)
{
    char buff[2048];
    
    read(pipeFd, buff, 2048);
    close(pipeFd);
    string input = buff;
    vector < string > inputs = Tools :: splitByCharacter(input, '\n');
    int i = 0 ;
    while(inputs[i] != END_OF_FILES)
    {
        files.push_back(inputs[i]);
        i++;
    }
    
    // cerr << getpid() << endl;
    i++;
    fifoPath = FIFO_FILE_PATH + to_string(getpid());
    mkfifo(fifoPath.c_str(), 0666);
    this -> getFilters(inputs[i]);
}
void Worker :: getFilters( string allFilters )
{
    vector <string> filtersStr = Tools :: splitByCharacter(allFilters , '-');
    for (int j = 0 ; j < filtersStr.size() ; j++)
    {
        vector <string> singleFilter = Tools :: splitByCharacter(filtersStr[j], '=');
        pair < string , string > filter;
        filter.first = singleFilter[0];
        filter.second = singleFilter[1];
        filters.push_back(filter); 
    }
}

void Worker :: getFileContents()
{
    bool headerAdded = false;
    for (int i = 0 ; i < files.size() ; i++)
    {
        string line ;
        ifstream file(files[i]);
        if(!getline(file, line))
            continue ;
        
        if(!headerAdded)
        {
            filesContent.push_back( Tools :: splitByCharacter(line, ' '));
            headerAdded = true;
        } 
        while(getline(file, line))
            filesContent.push_back( Tools :: splitByCharacter(line, ' '));
        file.close();
       
    }   
}

void Worker :: filterFilesContent()
{
    for(int i = 0 ; i < filters.size() ; i++)
    {
        if(filesContent.size() == 0)
            return ;
        int j = this -> findFilterIndex(filters[i].first, 0);
        if(j < 0)
        {
            cerr << "filter not found " << filters[i].first << endl;
            return ;
        }
        int k = 1;
        while( k != filesContent.size())
        {
            if(filesContent[k][j] != filters[i].second)
                filesContent.erase (filesContent.begin()+k);
            else
                k++;
        }
    } 
}

int Worker :: findFilterIndex(string filterName, int row)
{
    for(int i = 0 ; i < filesContent[row].size() ; i++)
    {
        if(filesContent[0][i] == filterName)
            return i;
    }
    return -1;
}

void Worker :: sendContentsToPresenter()
{
    string toSend = "";
    for (int i = 0 ; i < filesContent.size() ; i++)
    {
        for(int j = 0 ; j < filesContent[i].size() ; j++)
        {
            toSend += filesContent[i][j];
            if(j == filesContent[i].size() - 1)
                toSend += "\n";
            else
                toSend += " ";
        }
    }
    int fd = open(fifoPath.c_str(), O_WRONLY);
    int x = write(fd, toSend.c_str() , strlen(toSend.c_str()) + 1);
    close(fd);
}


bool Worker :: havePermissionToWrite()
{
    /* the size (in bytes) of shared memory object */
    const int SIZE = 128; 
    const char* name = "permission"; 
    int shm_fd; 
    void* ptr;
    void* ptrW; 
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); 
    string permission = (char*) ptr;
    cerr << permission << endl;
    if(permission == "ok")
    {
        this -> getPermissionToWrite();
        return true;  
    }
    return false;
}
void Worker :: getPermissionToWrite()
{
    const int SIZE = 128; 
    const char* name = "permission"; 
    const char* message = "nok"; 
    int shm_fd; 
    void* ptr; 
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 
    ftruncate(shm_fd, SIZE); 
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); 
    char* p = (char*) ptr;
    sprintf(p, "%s", message); 
}
void Worker :: givePermissonToWrite()
{
    const int SIZE = 128; 
    const char* name = "permission"; 
    const char* message = "ok"; 
    int shm_fd; 
    void* ptr; 
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); 
    ftruncate(shm_fd, SIZE); 
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0); 
    char* p = (char*) ptr;
    sprintf(p, "%s", message); 
}
Worker :: ~Worker()
{

}