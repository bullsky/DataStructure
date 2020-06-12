#include <iostream>
#include "list.h"

using namespace std;

template <typename T>
class print
{
public:
    void operator()(T &e)
    {
        cout << e << " ";
    }
};


int main()
{
    List<int> mylist;
    print<int> pfunc;
    for (int i = 0; i < 10; i++)
        mylist.insertB(mylist.first(), i);
    for (int i = 20; i > 15; i--)
        mylist.insertA(mylist.first(), i);
    mylist.traverse(pfunc);cout<<endl;
    mylist.sort();
    mylist.traverse(pfunc);cout<<endl;
    
}
