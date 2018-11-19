#include <iostream>
#include "Presenter.h"
using namespace std;
int main(int argc, char const *argv[])
{
    Presenter presenter;
    presenter.getWorkersDataAndSort();
    presenter.showSortedData();
    return 0;
}