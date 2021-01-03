#include <iostream>
#include "HashMap.h"
int main() {
    std::cout << "Hello, World!" <<(sqrt(5)-1)/2<<std::endl;
    HashMap<HashMap<int>>* a = new HashMap<HashMap<int>>();
    a->insert(12);
    a->insert(122);
    a->insert(11222);
    a->insert(23);
    a->deleteNode(23);
    for (int i = 0; i <500; ++i) {
        a->insert(i);
    }
    for (int i = 0; i <450; ++i) {
        a->deleteNode(i);
    }
    for (int i = 55; i <7500; ++i) {
        a->insert(i);
    }
    for (int i = 0; i <7480; ++i) {
        a->deleteNode(i);
    }
    a->printMap();
    delete a;
   // std::cout<<a->decodeKey(123456)<<"\n";
    return 0;
}
