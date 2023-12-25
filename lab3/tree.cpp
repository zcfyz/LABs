#include "tree.h"


Node::Node(int data)
{
    this->data = data;
    left = nullptr;
    right = nullptr;
}

BinaryTree::BinaryTree()
{

    root = nullptr;

}

BinaryTree::~BinaryTree()
{
    deleteSubtree(root);
}

void BinaryTree::deleteSubtree(Node* node)
{
    if (node == nullptr) return;

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

void BinaryTree::readFromFile(string filename)
{
    ifstream file(filename);
    if (file.is_open()) {
        string expression;
        getline(file, expression);
        file.close();

        stack<Node*> s;
        Node* currNode = nullptr;
        bool isLeftChild = true;

        for (int i = 0; i < expression.length(); i++) {
            if (expression[i] >= '0' && expression[i] <= '9') {
                // ������� ����� ���� � �������� ���������
                int value = expression[i] - '0';
                Node* newNode = new Node(value);

                if (currNode == nullptr) {
                    // ���� ������� ���� ������ �� ����������, ������ ��� ������
                    root = newNode;
                }
                else {
                    // ���� ������� ���� ������ ����������, ��������� ����� ���� � ����
                    if (isLeftChild) {
                        currNode->left = newNode;
                    }
                    else {
                        currNode->right = newNode;
                    }
                }

                // ������� ���� ���������� ����� �����
                currNode = newNode;
            }
            else if (expression[i] == '(') {
                // ����������� ������, ������� ���� ���������� ������������ ����� ��� ��������� �����
                s.push(currNode);
                isLeftChild = true;
            }
            else if (expression[i] == ')') {
                // ����������� ������, ������������ � ������������� ����
                s.pop();
            }
            else if (expression[i] == ' ') {
                // ������ - ��������� ���� ����� ������ �����
                isLeftChild = false;
            }
        }
    }
    else {
        cout << "Cannot open file!" << endl;
    }
}

void BinaryTree::depthFirstTraversal(Node* node)
{
    if (node == nullptr) return;

    cout << node->data << " ";

    depthFirstTraversal(node->left);
    depthFirstTraversal(node->right);
}

void BinaryTree::traverseDepthFirst()
{
    depthFirstTraversal(root);
    cout << endl;
}

void BinaryTree::createAVLtree(AVLtree& tree)
{
    if (root != NULL)
        createAVLtreeHelp(root, tree);
}

void BinaryTree::createAVLtreeHelp(Node* node, AVLtree& tree)
{
    tree.insert(node->data);
    if (node->left != nullptr || node->right != nullptr) {
        if (node->left != nullptr) {
            createAVLtreeHelp(node->left, tree);
        }
        if (node->right != nullptr) {
            createAVLtreeHelp(node->right, tree);
        }
    }
}


