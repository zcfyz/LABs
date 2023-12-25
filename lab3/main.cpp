#include <iostream>
#include <fstream>
#include "tree.h"
#include "avltree.h"

using namespace std;

int menu()
{
	int ch;
	cout << "Choose the action\n" << endl;

	cout << "1. Insert node\n"
		<< "2. Find node\n"
		<< "3. Delete node\n"
		<< "4. preOrder\n"
		<< "5. inOrder\n"  
		<< "6. postOrder\n"
		<< "7. levelOrder\n"
		<< "8. Output\n"
		<< "9. Exit\n";
		
	
	cout << ">>> ";
	cin >> ch;
	return ch;
}

int main() {
    setlocale(0, "");
    
    BinaryTree binary_tree;
	
	AVLtree AVLtree;
    cout << "Enter file name" << endl;
    string a;
    cin >> a;
    binary_tree.readFromFile(a); 

    cout << "Binary tree: ";
    binary_tree.traverseDepthFirst();

	cout << "AVL-tree:" << endl << endl;
	binary_tree.createAVLtree(AVLtree);
	AVLtree.printTree();
	cout << endl << endl;
	system("pause");
	system("cls");
	while (true) {
		int var = menu();
		switch (var) 
		{
		case 1:
		{	int a;
			cout << "Enter node value: " << endl;
			cin >> a;
			AVLtree.insert(a);
			cout << "Result:" << endl << endl;
			AVLtree.printTree();
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{	int a;
			cout << "Enter node value: ";
			cin >> a;
			AVLtree.search(a); 
			cout << "Result:" << endl << endl;
			AVLtree.printTree();
			cout << endl;
			system("pause");
			system("cls");
			break;

		}
		case 3:
		{
			int a;
			cout << "Enter node: ";
			cin >> a;
			AVLtree.remove(a);
			cout << "Result:" << endl << endl;
			AVLtree.printTree();
			cout << endl;
			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			AVLtree.PreOrder();
			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			AVLtree.InOrder();
			system("pause");
			system("cls");
			break;
		}
		case 6:
		{
			AVLtree.PostOrder();
			system("pause");
			system("cls");
			break;
		}
		case 7:
		{
			AVLtree.Levelorder();
			system("pause");
			system("cls");
			break;

		}
		case 8:
		{
			AVLtree.printTree();
			cout << endl;
			system("pause");
			system("cls");
			break;
		}



		case 9:

			cout << "Exit..." << endl;
			return 0;
			break;
		default:
			system("cls");
			cerr << "Error: invalid choice" << endl;
			break;

		}
	}
    return 0;
}
