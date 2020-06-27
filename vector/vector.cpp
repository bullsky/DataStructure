#include <iostream>
#include <algorithm>
#include "vector.h"

using namespace std;

template <typename T>
class Increase
{
public:
    void operator()(T & e) {
        e ++ ;
    }
};
template <typename T>
void print(T & e) {
    cout << e<<" ";    
}


int main() {
    Vector<int> v;
    for(int i=0;i<10;i++) v.insert(i);
    // void (*pf)(int &) = print<int>;
    // for(int i=0;i<10;i++) cout<<v[i]<<" ";
    Increase<int> increaseFunc;
    v.traverse(increaseFunc);
    v.traverse(print<int>);cout <<endl;
    v.remove(2,6);
    v.traverse(print<int>);cout <<endl;
    cout << v.search(5)<<endl;
    cout << v.search(8)<<endl;
    v.insert(0,10);
    v.insert(0,15);
    v.traverse(print<int>);cout <<endl;
    v.sort(0,9);
    v.traverse(print<int>);cout <<endl;
}
