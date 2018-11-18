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
        // cerr << inputs[i] << " ";
        i++;
    }
    // cerr << getpid() << endl;
    i++;
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
            return ;
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

     for( int i = 0 ; i < filesContent.size() ; i++)
    {
        for(int j = 0 ; j < filesContent[i].size() ; j++)
            cout << filesContent[i][j] << " " ;
        cout << endl;
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
Worker :: ~Worker()
{

}