

#include <iostream>
#include <cstdlib>
using namespace std;

struct avl
{
    int data;
    struct avl *left, *right;
    int height;
};

struct avl *root = NULL;

int getHeight(avl *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

int balancefactor(avl *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return (getHeight(node->left) - getHeight(node->right));
}

struct avl *shiftleft(struct avl *node)
{
    avl *Nnode = node->right;
    avl *LC = Nnode->left;
    node->right = LC;
    Nnode->left = node;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    Nnode->height = max(getHeight(Nnode->left), getHeight(Nnode->right)) + 1;

    return Nnode;
}

struct avl *shiftright(struct avl *node)
{
    avl *Nnode = node->left;
    avl *RC = Nnode->right;
    node->left = RC;
    Nnode->right = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    Nnode->height = max(getHeight(Nnode->left), getHeight(Nnode->right)) + 1;

    return Nnode;
}

struct avl *insert(struct avl *node, int value)
{
    if (node == NULL)
    {
        struct avl *temp = (struct avl *)malloc(sizeof(struct avl));
        temp->data = value;
        temp->left = temp->right = NULL;
        temp->height = 1;
        return temp;
    }

    if (value < node->data)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->data)
    {
        node->right = insert(node->right, value);
    }
    else
    {
        return node; // If the value is already present in the tree
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = balancefactor(node);

    if (bf > 1 && value < node->left->data)
    {
        return shiftright(node);
    }
    if (bf < -1 && value > node->right->data)
    {
        return shiftleft(node);
    }
    if (bf > 1 && value > node->left->data)
    {
        node->left = shiftleft(node->left);
        return shiftright(node);
    }
    if (bf < -1 && value < node->right->data)
    {
        node->right = shiftright(node->right);
        return shiftleft(node);
    }
    return node;
}

avl *min_node(struct avl *node)
{
    struct avl *curr = node;
    while (curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}
avl *deleteNode(struct avl *node, int value)
{
    if (node == NULL)
    {
        return node;
    }
    if (value < node->data)
    {
        node->left = deleteNode(node->left, value);
    }
    if (value > node->data)
    {
        node->right = deleteNode(node->right, value);
    }
    else
    {
        struct avl *curr = node;
        if (node->left == NULL)
        {
            struct avl *temp = node->right;
            free(node);
            return temp;
        }
        if (node->right == NULL)
        {
            struct avl *temp = node->left;
            free(node);
            return temp;
        }
        else
        {
            struct avl *temp = min_node(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, value);
        }
    }
    // Update the height of the current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Get the balance factor of this node
    int bf = balancefactor(node);

    //shift right (left left case)
    if (bf > 1 && value < node->left->data)
    {
        return shiftright(node);
    }
    // shift left (right right case)
    if (bf < -1 && value > node->right->data)
    {
        return shiftleft(node);
    }
    // double shift (left right case)
    if (bf > 1 && value > node->left->data)
    {
        node->left = shiftleft(node->left);
        return shiftright(node);
    }
    // double shift (right left case)
    if (bf < -1 && value < node->right->data)
    {
        node->right = shiftright(node->right);
        return shiftleft(node);
    }

    // Return the updated node
    return node;
}
void preOrder(avl *node)
{
    if (node == NULL)
    {
        return;
    }
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

int main()
{
    struct avl *root = NULL;

    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 3);
    root=deleteNode(root,4);
    preOrder(root);

    return 0;
}