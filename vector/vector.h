/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2019. All rights reserved.
 ******************************************************************************************/

#pragma once

typedef int Rank;          //秩
#define DEFAULT_CAPACITY 3 //默认的初始容量（实际应用中可设置为更大）

template <typename T>
class Vector
{ //向量模板类
protected:
    Rank _size;
    int _capacity;
    T *_elem;                                    //规模、容量、数据区
    void copyFrom(T const *A, Rank lo, Rank hi); //复制数组区间A[lo, hi)
    void expand();                               //空间不足时扩容
    void shrink();                               //装填因子过小时压缩
    int bubble(Rank lo, Rank hi);                //扫描交换
    void bubbleSort(Rank lo, Rank hi);           //起泡排序算法
    Rank max(Rank lo, Rank hi);                  //选取最大元素
    void selectionSort(Rank lo, Rank hi);        //选择排序算法
    void merge(Rank lo, Rank mi, Rank hi);       //归并算法
    void mergeSort(Rank lo, Rank hi);            //归并排序算法
    void heapSort(Rank lo, Rank hi);             //堆排序（稍后结合完全堆讲解）
    Rank partition(Rank lo, Rank hi);            //轴点构造算法
    void quickSort(Rank lo, Rank hi);            //快速排序算法
    void shellSort(Rank lo, Rank hi);            //希尔排序算法
public:
    // 构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c、规模为s、所有元素初始为v
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    }                                                                           //s<=c
    Vector(T const *A, Rank n) { copyFrom(A, 0, n); }                           //数组整体复制
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }               //区间
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); }               //向量整体复制
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //区间
                                                                                // 析构函数
    ~Vector() { delete[] _elem; }                                               //释放内部空间
                                                                                // 只读访问接口
    Rank size() const { return _size; }                                         //规模
    bool empty() const { return !_size; }                                       //判空
    Rank find(T const &e) const { return find(e, 0, _size); }                   //无序向量整体查找
    Rank find(T const &e, Rank lo, Rank hi) const;                              //无序向量区间查找
    Rank search(T const &e) const                                               //有序向量整体查找
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const &e, Rank lo, Rank hi) const;     //有序向量区间查找
                                                         // 可写访问接口
    T &operator[](Rank r);                               //重载下标操作符，可以类似于数组形式引用各元素
    const T &operator[](Rank r) const;                   //仅限于做右值的重载版本
    Vector<T> &operator=(Vector<T> const &);             //重载赋值操作符，以便直接克隆向量
    T remove(Rank r);                                    //删除秩为r的元素
    int remove(Rank lo, Rank hi);                        //删除秩在区间[lo, hi)之内的元素
    Rank insert(Rank r, T const &e);                     //插入元素
    Rank insert(T const &e) { return insert(_size, e); } //默认作为末元素插入
    void sort(Rank lo, Rank hi);                         //对[lo, hi)排序
    void sort() { sort(0, _size); }                      //整体排序
    void unsort(Rank lo, Rank hi);                       //对[lo, hi)置乱
    void unsort() { unsort(0, _size); }                  //整体置乱
    int deduplicate();                                   //无序去重
    int uniquify();                                      //有序去重
                                                         // 遍历
    void traverse(void (*)(T &));                        //遍历（使用函数指针，只读或局部性修改）
    template <typename VST>
    void traverse(VST &); //遍历（使用函数对象，可全局性修改）
};                        //Vector

template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
    //为什么要复制两倍的空间？
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi)
    {
        _elem[size++] = A[lo++];
    }
}
// 容器扩容
template <typename T>
void Vector<T>::expand()
{
    if (_size < _capacity)
        return;
    _capacity = max(_capacity, DEFAULT_CAPACITY);
    T *old_elem = _elem;
    _elem = new T[_capacity << 1];
    while (--_size >= 0)
    {
        _elem[_size] = old_elem[_size];
    }
    delete[] old_elem;
}

template <typename T>
T &Vector<T>::operator[](Rank r)
{
    return _elem[r];
}

template <typename T>
Rank Vector<T>::insert(Rank r, const T &e)
{
    expand() //需要则扩容
        for (int i = _size; i > r; i--)
    {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    _size++;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi)
        return 0;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink(); //空余空间太多，需要缩容
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
    T ret = _elem[r];
    remove(r, r + 1);
    return ret;
}

//输入敏感，性能取决于输入的数据特征
template <typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const
{
    while ((lo < hi) && (_elem[--hi] != e))
        ;
    return hi;
}

//去重，返回删除元素的数目
template <typename T>
int Vector<T>::deduplicate()
{
    int oldsize = _size;
    Rank i = 1;
    while (i < _size)
    {
        find(_elem[i], 0, i) >= 0 ? remove(i) : i++;
    }
    return oldsize - _size;
}

//遍历（使用函数指针，只读或局部性修改）
template <typename T>
void Vector<T>::traverse(void (*visit)(T &))
{
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}
//遍历（使用函数对象，可全局性修改）
template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit)
{
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}
//有序向量去重，返回删除元素的数目
template <typename T>
int Vector<T>::uniquify()
{
    Rank oldsize = _size;
    Rank lo = 0, hi = 0;
    while (++hi < _size)
    {
        if (_elem[hi] != _elem[lo])
            _elem[++lo] = _elem[hi]
    }
    _size = lo + 1;
    shrink();
    return oldsize - _size;
}
//有序向量区间查找
template <typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const
{
    return binarySearch(_elem, e, lo, hi);
}

//二分查找
template <typename T>
static Rank binarySearch(const T elem[], const T &e, Rank lo, Rank hi)
{
    while (lo < hi)
    { //A[0,lo)<=e<A[hi,n)
        Rank mid = hi + lo >> 1;
        e < elem[mid] ? hi = mid : lo = mid + 1;
    }
    return --lo;
}

//起泡排序
template <typename T>
int Vector<T>::bubble(Rank lo, Rank hi)
{
    Rank last = lo;
    while (hi > lo++)
    {
        if (_elem[lo] < _elem[lo - 1])
        {
            last = lo;
            swap(_elem[lo], _elem[lo - 1]);
        }
    }
    return last;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (lo < (hi = bubble(lo, hi)))
        ;
}

//归并算法
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
    T *A = _elem + lo;
    T *B = new T[mi - lo];
    T *C = _elem + mi;
    for (Rank i = 0; i < mi - lo; i++)
        B[i] = A[i];
    Rank lb = mi - lo, lc = hi - mi;
    Rank i = 0, j = 0, k = 0;
    while (i < lb && j < lc)
    {
        if (B[i] < C[i])
            A[k++] = B[i++];
        else
            A[k++] = C[j++];
    }
    if (j == lc)
    {
        while (i < lb)
        {
            A[k++] = B[j++];
        }
    }
    // if (i == lb)
    // {
    //     while (j < lc)
    //     {
    //         A[k++] = C[j++];
    //     }
    // }
}

//归并排序算法
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    Rank mid = (lo + hi) >> 1;
    mergeSort(lo, mid);
    mergeSort(mid, hi);
    merge(lo, mid, hi);
}