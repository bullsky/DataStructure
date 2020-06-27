#include "binTree.h"
#include "iostream"
using namespace std;

int main() {
    BinTree<int> tree;
    tree.insertAsRoot(1);
    tree.insertAsLC(tree.root(),2);tree.insertAsRC(tree.root(),3);
    tree.insertAsLC(tree.root()->lc,4);tree.insertAsRC(tree.root()->lc,5);
    tree.insertAsLC(tree.root()->rc,6);tree.insertAsRC(tree.root()->rc,7);
    auto print_func = [](int x) {cout<<x<<" ";};
    tree.travPre(print_func);
    tree.travIn(print_func);
    tree.travPost(print_func);
    tree.travLevel(print_func);
}