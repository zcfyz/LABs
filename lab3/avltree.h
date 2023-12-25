#pragma once
#include <iostream>

struct NodeA {
    int key = 0;
    NodeA* left = NULL;
    NodeA* right = NULL;
    unsigned char height = 0; // ������ ������
};

class AVLtree
{
public:
    NodeA* root;

private:
    unsigned char height(NodeA* node); // ������
    int balanceFactor(NodeA* node); // ������ ������������
    void fixHeight(NodeA* node); // ��������� ������
    NodeA* rotateRight(NodeA* node); // ������ �������
    NodeA* rotateLeft(NodeA* node); // ����� �������
    NodeA* balance(NodeA* node); // ������������
    NodeA* insert(NodeA* node, int data); // �������
    NodeA* findMin(NodeA* node); // ����� ������������
    NodeA* remove(NodeA* node, int data); // ��������
    NodeA* find(NodeA* node, int data); // �����
    void preOrder(NodeA* root); // ����� ������
    void inOrder(NodeA* root); // ����� � ������������ �������
    void postOrder(NodeA* root); // ����� ����-�������
    void levelOrder(NodeA* root); //����� �� �������� � ������

    void printTreeHelp(NodeA* node); // ��������������� ������� ��� ������
public:
    AVLtree(); // ����������
    void insert(int data); //�������
    void remove(int data); // ��������
    void search(int data); // �����
    void printTree(); // �����
    void PreOrder(); // �����
    void InOrder();
    void PostOrder();
    void Levelorder();
};
