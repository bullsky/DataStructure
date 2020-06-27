#include <string.h>

//getnext 等价于 模式串自己匹配自己，并在过程中记录相同的真前缀 和真后缀
int * getNext(char * P) {
    int m = strlen(P),i=0;
    int *next = new int[m];
    int t = next[0] = -1;//next[0],哨兵
    while(i<m-1) {
        if(t<0 || P[t]==P[i]) {//匹配
            i++;t++;
            // next[i]=t;
            next[i] = P[t]!=P[i] ? t : next[t];
        } else t = next[t];//失配
    }
    // for(int i=1;i<m;i++) {
    //     for(int j=i-1;j>=0;) {
    //         P[i] == P[j+1] ? next[i] = j+1 : j=next[j];
    //     }
    // }
    return next;
}
int isMatch(char * P,char * T ) {
    int *next = getNext(P);
    int m = strlen(P),i=0;
    int n = strlen(T),j=0;
    while(i<m && j<n) {
        if(i<0 || P[i]==T[j]) { i++;j++;}//匹配++
        else i = next[i];//失配 ，快速滑动
    }
    return j-i;
}
