/*
	Dylan Bush & Adam Rucker
	4/10/2017
	Lab 11/ Binary Search Tree /Tree sort labs
*/	
#if !defined (BINARYSEARCHTREE_H)
#define BINARYSEARCHTREE_H

#include "BinaryTreeIterator.h"
#include "TreeNode.h"
#include "Text.h"
using CSC2110::String;
#include "Line.h"
#include "Drawable.h"
#include "wx/wx.h"


template < class T >
class BinarySearchTree : public Drawable
{

   private:
      TreeNode<T>* root;
      int sze;
      void destroyItem(TreeNode<T>* tNode);
      void destroy();

      TreeNode<T>* insertItem(TreeNode<T>* tNode, T* item);
      TreeNode<T>* removeItem(TreeNode<T>* tNode, String* sk);
      TreeNode<T>* removeNode(TreeNode<T>* tNode);
      TreeNode<T>* removeLeftMost(TreeNode<T>* tNode);
      T* findLeftMost(TreeNode<T>* tNode);

      TreeNode<T>* getRootNode();
      void setRootNode(TreeNode<T>* tNode);
      int getHeight(TreeNode<T>* tNode);
      bool isBalanced(TreeNode<T>* tNode);

      int (*compare_items) (T* item_1, T* item_2);
      int (*compare_keys) (String* key, T* item);

      void drawRec(TreeNode<T>* tNode, wxDC& dc, Line* line, int x_parent, int x_curr, int y_curr);

