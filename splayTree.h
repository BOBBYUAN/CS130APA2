#ifndef splayTree_h
#define splayTree_h
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
using namespace std;
typedef long long lld;
typedef unsigned long long llu;

struct TreeNode
{
    int key;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int key)
    {
        this -> key = key;
        this -> parent = NULL;
        this -> left = NULL;
        this -> right = NULL;
    }
};

class SplayTree
{
    TreeNode *root;
    void zig(TreeNode*);
    void zig_zig(TreeNode*);
    void zig_zag(TreeNode*);
    void splay(TreeNode*);
public:
    SplayTree();
    SplayTree(TreeNode*);
    TreeNode* access(int);
    TreeNode* joint(TreeNode* t1, TreeNode* t2);
    pair<TreeNode*,TreeNode*> split(int x);
    void insert(int);
    void Delete(int);
    void find(int);
    void print();
   // void preOrder();
};

void SplayTree::zig(TreeNode *x)
{
    TreeNode *p = x -> parent;
    if (p -> left == x)
    {
        TreeNode *A = x -> left;
        TreeNode *B = x -> right;
        TreeNode *C = p -> right;
        x -> parent = NULL;
        x -> right = p;
        p -> parent = x;
        p -> left = B;
        if (B != NULL) B -> parent = p;
    }
    else
    {
        TreeNode *A = p -> left;
        TreeNode *B = x -> left;
        TreeNode *C = x -> right;
        x -> parent = NULL;
        x -> left = p;
        p -> parent = x;
        p -> right = B;
        if (B != NULL) B -> parent = p;
    }
}

void SplayTree::zig_zig(TreeNode *x)
{
    TreeNode *p = x -> parent;
    TreeNode *g = p -> parent;
    if (p -> left == x)
    {
        TreeNode *A = x -> left;
        TreeNode *B = x -> right;
        TreeNode *C = p -> right;
        TreeNode *D = g -> right;
        x -> parent = g -> parent;
        x -> right = p;
        p -> parent = x;
        p -> left = B;
        p -> right = g;
        g -> parent = p;
        g -> left = C;
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        if (B != NULL) B -> parent = p;
        if (C != NULL) C -> parent = g;
    }
    else
    {
        TreeNode *A = g -> left;
        TreeNode *B = p -> left;
        TreeNode *C = x -> left;
        TreeNode *D = x -> right;
        x -> parent = g -> parent;
        x -> left = p;
        p -> parent = x;
        p -> left = g;
        p -> right = C;
        g -> parent = p;
        g -> right = B;
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        if (B != NULL) B -> parent = g;
        if (C != NULL) C -> parent = p;
    }
}

void SplayTree::zig_zag(TreeNode *x)
{
    TreeNode *p = x -> parent;
    TreeNode *g = p -> parent;
    if (p -> right == x)
    {
        TreeNode *A = p -> left;
        TreeNode *B = x -> left;
        TreeNode *C = x -> right;
        TreeNode *D = g -> right;
        x -> parent = g -> parent;
        x -> left = p;
        x -> right = g;
        p -> parent = x;
        p -> right = B;
        g -> parent = x;
        g -> left = C;
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        if (B != NULL) B -> parent = p;
        if (C != NULL) C -> parent = g;
    }
    else
    {
        TreeNode *A = g -> left;
        TreeNode *B = x -> left;
        TreeNode *C = x -> right;
        TreeNode *D = p -> right;
        x -> parent = g -> parent;
        x -> left = g;
        x -> right = p;
        p -> parent = x;
        p -> left = C;
        g -> parent = x;
        g -> right = B;
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        if (B != NULL) B -> parent = g;
        if (C != NULL) C -> parent = p;
    }
}

void SplayTree::splay(TreeNode *x)
{
    while (x -> parent != NULL)
    {
        TreeNode *p = x -> parent;
        TreeNode *g = p -> parent;
        if (g == NULL) zig(x);
        else if (g -> left == p && p -> left == x) zig_zig(x);
        else if (g -> right == p && p -> right == x) zig_zig(x);
        else zig_zag(x);
    }
    this -> root = x;
}

SplayTree::SplayTree()
{
    this -> root = NULL;
}

SplayTree::SplayTree(TreeNode *rt)
{
    this -> root = rt;
}

