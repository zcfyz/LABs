#include <iostream>
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "avltree.h"

using namespace std;
class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int data); //�������� ����
};

class BinaryTree {
private:
    Node* root;

public:
    BinaryTree();
    ~BinaryTree();// ���������� ������� ��� ���� ������;
    void deleteSubtree(Node* node);// ����������� ������� �������� ���������
    void readFromFile(string filename);// ������� ������ ����������� ��������� ������ �� ����� � �������� ������
    void depthFirstTraversal(Node* node);// ����������� ������� ������ � ������� (���������� �����)
    void traverseDepthFirst();// ������� ������ ������ � ������� (���������� �����)
    void createAVLtree(AVLtree& tree); //������� ��� ������
    void createAVLtreeHelp(Node* node, AVLtree& tree); // ��������������� ������� ��� �������� ��� ������
};


    
