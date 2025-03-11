/* BST.h --------------------------------------------------------------
    CPP file that contains the declaration of class BST and definitions
    of all of its member functions.
---------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

template <typename DataType>
class BST {
   public:
      /***** Public Function Members *****/
      // BST() -- the default constructor; constructs a BST object
      BST();

      // empty() -- checks if the BST is empty
      bool empty() const;  

      // search() -- searches the BST for an item
      bool search(const DataType & item) const;

      // insert() -- iserts an item into the BST
      void insert(const DataType & item);

      // remove() -- removes an item from the BST
      void remove(const DataType & item);

      // preorder() -- preorder traversal of BST
      void preorder(ostream & out) const;

      // countLeaves() -- counts the number of leaves in the BST
      int countLeaves() const;

      // getSibling() -- prints to console whether or not a node has a sibling; if the node has a sibling, then it is printed
      void getSibling(const DataType & item) const;
   
   private:
      /***** Node class *****/
      class Node {
         public:
            DataType data;
            Node * left;
            Node * right;

            // Node's Default Constructor
            Node() : left(0), right(0) {}

            // Node's Explicit Value Constructor
            Node(DataType item) : data(item), left(0), right(0) {}
      }; // End of class Node declaration

      typedef Node * NodePointer; 

      /***** Private Function Members *****/
      // search2() -- Locates a node containing item and its parent
      void search2(const DataType & item, bool & found, NodePointer & locptr, NodePointer & parent) const;

      // preorderAux() -- Preorder traversal auxiliary function
      void preorderAux(ostream & out, NodePointer subtreePtr) const;

      // countLeavesAux() -- countLeaves auxiliary function
      int countLeavesAux(NodePointer subtreeRoot, int &numberOfLeaves) const;

      // getParent() -- gets the parent of a node
      NodePointer getParent(NodePointer subtreeRoot, NodePointer node) const;


      /***** Private Data Members *****/
      NodePointer myRoot; 

}; // End of class BST declaration



//--- Definition of BST's Default Constructor
template <typename DataType>
BST<DataType>::BST() {
   myRoot = 0;
}

//--- Definition of BST's empty()
template <typename DataType>
bool BST<DataType>::empty() const { 
   return myRoot == 0; 
}

//--- Definition of BST's search()
template <typename DataType>
bool BST<DataType>::search(const DataType & item) const {
   BST<DataType>::NodePointer locptr = myRoot;
   bool found = false;
   while (!found && locptr != 0) {
      if (item < locptr->data) {
         locptr = locptr->left;
      }
      else if (locptr->data < item) {
         locptr = locptr->right;
      }
      else {
         found = true;
      }
   }
   return found;
}

//--- Definition of BST's insert()
template <typename DataType>
void BST<DataType>::insert(const DataType & item) {
   BST<DataType>::NodePointer locptr = myRoot;
   BST<DataType>::NodePointer parent = 0;
   bool found = false;
   while (!found && locptr != 0) {
      parent = locptr;
      if (item < locptr->data) {
         locptr = locptr->left;
      }
      else if (locptr->data < item) {
         locptr = locptr->right;
      }
      else {
         found = true;
      }
   }
   if (!found) {
      locptr = new BST<DataType>::Node(item);  
      if (parent == 0) {
         myRoot = locptr;
      }
      else if (item < parent->data) {
         parent->left = locptr;
      }
      else {
         parent->right = locptr;
      }
   }
   else {
      cout << "The item is already in the tree\n";
   }
}

//--- Definition of BST's remove()
template <typename DataType>
void BST<DataType>::remove(const DataType & item) {
   bool found;
   BST<DataType>::NodePointer x;
   BST<DataType>::NodePointer parent;
   search2(item, found, x, parent);

   if (!found) {
      cout << "Item not in the BST\n";
      return;
   }

   if (x->left != 0 && x->right != 0) {                                
      BST<DataType>::NodePointer xSucc = x->right;
      parent = x;
      while (xSucc->left != 0) {
         parent = xSucc;
         xSucc = xSucc->left;
      }
     x->data = xSucc->data;
     x = xSucc;
   }

   BST<DataType>::NodePointer subtree = x->left;
   if (subtree == 0) {
      subtree = x->right;
   }
   if (parent == 0) {
      myRoot = subtree;
   }
   else if (parent->left == x) {
      parent->left = subtree;
   } 
   else {
      parent->right = subtree;
   }
   delete x;
}

