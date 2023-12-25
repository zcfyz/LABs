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
    Node(int data); //создание узла
};

class BinaryTree {
private:
    Node* root;

public:
    BinaryTree();
    ~BinaryTree();// Рекурсивно удалить все узлы дерева;
    void deleteSubtree(Node* node);// Рекурсивная функция удаления поддерева
    void readFromFile(string filename);// Функция чтения парсинговой скобочной записи из файла и создания дерева
    void depthFirstTraversal(Node* node);// Рекурсивная функция обхода в глубину (префиксная обход)
    void traverseDepthFirst();// Функция обхода дерева в глубину (префиксный обход)
    void createAVLtree(AVLtree& tree); //создать авл дерево
    void createAVLtreeHelp(Node* node, AVLtree& tree); // вспомогательная функция для создания авл дерева
};


    
