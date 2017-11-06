/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTree.h
 * Author: ahmed
 *
 * Created on November 2, 2017, 7:23 PM
 */
#ifndef BIN_TREE_H
#define BIN_TREE_H

template <class keyType, class dataType>

class binaryTree {   
    public:
        binaryTree();  
        bool add (const keyType &, const dataType &);
        bool clear() const;
        bool find (const keyType &) const;
        bool get (const keyType &, dataType &) const;
        void traverse() const;
        void preorder () const;
        void inorder () const;
        void draw() const;
        void deleteItem (const keyType &);
    private:
        class node {
            public:
                keyType key;
                dataType data;		
                node* left;		
                node* right;	
        }; 
        typedef node * pointer;
        pointer root;
	bool mFind (pointer , const keyType &) const;
	bool mGet (pointer , const keyType & , dataType &) const;
	bool mAdd (pointer &, const keyType &, const dataType &);
        void mTraverse (pointer ) const; 
        void mDraw (int ,pointer ) const;
        void findParent 
        ( const keyType &k, bool &found, pointer &locptr, pointer &parent) const;
}; 

#endif 
