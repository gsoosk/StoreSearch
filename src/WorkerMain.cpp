#include <iostream>
#include "Worker.h"
using namespace std;
int main(int argc, char const *argv[])
{
    Worker worker(atoi(argv[1]));
    worker.getFileContents();
    worker.filterFileContents();

    return 0;
}
