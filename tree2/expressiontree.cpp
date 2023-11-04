#include <iostream>
#include <stdlib.h>
using namespace std;

struct tree
{
    char data;
    struct tree *left;
    struct tree *right;
};

struct tree *createNode(char c)
{
    struct tree *temp = (struct tree *)malloc(sizeof(struct tree));
    temp->data = c;
    temp->left = temp->right = NULL;
    return temp;
}
bool ifOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '&' || c == '|' || c == '>' || c == '<' || c == '!')
    {
        return true;
    }
    return false;
}

tree *expression(string ptfix)
{
    tree *t, *t1, *t2;
    tree *stack[1000];
    int top = -1;
    for (int i = 0; i < ptfix.length(); i++)
    {
        if (!ifOperator(ptfix[i]))
        {
            t = createNode(ptfix[i]);
            stack[++top] = t;
        }
        else
        {
            t=createNode(ptfix[i]);
            t1=stack[top--];
            t2=stack[top--];
            t->left=t2;
            t->right=t1;
            stack[++top]=t;
        }
    }
    return stack[top--];
}

void preorder(tree *node)
{
    if (node == nullptr)
        return;

    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

int main()
{
    string ptfix ;
    cin>>ptfix;
    tree *root = expression(ptfix);
    cout << "Preorder traversal of expression tree: " << endl;
    preorder(root);
    return 0;
}