TreeNode* SplayTree::access(int x)
{
    TreeNode *ret = NULL;
    TreeNode *curr = this -> root;
    TreeNode *prev = NULL;
    while (curr != NULL)
    {
        prev = curr;
        if (x < curr -> key) curr = curr -> left;
        else if (x > curr -> key) curr = curr -> right;
        else
        {
            ret = curr;
            break;
        }
    }
    if (ret != NULL) splay(ret);
    else if (prev != NULL) splay(prev);
    return ret;
}

void SplayTree::find(int x)
{
    if (access(x) != NULL) {
        cout << "item " << x << " found" << endl;
    } else {
        cout << "item " << x << " not found" << endl;
    }
}

TreeNode* subtree_max(TreeNode *subRoot)
{
    TreeNode *curr = subRoot;
    while (curr -> right != NULL) curr = curr -> right;
    return curr;
}

TreeNode* subtree_min(TreeNode *subRoot)
{
    TreeNode *curr = subRoot;
    while (curr -> left != NULL) curr = curr -> left;
    return curr;
}

TreeNode* SplayTree::joint(TreeNode *t1, TreeNode *t2)
{
    TreeNode *M = subtree_max(t1);
    splay(M);
    M->right = t2;
    t2->parent = M;
    t1->parent = NULL;
    return M;
}

pair<TreeNode*,TreeNode*> SplayTree::split(int x)
{
    TreeNode *leftTree = NULL;
    TreeNode *rightTree = NULL;
    TreeNode *split = access(x);
    
    if (split != NULL) {
        cout << "item " << x << " not inserted; already present" << endl;
        leftTree = split->left;
        rightTree = split->right;
        return make_pair(leftTree, rightTree);
    } else {
        TreeNode *curr = this->root;
        if (curr->key > x) {
            leftTree = curr->left;
            curr->left = NULL;
            rightTree = curr;
        } else {
            rightTree = curr->right;
            curr->right = NULL;
            leftTree = curr;
        }
        cout << "item " << x << " inserted" << endl;
        return make_pair(leftTree, rightTree);
    }
}

void SplayTree::insert(int x)
{
    if (root == NULL) {
        root = new TreeNode(x);
        cout << "item " << x << " inserted" << endl;
        return;
    }
    TreeNode *leftTree = NULL;
    TreeNode *rightTree = NULL;
    pair<TreeNode*, TreeNode*> v = split(x);
    leftTree = v.first;
    rightTree = v.second;
    root = new TreeNode(x);
    root->left = leftTree;
    if (leftTree != NULL) {
        leftTree->parent = root;
    }
    root->right = rightTree;
    if (rightTree != NULL) {
        rightTree->parent = root;
    }
  
}

void SplayTree::Delete(int x)
{
    TreeNode *del = access(x);
    if (del == NULL) {
        cout << "item " << x << " not deleted; not present" << endl;
        return;
    }
    TreeNode *leftTree = del->left;
    TreeNode *rightTree = del->right;
    if (leftTree == NULL && rightTree == NULL)
    {
        this -> root = NULL;
    }
    else if (leftTree == NULL)
    {
        rightTree->parent = NULL;
        this->root = rightTree;
    }
    else if (rightTree == NULL)
    {
        leftTree->parent = NULL;
        this->root = leftTree;
    }
    else
    {
        this->root = joint(leftTree, rightTree);
    }
    cout << "item " << x << " deleted" << endl;
    delete del;
}

void SplayTree::print()
{
    if (root == NULL) return;
    
    queue<TreeNode *> q;

    q.push(root);
    
    while (q.empty() == false)
    {
     
        int nodeCount = q.size();
        
        while (nodeCount > 0)
        {
            TreeNode *node = q.front();
            cout << node->key << " ";
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
            nodeCount--;
        }
        cout << endl;
    }
}

//void SplayTree::print()
//{
//    queue<TreeNode*> orderQueue;
//    if (root == NULL) {
//        return;
//    } else {
//        TreeNode *current = root;
//        TreeNode *pre = NULL;
//        orderQueue.push(current);
//        while (current != NULL) {
//            if (current->left != NULL) {
//                orderQueue.push(current->left);
//            }
//            if (current->right != NULL) {
//                orderQueue.push(current->right);
//            }
//            if (pre == NULL) {
//                cout << current->key;
//            } else if (current->parent == pre->parent) {
//                cout << current->key << " ";
//            } else {
//                cout << endl;
//                cout << current->key << " ";
//            }
//            pre = current;
//            orderQueue.pop();
//            current = orderQueue.front();
//            if (orderQueue.empty()) {
//                break;
//            }
//        }
//    }
//}

#endif /* splayTree_h */
