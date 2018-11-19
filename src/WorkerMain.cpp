#include <iostream>
#include "Worker.h"
using namespace std;
int main(int argc, char const *argv[])
{
    
    Worker worker(atoi(argv[1]));
    worker.getFileContents();
    worker.filterFilesContent();
    worker.sendContentsToPresenter();
    return 0;
}
