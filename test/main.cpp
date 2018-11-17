#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
int main()
{
    pid_t x = fork();

    if (x > 0)
    {
        // for (int i = 0; i < 1000000000000; i++)
        // {
            
        // }
        sleep(10);
        cout << "ok";
        wait(&x);
        // waitpid(x, )
        cout << "finish";
    }
    else if (x == 0)
    {
        char *l[10];
        execv("./a", l);
        cout << "finish child" << endl;
    }
}
