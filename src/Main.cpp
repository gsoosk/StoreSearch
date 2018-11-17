#include <iostream>
#include <string>
#include <vector>
#include "LoadBalancer.h"
using namespace std;


int main()
{
    string command;
    getline(cin, command);
    LoadBalancer loadBalancer(command);
    
    loadBalancer.createWorkerPipes();
    loadBalancer.forkWorkers();
    loadBalancer.writeOnWorkerPipes();
    
    for(getline(cin, command) ; command != "quit" ; getline(cin, command)){}
    return 0;
}
