#include "rbtree.hpp"
#include <iostream>
#include <random>
#include <vector>
using namespace std;
int main() {
    RB_Tree<int, int> tree;
    for(int i=0; i<1000; i++) 
        tree.insertNode(i, i*5);
    

    for(int i=0; i< 1000; i+=7) {
        if(i == 0)
            cout << " " << endl;
        tree.eraseNode(i);
        try {
            std::cout << tree.find(i) << std::endl;
        } catch (const char *mesage) {
            std::cout <<  mesage << i <<std::endl;
        }
    }
    

    return 0;
}