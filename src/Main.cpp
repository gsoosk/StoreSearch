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

    loadBalancer.forkPresenter();
    loadBalancer.sendPresenterDetails();

    loadBalancer.createWorkerPipes();
    loadBalancer.forkWorkers();
    loadBalancer.writeOnWorkerPipes();


    for(getline(cin, command) ; command != "quit" ; getline(cin, command)){}
    return 0;
}