//--- Definition of BST's preorder()
template <typename DataType>
void BST<DataType>::preorder(ostream & out) const { 
   preorderAux(out, myRoot); 
}

//--- Definition of search2()
template <typename DataType>
void BST<DataType>::search2(const DataType & item, bool & found, BST<DataType>::NodePointer & locptr, BST<DataType>::NodePointer & parent) const {
   locptr = myRoot;
   parent = 0;
   found = false;

   while (!found && locptr != 0) {
      if (item < locptr->data) {
         parent = locptr;
         locptr = locptr->left;
      }
      else if (locptr->data < item) {
         parent = locptr;
         locptr = locptr->right;
      }
      else {
         found = true;
      }
   }
}

//--- Definition of BST's preorderAux()
template <typename DataType>
void BST<DataType>::preorderAux(ostream & out, BST<DataType>::NodePointer subtreeRoot) const {
   if (subtreeRoot != 0) {
      out << subtreeRoot->data << "\t\t";      // V operation

      if (subtreeRoot->left != nullptr) {
         out << (subtreeRoot->left)->data << "\t\t";
      }
      else if (subtreeRoot->left == nullptr) {
         out << "NIL" << "\t\t";
      }
      if (subtreeRoot->right != nullptr) {
         out << (subtreeRoot->right)->data << endl;
      }
      else if (subtreeRoot->right == nullptr) {
         out << "NIL" << endl;
      }

      preorderAux(out, subtreeRoot->left);    // L operation
      preorderAux(out, subtreeRoot->right);   // R operation
    }
}

//--- Definition of BST's countLeaves()
template <typename DataType>
int BST<DataType>::countLeaves() const {
   int numberOfLeaves = 0;
   return countLeavesAux(myRoot, numberOfLeaves);
}

//--- Definition of BST's countLeavesAux()
template <typename DataType>
int BST<DataType>::countLeavesAux(BST<DataType>::NodePointer subtreeRoot, int &numberOfLeaves) const {
   if (subtreeRoot != 0) {
      if ((subtreeRoot->left == nullptr) && (subtreeRoot->right == nullptr)) {    // V operation
         ++numberOfLeaves;
      }

      countLeavesAux(subtreeRoot->left, numberOfLeaves);    // L operation
      countLeavesAux(subtreeRoot->right, numberOfLeaves);   // R operation
   }

   return numberOfLeaves;
}

//--- Definition of BST's getSibling()
template <typename DataType>
void BST<DataType>::getSibling(const DataType & item) const {
   BST<DataType>::NodePointer locptr = myRoot;
   BST<DataType>::NodePointer nodeOfItem = 0;
   BST<DataType>::NodePointer parent;
   bool found = false;

   while (!found && locptr != 0) {
      if (item < locptr->data) {          // descend left
         locptr = locptr->left;
      }
      else if (locptr->data < item) {     // descend right
         locptr = locptr->right;
      }
      else {
         nodeOfItem = locptr;             // item found
         found = true;
      }
   }

   if ((!found) || (nodeOfItem == 0)) {
      cout << item << " is not in the tree." << endl;
      return;
   }

   parent = getParent(myRoot, nodeOfItem);
   
   if (parent == 0) {
      cout << item << " has no sibling (it is the root of the BST)." << endl;
   } 
   else {
      if (parent->left == nodeOfItem) {
         if (parent->right != 0) {
            cout << "The sibling of " << item << " is " << (parent->right)->data << "." << endl;
         } else {
            cout << item << " has no sibling." << endl;
         }
      } else if (parent->right == nodeOfItem) {
         if (parent->left != 0) {
            cout << "The sibling of " << item << " is " << (parent->left)->data << "." << endl;
         } else {
            cout << item << " has no sibling." << endl;
         }
      }
   }
}

//--- Definition of BST's getParent()
template <typename DataType>
typename BST<DataType>::NodePointer BST<DataType>::getParent(BST<DataType>::NodePointer subtreeRoot, BST<DataType>::NodePointer node) const {
   if (subtreeRoot == nullptr) {
      return nullptr;
   }

   if (subtreeRoot->left == node || subtreeRoot->right == node) {
      return subtreeRoot;
   }

   if (node->data < subtreeRoot->data) {
      return getParent(subtreeRoot->left, node);
   }
   else if (node->data > subtreeRoot->data) {
      return getParent(subtreeRoot->right, node);
   }

   return nullptr;
}


