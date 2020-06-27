/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2019. All rights reserved.
 ******************************************************************************************/

#pragma once
#include <stack>
#include <queue>

#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）
typedef enum { RB_RED, RB_BLACK} RBColor; //节点颜色

template <typename T> struct BinNode { //二叉树节点模板类
// 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
   T data; //数值
   BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //父节点及左、右孩子
   int height; //高度（通用）
   int npl; //Null Path Length（左式堆，也可直接用height代替）
   RBColor color; //颜色（红黑树）
// 构造函数
   BinNode() :
      parent ( NULL ), lc ( NULL ), rc ( NULL ), height ( 0 ), npl ( 1 ), color ( RB_RED ) { }
   BinNode ( T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
             int h = 0, int l = 1, RBColor c = RB_RED ) :
      data ( e ), parent ( p ), lc ( lc ), rc ( rc ), height ( h ), npl ( l ), color ( c ) { }
// 操作接口
   int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
   BinNodePosi(T) insertAsLC ( T const& ); //作为当前节点的左孩子插入新节点
   BinNodePosi(T) insertAsRC ( T const& ); //作为当前节点的右孩子插入新节点
   BinNodePosi(T) succ(); //取当前节点的直接后继
   template <typename VST> void travLevel ( VST& ); //子树层次遍历
   template <typename VST> void travPre ( VST& ); //子树先序遍历
   template <typename VST> void travIn ( VST& ); //子树中序遍历
   template <typename VST> void travPost ( VST& ); //子树后序遍历
// 比较器、判等器（各列其一，其余自行补充）
   bool operator< ( BinNode const& bn ) { return data < bn.data; } //小于
   bool operator== ( BinNode const& bn ) { return data == bn.data; } //等于
   /*DSA*/
   /*DSA*/BinNodePosi(T) zig(); //顺时针旋转
   /*DSA*/BinNodePosi(T) zag(); //逆时针旋转
   /*DSA*/BinNodePosi(T) balance(); //完全平衡化
   /*DSA*/BinNodePosi(T) imitate( const BinNodePosi(T) );
};
//作为当前节点的左孩子插入新节点
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC ( T const& e) {
    lc = new BinNode<T>(e,this);
}
//作为当前节点的右孩子插入新节点
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC ( T const& e) {
    rc = new BinNode<T>(e,this);
}
//取当前节点的直接后继
template <typename T>
BinNodePosi(T) BinNode<T>::succ() {}
//子树先序遍历
template <typename T>
template <typename VST> 
void BinNode<T>::travPre ( VST& visit) {
    std::stack<BinNodePosi(T)> st;
    BinNodePosi(T) cur = this;
    while(true) {
        while(cur) {
            visit(cur->data);
            st.push(cur->rc);
            cur = cur->lc;
        }
        if(st.empty()) break;
        cur = st.top();st.pop();
    }
}
//特殊版
// template <typename T>
// template <typename VST> 
// void BinNode<T>::travPre ( VST& visit) {
//     stack<BinNodePosi(T)> st;
//     if(this) st.push(this);
//     while(!st.empty()) {
//         BinNodePosi<T> cur = st.pop();
//         visit(cur);
//         if(cur->rc) st.push(cur->rc);
//         if(cur->lc) st.push(cur->lc);
//     }
// }
//子树中序遍历
template <typename T>
template <typename VST>
void BinNode<T>::travIn ( VST& visit) {
    std::stack<BinNodePosi(T)> st;
    BinNodePosi(T) cur = this;
    while(true) {
        while(cur) {
            st.push(cur);
            cur=cur->lc;
        }
        if(st.empty()) break;
        cur = st.top();
        visit(cur->data);st.pop();
        cur = cur->rc;
    }
}
//子树后序遍历
template <typename T>
template <typename VST>
void BinNode<T>::travPost ( VST& visit) {
}
//子树层次遍历
template <typename T>
template <typename VST>
void BinNode<T>::travLevel ( VST& visit) {
    std::queue<BinNodePosi(T)> q;
    q.push(this);
    while(!q.empty()) {
        BinNodePosi(T) cur = q.front();q.pop();
        visit(cur->data);
        if(cur->lc) q.push(cur->lc);
        if(cur->rc) q.push(cur->rc);
    }
}
