#include <iostream>
#include "kmp.h"

using namespace std;

int main() {
    char text[] = "asfafhellowgergdhrtworldisofmsmfpwew";
    char parten[] = "hello";
    // char parten[] = "asdsfds";
    cout << isMatch(parten,text)<<endl;
    cout << text[isMatch(parten,text)]<<endl;

}