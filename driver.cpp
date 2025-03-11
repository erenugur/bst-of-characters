/*--------------------------------------------------------------------------
      Driver program to test the functionalities of the BST.
 -------------------------------------------------------------------------*/

#include <iostream>
#include "BST.h"
using namespace std;

int main() {
    BST<char> charBST;
    int option;
    
    while (option != 7) {
        cout << "-------------------- MENU ----------------------" << endl <<
                "\t\t1. Insert node(s)" << endl <<
                "\t\t2. Traverse Preorder" << endl <<
                "\t\t3. Search BST" << endl <<
                "\t\t4. Delete node" << endl <<
                "\t\t5. Leaf Count" << endl <<
                "\t\t6. Sibling of a node" << endl <<
                "\t\t7. Quit" << endl <<
                "\t\tEnter your choice: ";

        cin >> option;
        cout << "\n";

        if (option == 1) {
            int numNodes;
            char item;

            cout << "Enter number of nodes to insert: ";
            cin >> numNodes;

            int i = 0;
            while (i < numNodes) {
                cout << "Enter node: ";
                cin >> item;
                if (charBST.search(item)) {
                    cout << item << " is already in the BST." << endl;
                }
                else {
                    charBST.insert(item);
                    cout << "Inserted." << endl;
                    ++i;
                }
            }
            cout << "\n";
        }
        else if (option == 2) {
            cout << "            Traversing Preorder" << endl;
            cout << "Node Info   Left Child Info   Right Child Info" << endl;
            cout << "---------   ---------------   ---------------" << endl;
            charBST.preorder(cout);
            cout << "\n";
        }
        else if (option == 3) {
            char item;
            cout << "Enter item you want to search for: ";
            cin >> item;
            if (charBST.search(item)) {
                cout << item << " is found in the BST." << endl << endl;
            }
            else {
                cout << item << " is not found in the BST." << endl << endl;
            }
        }
        else if (option == 4) {
            char item;
            cout << "Enter item you want to delete: ";
            cin >> item;
            if (charBST.search(item)) {
                charBST.remove(item);
                cout << item << " is deleted." << endl << endl;
            }
            else {
                cout << item << " is not found in the BST." << endl << endl;
            }
        }
        else if (option == 5) {
            int numLeaves = charBST.countLeaves();
            cout << "There are " << numLeaves << " number of leaves in the BST." << endl << endl;
        }
        else if (option == 6) {
            char item;
            cout << "Enter item you want to find the sibling of: ";
            cin >> item;
            charBST.getSibling(item);
            cout << "\n";
        }
        else if (option == 7) {
            break;
        }
        else {
            cout << "Invalid input." << endl;
            break;
        }
    }
    
    return 0;
}
