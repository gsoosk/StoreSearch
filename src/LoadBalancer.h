#include <vector>
#include <string>
#define ASCEND "ascend"
#define DESCEND "descend"
#define PROCESS_COUNT "prc_cnt"
#define DIRECTORY "dir"



class LoadBalancer
{

  public:
    LoadBalancer(std :: string commmand);
    ~LoadBalancer();

  private:
    std :: vector< std :: pair <std :: string , std :: string> > filters;
    std :: pair < std :: string , std :: string > sortValue ;
    bool sortOrNot;
    int processCount;
    std :: string filesDirectory; 
};
