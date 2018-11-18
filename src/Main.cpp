#include <iostream>
#include <string>
#include <vector>
#include "LoadBalancer.h"
#include "Tools.h"
using namespace std;


int main()
{
    string command;
    getline(cin, command);
    LoadBalancer loadBalancer(command);

   
   
    loadBalancer.createWorkerPipes();
    loadBalancer.forkWorkers();
    loadBalancer.writeOnWorkerPipes();

    loadBalancer.forkPresenter();
    loadBalancer.sendPresenterDetails();
    for(getline(cin, command) ; command != "quit" ; getline(cin, command)){}
    return 0;
}
