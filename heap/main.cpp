#include <iostream>
#include "heap.h"
using namespace std;


int main() {
    heap<int> h1;
    int A[10] = {0,1,3,5,7,9,12,14,16,8};
    heap<int> h2(A,10);
    for(int i=0;i<10;i++) h1.insert(i);
    auto func = [](int x) {cout<<x<<" ";};
    h1.traverse(func);cout<<endl;
    h2.traverse(func);cout<<endl;
    cout << h1.getMax() <<endl;
    h1.delMax();
    cout<<h1.delMax()<<" "<<h1.getMax()<<endl;


}