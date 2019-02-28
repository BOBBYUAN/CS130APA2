#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include <utility>
#include "splayTree.h"
using namespace std;
typedef long long lld;
typedef unsigned long long llu;

int main()
{
    SplayTree *sTree = new SplayTree();
    string input;
    int numberOfOperation;
    cin >> numberOfOperation;

    while (cin >> input) {
        if (input == "insert") {
            cin >> input;
            sTree -> insert(stoi(input));
        }
        else if (input == "find") {
            cin >> input;
            sTree -> find(stoi(input));
        }
        else if (input == "delete") {
            cin >> input;
            sTree -> Delete(stoi(input));
        }
        else if (input == "print") {
            sTree -> print();
        }
        else continue;
    }
    return 0;
    
//    SplayTree *sTree = new SplayTree();
//
//    sTree -> insert(10);
//    sTree -> insert(8);
//    sTree -> insert(5);
//    sTree -> insert(3);
//    sTree -> insert(14);
//    sTree -> insert(16);
//    sTree -> insert(19);
//    sTree -> print();
//
//    sTree -> Delete(3);
//    sTree -> Delete(3);
//    sTree -> insert(11);
//    sTree -> insert(11);
//    sTree -> insert(4);
//    sTree -> insert(4);
//
//    sTree -> preOrder();
    

        return 0;
}
