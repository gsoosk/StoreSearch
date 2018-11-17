#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
 
    vector < int*> x;
    {
        int t[2];
        t[0] = 10;
        t[1] = 9;
        x.push_back(t);
    }
    int t[2];
    t[0] = 7;
    t[1] = 6;
    cout << x[0][0] << " " << x[0][1];
    return 0;
}
    // cerr << processCount << endl;
    // // cerr << filesDirectory << endl;
    // for(int i = 0  ; i < filters.size() ; i++)
    //     cerr << filters[i].first << "  " << filters[i].second << endl;
    // for(int i = 0  ; i < files.size() ; i++)
    //     cerr << files[i] << endl;
    // // cerr << sortOrNot << endl;
    // // cerr << sortValue.first << " " << sortValue.second << endl;


    //  for( int i = 0 ; i < filesContent.size() ; i++)
    // {
    //     for(int j = 0 ; j < filesContent[i].size() ; j++)
    //         cout << filesContent[i][j] << " " ;
    //     cout << endl;
    // }
