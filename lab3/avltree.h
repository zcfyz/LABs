#pragma once
#include <iostream>

struct NodeA {
    int key = 0;
    NodeA* left = NULL;
    NodeA* right = NULL;
    unsigned char height = 0; // высота дерева
};

class AVLtree
{
public:
    NodeA* root;

private:
    unsigned char height(NodeA* node); // высота
    int balanceFactor(NodeA* node); // фактор балансировки
    void fixHeight(NodeA* node); // исправить высоту
    NodeA* rotateRight(NodeA* node); // правый поворот
    NodeA* rotateLeft(NodeA* node); // левый поворот
    NodeA* balance(NodeA* node); // балансировка
    NodeA* insert(NodeA* node, int data); // вставка
    NodeA* findMin(NodeA* node); // поиск минимального
    NodeA* remove(NodeA* node, int data); // удаление
    NodeA* find(NodeA* node, int data); // поиск
    void preOrder(NodeA* root); // обход прямой
    void inOrder(NodeA* root); // обход в симметричном порядке
    void postOrder(NodeA* root); // обход пост-порядок
    void levelOrder(NodeA* root); //обход по уровнями в ширину

    void printTreeHelp(NodeA* node); // вспомогательная функция для вывода
public:
    AVLtree(); // констуктор
    void insert(int data); //вставка
    void remove(int data); // удаление
    void search(int data); // поиск
    void printTree(); // вывод
    void PreOrder(); // обход
    void InOrder();
    void PostOrder();
    void Levelorder();
};