   public:
      BinarySearchTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));
      ~BinarySearchTree();

      bool isEmpty();
      void makeEmpty();

      T* retrieve(String* search_keys);
      void insert(T* item);
      void remove(String* search_keys);

      BinaryTreeIterator<T>* iterator();
      T* getRootItem();
      int getHeight();
      bool isBalanced();

      T** toArray();
      static T** treeSort(T** items, int num_itemss, int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item));

      void draw(wxDC& dc, int width, int height);
      void mouseClicked(int x, int y);
};
/*
Pre:Receives a String* search key
Post: Removes the item from the binary search tree
*/
template < class T >
void BinarySearchTree<T>::remove(String* sk)
{
   //DO THIS
   TreeNode<T>* current = getRootNode();
   current = removeItem(current, sk);
   sze--;
   setRootNode(current);
  /* TreeNode<T>* prev = getRootNode();
   int comparison = compare_keys(sk, current->getItem());
   while(current != NULL)
   {
	   if(comparison == 0)
	   {
		   cout<<"Found it "<<endl;
		   if(current == getRootNode())
		   {
			   current = removeNode(current);
			   setRootNode(current);
		   }
		   else if(prev->getRight() == current)
		   {
				current = removeNode(current);
			

			prev->setRight(current);
		   }else if(prev->getLeft() == current)
		   {
			   current = removeNode(current);
			   prev->setLeft(current);
		   }
		   return;
	   }
	   else if(comparison > 0)
	   {
		   prev = current;
		   current = current->getRight();
	   }else if(comparison < 0)
	   {
		   prev = current;
		   current = current->getLeft();
	   }
	   if(current != NULL)
		   comparison = compare_keys(sk, current->getItem());
   }*/
}
/*
Pre:Receives a String* search key and a tNode
Post: Removes the item from the binary search tree
*/
template < class T >
TreeNode<T>* BinarySearchTree<T>::removeItem(TreeNode<T>* tNode, String* sk)
{
   //DO THIS
   if(tNode == NULL) 
	   return NULL;
   int comparison = compare_keys(sk, tNode->getItem());
   if(comparison == 0)
    {
		tNode = removeNode(tNode);
		return tNode;
	}
	else if(comparison < 0)
	{
		TreeNode<T>* left = tNode->getLeft();
		left = removeItem(left, sk);
		tNode->setLeft(left);
	}
	else if(comparison > 0)
	{
		TreeNode<T>* right = tNode->getRight();
		right = removeItem(right, sk);
		tNode->setRight(right);
	}
	return tNode;
}
/*
Pre:Receives a TreeNode<T>* 
Post: Removes the TreeNode from the binary search tree and returns its children in the correct order
*/
template < class T >
TreeNode<T>* BinarySearchTree<T>::removeNode(TreeNode<T>* tNode)
{
   if (tNode->getLeft() == NULL && tNode->getRight() == NULL)
   {
      delete tNode;
	  tNode->setItem(NULL);
      return NULL;
   }
   else if (tNode->getLeft() == NULL)
   {
      TreeNode<T>* temp = tNode->getRight();
      tNode->setItem(NULL);
	  tNode->setRight(NULL);
	  delete tNode;
      return temp;
   }
   else if (tNode->getRight() == NULL)
   {
      TreeNode<T>* temp = tNode->getLeft();
	  tNode->setItem(NULL);
	  tNode->setLeft(NULL);
      delete tNode;
      return temp;
   }
   else
   {
      //DO THIS
	  
	  TreeNode<T>* temp = tNode->getRight();
	  T* item = findLeftMost(temp);
	  tNode->setRight(removeLeftMost(tNode->getRight()));
	  tNode->setItem(item);
	  return tNode;
   }
}
/*
Pre: receives a tNode
Post: finds the leftmost tree node
*/
template < class T >
T* BinarySearchTree<T>::findLeftMost(TreeNode<T>* tNode)
{
   //DO THIS (use a while loop)
   while(tNode->getLeft() != NULL)
   {
	   tNode = tNode->getLeft();
   }
   return tNode->getItem();
}
/*
	Pre:Receives a tNode
	Post:Removes the Tree Node at the leftmost part of the tree
*/	
template < class T >
TreeNode<T>* BinarySearchTree<T>::removeLeftMost(TreeNode<T>* tNode)
{
   //DO THIS (recursion)
   
   TreeNode<T>* left = tNode->getLeft();
   if(left == NULL)
   {
	   tNode = removeNode(tNode);
	   return tNode;
   }
	TreeNode<T>* subtree = removeLeftMost(left);
	tNode->setLeft(subtree);
	return tNode;



}
/*
	Pre:
	Post: Returns an array of items that are in the correct order
*/	
template < class T >
T** BinarySearchTree<T>::toArray()
{
   ///////
   
   T** array = new T*[sze];
   /*
   TreeNode<T>* current = getRootNode();
 for (int i=0;i<sze;i++)
  {
          current=findLeftMost(current);
          array[i]=current;
   }
   */
   BinaryTreeIterator<T>* iterator1 = iterator();
   iterator1->setInorder();
   int counter = 0;
   while(iterator1->hasNext())
   {
	   array[counter] = iterator1->next();
	   counter++;
   }
   delete iterator1;
   return array;


}
/*
	Pre:Receives an array of items, number of items, and the ways to compare items
	Post: Sorts the array of items
*/	
template < class T >
T** BinarySearchTree<T>::treeSort(T** items, int num_items, int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   //DO THIS
   BinarySearchTree<T>* bst = new BinarySearchTree<T>(comp_items, comp_keys);
   for(int i = 0; i < num_items; i++)
   {
		bst->insert(items[i]);
   }
   T** sorted_items =  bst->toArray();
   delete bst;
   return sorted_items;
}

template < class T >
int BinarySearchTree<T>::getHeight()
{
   return getHeight(getRootNode());
}

template < class T >
int BinarySearchTree<T>::getHeight(TreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return 0;
   }
   else
   {
       int left = getHeight(tNode->getLeft());
       int right = getHeight(tNode->getRight());

       if (left >= right)
       {
           return left + 1;
       }
       else
       {
          return right + 1;
       }
   }
}

template < class T >
bool BinarySearchTree<T>::isBalanced()
{
    bool bal = isBalanced(root);
    return bal;
}

template < class T >
bool BinarySearchTree<T>::isBalanced(TreeNode<T>* tNode)
{
   if (tNode == NULL)
   {
       return true;
   }

   TreeNode<T>* left = tNode->getLeft();
   TreeNode<T>* right = tNode->getRight();

   bool left_bal = isBalanced(left);
   if (left_bal == false)
   {
      return false;
   }

   bool right_bal = isBalanced(right);
   if (right_bal == false)
   {
      return false;
   }

   int lh = getHeight(left);
   int rh = getHeight(right);
   if (abs(lh - rh) > 1)
   {
      return false;
   }

   return true;
}

template < class T >
BinarySearchTree<T>::BinarySearchTree(int (*comp_items) (T* item_1, T* item_2), int (*comp_keys) (String* key, T* item))
{
   root = NULL;
   sze = 0;

   compare_items = comp_items;
   compare_keys = comp_keys;
}

