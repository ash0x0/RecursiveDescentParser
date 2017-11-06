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

class binaryTree
{   

   public:
	        
      
      
      binaryTree();

      
      bool insert (const keyType &, const dataType &);

      
      bool empty() const;

      
      bool search (const keyType &) const;

	  
      bool retrieve (const keyType &, dataType &) const;
	  
	  
      void traverse() const;

	  
	  void preorder () const;

	  
	  void levelorder () const;

	  
      void graph() const;

	  
      void remove (const keyType &);

      
   private:
      
	   class treeNode
	   {
		public:
			keyType key; 		
			dataType data;		
			treeNode *left;		
			treeNode *right;	
	   }; 

	   typedef treeNode * NodePointer;
	 
      NodePointer root;
	  
      

      
      bool search2 (NodePointer , const keyType &) const;
	  
      
      bool retrieve2 (NodePointer , const keyType & , dataType &) const;
	  
	  
      bool insert2 (NodePointer &, const keyType &, const dataType &);

	  
      void traverse2 (NodePointer ) const; 

	  
	  void graph2 (int ,NodePointer ) const;

	  
      void parentSearch ( const keyType &k, bool &found, 
							NodePointer &locptr, NodePointer &parent) const;


}; 

#endif 
