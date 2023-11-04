void inorderPredecessor(struct tree *node, int key, bool &found)
// {
//     if (node == NULL)
//     {
//         return;
//     }
//     inorderPredecessor(node->right, key, found);
//     if (found)
//     {
//         cout << "Inorder Predecessor: " << node->data << endl;
//         found = false;
//         return;
//     }
//     if (node->data == key)
//     {
//         found = true;
//     }
//     inorderPredecessor(node->left, key, found);
// }