template < class T >
BinarySearchTree<T>::~BinarySearchTree()
{
   destroy();
}

template < class T >
void BinarySearchTree<T>::destroy()
{
   destroyItem(root);
}

template < class T >
void BinarySearchTree<T>::destroyItem(TreeNode<T>* tNode)
{
   if (tNode != NULL)
   {
      destroyItem(tNode->getLeft());
      destroyItem(tNode->getRight());
      delete tNode;
   }
}

template < class T >
bool BinarySearchTree<T>::isEmpty()
{
   return sze == 0;
}

template < class T >
void BinarySearchTree<T>::makeEmpty()
{
   destroy();
   root == NULL;
   sze = 0;
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::getRootNode()
{
   return root;
}

template < class T >
void BinarySearchTree<T>::setRootNode(TreeNode<T>* tNode)
{  
   root = tNode;
}

template < class T >
T* BinarySearchTree<T>::getRootItem()
{
   T* rootItem = root->getItem();
   return rootItem;
}

template < class T >
void BinarySearchTree<T>::insert(T* item)
{
   root = insertItem(root, item);
}

template < class T >
T* BinarySearchTree<T>::retrieve(String* sk)
{
   TreeNode<T>* tNode = getRootNode();

   while (tNode != NULL)
   {
      T* node_items = tNode->getItem();
      int comp = (*compare_keys) (sk, node_items);

      if (comp == 0)
      {
         //no duplicate search keys allowed, so do nothing
         return node_items;
      }
      else if (comp < 0)
      {
         tNode = tNode->getLeft();
      }
      else
      {
         tNode = tNode->getRight();
      }
   }

   return NULL; //item is not in the tree
}

template < class T >
TreeNode<T>* BinarySearchTree<T>::insertItem(TreeNode<T>* tNode, T* item)
{
   TreeNode<T>* subtree;
   if (tNode == NULL)
   { 
      sze++;
      return new TreeNode<T>(item);
   }

   T* node_items = tNode->getItem();
   int comp = (*compare_items) (item, node_items);

   if (comp == 0)
   {
      //no duplicate search keys allowed, so do nothing
      return tNode;
   }
   else if (comp < 0)
   {
      subtree = insertItem(tNode->getLeft(), item);
      tNode->setLeft(subtree);
   }
   else
   {
      subtree = insertItem(tNode->getRight(), item);
      tNode->setRight(subtree);
   }
   
   return tNode;
}

template < class T >
BinaryTreeIterator<T>* BinarySearchTree<T>::iterator()
{
   return new BinaryTreeIterator<T>(root);
}

template < class T >
void BinarySearchTree<T>::draw(wxDC& dc, int width, int height)
{
   Line line(new Color(0, 0, 0), 5.0);
   drawRec(getRootNode(), dc, &line, width, width/2, 20);
}

template < class T >
void BinarySearchTree<T>::drawRec(TreeNode<T>* tNode, wxDC& dc, Line* line, int x_parent, int x_curr, int y_curr)
{

   //traversal to draw the entire binary tree
   if (tNode != NULL)
   {
      //computing the location of the current node's two children
      //the distance between a node's two children is the same as the horizontal distance between
      //the current node and the current node's parent
      //need to do this first as the drawing is from the bottom to the top
      int separation = abs(x_curr - x_parent);

      //need to make sure that the children are symmetrically placed with respect to the parent
      int x_left = x_curr - separation/2;  //the location of the left child
      int x_right = x_left + separation;   //the location of the right child

      //compute the vertical location of the current node's parent
      //and the current node's two children
      int y_parent = y_curr - 50;
      int y_children = y_curr + 50;

      //draw the line connecting the current node to its parent
      if (tNode != root)
      {
         line->draw(dc, x_curr, y_curr, x_parent, y_parent);
      }

      //draw the children
      drawRec(tNode->getLeft(), dc, line, x_curr, x_left, y_children);
      drawRec(tNode->getRight(), dc, line, x_curr, x_right, y_children);

      //draw tNode
      tNode->draw(dc, x_curr, y_curr);
   }
}

template < class T >
void BinarySearchTree<T>::mouseClicked(int x, int y) {}
#endif