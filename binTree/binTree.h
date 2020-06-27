/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2019. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "binNode.h" //引入二叉树节点类
#include "BinNode_macro_BASIC.h"
#include <algorithm>
template <typename T> 
class BinTree { //二叉树模板类
protected:
   int _size; BinNodePosi(T) _root; //规模、根节点
   virtual int updateHeight ( BinNodePosi(T) x ); //更新节点x的高度
   void updateHeightAbove ( BinNodePosi(T) x ); //更新节点x及其祖先的高度
public:
   BinTree() : _size ( 0 ), _root ( NULL ) { } //构造函数
   ~BinTree() { if ( 0 < _size ) remove ( _root ); } //析构函数
   int size() const { return _size; } //规模
   bool empty() const { return !_root; } //判空
   BinNodePosi(T) root() const { return _root; } //树根
   BinNodePosi(T) insertAsRoot ( T const& e ); //插入根节点
   BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); //e作为x的左孩子（原无）插入
   BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); //e作为x的右孩子（原无）插入
//    BinNodePosi(T) attachAsLC ( BinNodePosi(T) x, BinTree<T>* &T ); //T作为x左子树接入
//    BinNodePosi(T) attachAsRC ( BinNodePosi(T) x, BinTree<T>* &T ); //T作为x右子树接入
   int remove ( BinNodePosi(T) x ); //删除以位置x处节点为根的子树，返回该子树原先的规模
   BinTree<T>* secede ( BinNodePosi(T) x ); //将子树x从当前树中摘除，并将其转换为一棵独立子树
   template <typename VST> //操作器
   void travLevel ( VST& visit ) { if ( _root ) _root->travLevel ( visit ); } //层次遍历
   template <typename VST> //操作器
   void travPre ( VST& visit ) { if ( _root ) _root->travPre ( visit ); } //先序遍历
   template <typename VST> //操作器
   void travIn ( VST& visit ) { if ( _root ) _root->travIn ( visit ); } //中序遍历
   template <typename VST> //操作器
   void travPost ( VST& visit ) { if ( _root ) _root->travPost ( visit ); } //后序遍历
   bool operator< ( BinTree<T> const& t ) //比较器（其余自行补充）
   { return _root && t._root && lt ( _root, t._root ); }
   bool operator== ( BinTree<T> const& t ) //判等器
   { return _root && t._root && ( _root == t._root ); }
}; //BinTree

//更新节点x的高度
template <typename T>
int BinTree<T>::updateHeight ( BinNodePosi(T) x ) {
    x->height = 1 + std::max(stature(x->lc),stature(x->rc));
}
//更新节点x及其祖先的高度
template <typename T>
void BinTree<T>::updateHeightAbove ( BinNodePosi(T) x ) {
    while(x) {
        updateHeight(x);
        x = x->parent;
    }
}
//插入根节点
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot ( T const& e ) {
    _size++;_root = new BinNode<T>(e);
    updateHeight(_root);
    return _root;
}
//e作为x的左孩子（原无）插入
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC ( BinNodePosi(T) x, T const& e ) {
    ++_size;x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}
//e作为x的右孩子（原无）插入
template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC ( BinNodePosi(T) x, T const& e ) {
    ++_size;x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template <typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
int BinTree<T>::remove ( BinNodePosi(T) x ) { //assert: x为二叉树中的合法位置
   FromParentTo ( *x ) = NULL; //切断来自父节点的指针
   updateHeightAbove ( x->parent ); //更新祖先高度
   int n = removeAt ( x ); _size -= n; return n; //删除子树x，更新规模，返回删除节点总数
}
template <typename T> //删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
static int removeAt ( BinNodePosi(T) x ) { //assert: x为二叉树中的合法位置
   if ( !x ) return 0; //递归基：空树
   int n = 1 + removeAt ( x->lc ) + removeAt ( x->rc ); //递归释放左、右子树
   delete x ; return n; //释放被摘除节点，并返回删除节点总数
} //release()负责释放复杂结构，与算法无直接关系，具体实现详见代码包