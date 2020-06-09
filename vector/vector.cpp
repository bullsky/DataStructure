#include <iostream>
#include <vector.h>

using namespace std;

template <typename T>
class Increase
{
public:
    void operator()(T & e) {
        e ++ ;
    }
};


int main() {
    Vector<int> v;
    for(int i=0;i<10;i++) v.insert(i);
    v.traverse(Increase<int>());
}
