#include <iostream>
#include <stdlib.h>
using namespace std;

struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
};
struct tree *root = NULL;

tree *insert(struct tree *node, int val)
{
    struct tree *temp = (struct tree *)malloc(sizeof(struct tree));
    temp->data = val;
    temp->left = temp->right = NULL;
    if (node == NULL)
    {
        node = temp;
        return temp;
    }
    else if (val < node->data)
    {
        node->left = insert(node->left, val);
    }
    else
    {
        node->right = insert(node->right, val);
    }
}
void descendetors(struct tree *node)
{
    struct tree *root = node;
    if (node == NULL)
    {
        return;
    }
    cout << root->data << " ";
    descendetors(root->left);
    descendetors(root->right);
}
void ancestors(struct tree *root, int key)
{
    if (root == NULL)
    {
        return;
    }
    if (root->data == key)
    {
        return;
    }
    if (key < root->data)
    {
        cout << root->data << " ";
        ancestors(root->left, key);
    }
    else if (key > root->data)
    {
        cout << root->data << " ";
        ancestors(root->right, key);
    }
}

void inorderPredecessor(tree *node, int val, bool &flag)
{
    if (node == NULL)
    {
        return;
    }
    inorderPredecessor(node->right, val, flag);
    if (flag)
    {
        cout << "Inorder Predecessor" <<node->data;
        flag = false;
        return;
    }
    if (node->data == val)
    {
        flag = true;
    }
    inorderPredecessor(node->left, val, flag);
}

void inorderSuccessor(struct tree *node, int key, bool &found)
{
    if (node == NULL)
    {
        return;
    }
    inorderSuccessor(node->left, key, found);
    if (found)
    {
        cout << "Inorder Successor: " << node->data << endl;
        found = false;
        return;
    }
    if (node->data == key)
    {
        found = true;
    }
    inorderSuccessor(node->right, key, found);
}

int main()
{
    root = insert(root, 3);
    insert(root, 4);
    insert(root, 5);
    insert(root, 2);
    root = insert(root, 1);
    insert(root, 38);
    insert(root, 30);
    // descendetors(root);
    // ancestors(root, 5);
    bool flag = false;
    inorderPredecessor(root, 5, flag);   
    inorderSuccessor(root,5,flag);
}