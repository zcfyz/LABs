#include "avltree.h"
#include <queue>

using namespace std;

unsigned char AVLtree::height(NodeA* node)
{
    return node ? node->height : 0;
}

int AVLtree::balanceFactor(NodeA* node)
{
    if (node == NULL)
        return 0;
    else
        return height(node->right) - height(node->left);
}

void AVLtree::fixHeight(NodeA* node)
{
    unsigned char hleft = height(node->left);
    unsigned char hright = height(node->right);
    node->height = (hleft > hright ? hleft : hright) + 1;
}

NodeA* AVLtree::rotateRight(NodeA* node)
{
    NodeA* son = node->left;
    node->left = son->right;
    son->right = node;
    fixHeight(node);
    fixHeight(son);
    return son;
}

NodeA* AVLtree::rotateLeft(NodeA* node)
{
    NodeA* son = node->right;
    node->right = son->left;
    son->left = node;
    fixHeight(node);
    fixHeight(son);
    return son;
}

NodeA* AVLtree::balance(NodeA* node)
{
    fixHeight(node);

    if (balanceFactor(node) == -2)
    {
        if (balanceFactor(node->left) > 0)
        {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if (balanceFactor(node) == 2)
    {
        if (balanceFactor(node->right) < 0)
        {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

NodeA* AVLtree::insert(NodeA* node, int data)
{
    if (node == NULL)
    {
        node = new NodeA;
        node->key = data;
        node->left = NULL;
        node->right = NULL;
        node->height = 0;
    }

    else if (data < node->key)
    {
        node->left = insert(node->left, data);
    }

    else
    {
        node->right = insert(node->right, data);
    }

    fixHeight(node);
    return balance(node);
}

NodeA* AVLtree::findMin(NodeA* node)
{
    if (node == NULL)
        return NULL;
    else
        return node->left ? findMin(node->left) : node;
}

NodeA* AVLtree::remove(NodeA* node, int data)
{
    NodeA* tmp;
    if (node == NULL)
    {
        cout << "Node with value " << data << " not found" << endl;
        return NULL;
    }
    else if (data < node->key)
        node->left = remove(node->left, data);
    else if (data > node->key)
        node->right = remove(node->right, data);
    else if (node->left && node->right)
    {
        tmp = findMin(node->right);
        node->key = tmp->key;
        node->right = remove(node->right, node->key);
    }
    else
    {
        tmp = node;
        if (node->left == NULL)
            node = node->right;
        else if (node->right == NULL)
            node = node->left;

        delete tmp;
    }

    if (node == NULL)
        return node;

    return balance(node);
}

NodeA* AVLtree::find(NodeA* node, int data)
{
    if (node == NULL || node->key == data)
        return node;

    else if (data < node->key)
        return find(node->left, data);

    else
        return find(node->right, data);
}

void AVLtree::preOrder(NodeA* root)
{
    if (root != NULL) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void AVLtree::inOrder(NodeA* root)
{
    if (root != NULL) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }

}

void AVLtree::postOrder(NodeA* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

void AVLtree::levelOrder(NodeA* root)
{
    if (root == NULL)
        return;

    queue<NodeA*> q;
    q.push(root);

    while (!q.empty()) {
        NodeA* current = q.front();
        cout << current->key << " ";
        if (current->left != NULL)
            q.push(current->left);
        if (current->right != NULL)
            q.push(current->right);
        q.pop();
    }

}
void AVLtree::printTreeHelp(NodeA* node)
{
    cout << node->key;
    if (node->left != NULL || node->right != NULL)
    {
        cout << "(";
        if (node->left != NULL)
        {
            printTreeHelp(node->left);
        }
        cout << ")(";
        if (node->right != NULL)
            printTreeHelp(node->right);
        cout << ")";
    }
}

AVLtree::AVLtree()
{
    root = NULL;
}

void AVLtree::insert(int data)
{
    root = insert(root, data);
}

void AVLtree::remove(int data)
{
    root = remove(root, data);
}

void AVLtree::search(int data)
{
    if (find(root, data) == NULL)
        cout << "Node did not found" << endl;

    else
        cout << "Node is found" << endl;
}

void AVLtree::printTree()
{
    if (root != NULL)
    {
        cout << "(";
        printTreeHelp(root);
        cout << ")";
    }

    else
        cout << "Tree is empty" << endl;
}

void AVLtree::PreOrder()
{
    preOrder(root);
}

void AVLtree::InOrder()
{
    inOrder(root);
}

void AVLtree::PostOrder()
{
    postOrder(root);
}

void AVLtree::Levelorder() {
    levelOrder(root);
}


