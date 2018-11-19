#include <iostream>
#include <string>
#include <vector>
#include "LoadBalancer.h"
#include "Tools.h"
using namespace std;

int main()
{
    string command;
    for(getline(cin, command) ; command != "quit" ; getline(cin, command))
    {
        LoadBalancer loadBalancer(command);

        loadBalancer.createWorkerPipes();
        loadBalancer.forkWorkers();
        

        loadBalancer.forkPresenter();
        loadBalancer.sendPresenterDetails();
        loadBalancer.writeOnWorkerPipes();
        
    }
    return 0;
}
