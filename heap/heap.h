#include <vector>
#include <algorithm>

template <typename T>
class heap {
    std::vector<T> _elem;
    void heapify(int n);
    int percolateDown (int n, int i ); //下滤
    int percolateUp (int i ); //上滤
    int parent(int i) {return i>>1; }//父亲
    int lchild(int i) {return 1+(i<<1);}//左孩子
    int rchild(int i) {return (1+i)<<1;}//有孩子
    bool inHeap(int n,int i) {return i>=0 && i<n;}//是否在堆中
    int maxParentChild(int n,int i) ;//节点和左右孩子中数值最大的节点
public :
    heap() {}
    heap(T* A,int n);
    heap(std::vector<T>&A,int n);
    void insert(T e);
    T getMax() {return _elem[0];}
    T delMax();
    template <typename VST>
    void traverse(VST visit) {
        for(T e : _elem) {visit(e);}
    }
};

//节点和左右孩子中数值最大的节点id
template <typename T>
int heap<T>::maxParentChild (int n, int i ) {
    int lc = lchild(i),rc = rchild(i);
    int max_val = _elem[i],ret = i;
    if(inHeap(n,lc) && max_val<_elem[lc]) { max_val=_elem[lc]; ret=lc;}
    if(inHeap(n,rc) && max_val<_elem[rc]) {max_val=_elem[rc];ret=rc;}
    return ret;
}
//下滤,如果左右孩子中有比自己大的，交换之，继续比较
template <typename T>
int heap<T>::percolateDown (int n, int i ) {
    T e = _elem[i];int j=i;
    while(j!=(i=maxParentChild(n,i))) {
        _elem[j] = _elem[i];j = i;
    }
    _elem[i] = e;
    return i;
}
//上滤，如果比父亲的kei大，交换之，继续比较
template <typename T>
int heap<T>::percolateUp (int i ) {
    T e = _elem[i];
    while(i) {
        int  j = parent(i);
        if(_elem[j]<e) {
            _elem[i]=_elem[j];
            i = j;
        } else break;
    }
    _elem[i] = e;
    return i;
}
template <typename T>
heap<T>::heap(T* A,int n) {
    int k = n;
    while(n--) {_elem.push_back(*A);A++;} 
    heapify(k);
}
template <typename T>
heap<T>::heap(std::vector<T>& A,int n) {
    for(int i=0;i<n;i++) _elem.push_back(A[i]);
    heapify(n);
}
//自下而上的下滤
template <typename T>
void heap<T>::heapify(int n) {
    //从最后一个父亲开始下率
    for(int i=n/2 -1;i>=0;i--) {
        percolateDown(n,i);
    }
}
template <typename T>
void heap<T>::insert(T e) {
    _elem.push_back(e);
    percolateUp(_elem.size()-1);
}

template <typename T>
T heap<T>::delMax() {
    int size = _elem.size();T ret = _elem[0];
    std::swap(_elem[0],_elem[size-1]);
    _elem.pop_back();
    percolateDown(size-1,0);
    return ret;
}



