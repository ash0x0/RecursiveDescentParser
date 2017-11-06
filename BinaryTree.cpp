/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTree.cpp
 * Author: ahmed
 * 
 * Created on November 2, 2017, 7:23 PM
 */
#include <iostream>
#include <iomanip>
#include <stack>
#include <queue>
#include "BinaryTree.h"
using namespace std;

template <class keyType, class dataType>
binaryTree<keyType, dataType>::binaryTree() { root = NULL; }

template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::find(const keyType &k) const {
   return mFind(root, k);
} 

template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::mFind (pointer aRoot, const keyType &k) const {
    if (aRoot == NULL) return false;
    else if (k == aRoot->key) return true;
    else if (k < aRoot->key) return mFind(aRoot->left, k);
    else return mFind(aRoot->right, k);
} 

template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::get(const keyType &k, dataType &d) const {
   return mGet(root, k, d);
} 

template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::mGet(pointer aRoot, const keyType &k, dataType &d) const {
    if (aRoot == NULL) return false;
    else if (k == aRoot->key){ 
        d = aRoot->data; 
        return true;
    }
    else if (k < aRoot->key) return mGet(aRoot->left, k, d);
    else return mGet(aRoot->right,k, d);
} 

template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::add(const keyType &k, const dataType &d) {
	return mAdd (root, k , d);
} 

template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::mAdd(pointer &aRoot, const keyType &k, const dataType &d) {
    if (aRoot == NULL) { 
      aRoot = new node;
      aRoot->left = NULL;
      aRoot->right = NULL;
      aRoot->key = k;
      aRoot->data = d;
      return true;
    }
    else if (k == aRoot->key) return false;
    else if (k < aRoot->key) return mAdd (aRoot->left, k, d);
    else return mAdd (aRoot->right, k, d);
} 

template <class keyType, class dataType>
bool binaryTree<keyType, dataType>::clear() const {
   return(root == NULL);
} 

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::traverse() const {
   mTraverse (root);
} 

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::mTraverse (pointer aRoot) const {
    if (aRoot != NULL) { 
        mTraverse (aRoot->left);
        cout << aRoot->key << " " << aRoot->data << endl;
        mTraverse (aRoot->right);
    }
} 

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::preorder () const {
    stack<pointer> s;
    pointer t = root;
    s.push(t);
    int i=0;
    while(!s.empty()) {
        t=s.top(); s.pop();
        cout << t->key;
        if ( t->right != NULL ) { 
            cout<<"\n"; s.push(t->right); 
            for (int g = 0; g < i; ++g) cout<<"  ";
        }
        if ( t->left  != NULL ) { 
            cout<<"\n"; 
            s.push (t->left); 
            for (int g = 0; g < i+1; ++g) cout<<"  ";
        }
        i++;
    }
}


template <class keyType, class dataType>
void binaryTree<keyType, dataType>::inorder () const {
    queue<pointer> q;
    pointer t = root;
    q.push(t);
    while(!q.empty()) {
        t=q.front(); q.pop(); cout << t->key << endl;
        if ( t->left  != NULL ) q.push (t->left);
        if ( t->right != NULL ) q.push (t->right);
    }
}

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::draw() const {
    mDraw (0 , root);
}

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::mDraw(int indent, pointer aRoot) const {
    if (aRoot != NULL) { 
        mDraw (indent+8, aRoot->right);
        cout << setw(indent) << " " << aRoot->key << endl;
        mDraw (indent+8, aRoot->left);
    }
}

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::deleteItem (const keyType &k) {
    bool found;
    pointer x,parent;
    findParent (k, found, x, parent);
    if (!found) {
        cout << "Not found in tree" << endl;
        return;
    }

    if ((x->left != NULL)&&(x->right != NULL)) {
        pointer xSucc = x->right;
        parent = x;
        while (xSucc->left != NULL) { 
            parent = xSucc; 
            xSucc = xSucc->left; 
        }
        x->key = xSucc->key; 
        x->data = xSucc->data;
        x = xSucc;
    }

    pointer subtree = x->left; 
    if (subtree == NULL) subtree = x->right;
    if (parent == NULL) root = subtree; 
    else if (parent->left == x) parent->left = subtree;
    else parent->right = subtree; 
    delete x;
} 

template <class keyType, class dataType>
void binaryTree<keyType, dataType>::findParent (const keyType &k, bool &found, pointer &locptr, pointer &parent) const {
    locptr = root;  parent = NULL; found = false;
    while (!found && locptr != NULL) {
        if (k < locptr->key) {
            parent = locptr;	
            locptr = locptr->left;
        }
        else if (locptr->key < k) {
            parent = locptr;	
            locptr = locptr->right;
        }
        else found = true; 
    }
} 