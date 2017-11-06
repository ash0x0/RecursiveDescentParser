/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTree.h
 * Author: ahmed
 *
 * Created on November 6, 2017, 7:23 PM
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
        class treeNode {
            public:
                keyType key; 		
                dataType data;		
                treeNode *left;		
                treeNode *right;	
        }; 
        typedef treeNode * NodePointer;
        NodePointer root;
	bool mFind (NodePointer , const keyType &) const;
	bool mGet (NodePointer , const keyType & , dataType &) const;
	bool mAdd (NodePointer &, const keyType &, const dataType &);
        void mTraverse (NodePointer ) const; 
        void mDraw (int ,NodePointer ) const;
        void findParent 
        ( const keyType &k, bool &found, NodePointer &locptr, NodePointer &parent) const;
}; 

#endif 
