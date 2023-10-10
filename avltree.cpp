#include <iostream>
#include <cstdio>
#include <sstream>
#include <algorithm>

#define pow2(n) (1 << (n))

/*
 * Node declaration
 */

struct AvlNode {
    int data;
    struct AvlNode *left;
    struct AvlNode *right;

    AvlNode(int val = 0,
            struct AvlNode *l = nullptr,
            struct AvlNode *r = nullptr) : data(val), left(l), right(r) {}
} *root;

/*
 * Class declaration
 */

class AvlTree {

    public:
        int height(AvlNode*);
        int diff(AvlNode*);
        AvlNode *rRot(AvlNode*);
        AvlNode *lRot(AvlNode*);
        AvlNode *balance(AvlNode*);
        AvlNode *insert(AvlNode*, int);
        void display(AvlNode*, int);
        void inorder(AvlNode*);
        void preorder(AvlNode*);
        void postorder(AvlNode*);

        AvlTree() {
            root = nullptr;
        }
};

/*
 * Height of AVL Tree
 */

int AvlTree::height(AvlNode* node)
{
    if (!node)
        return 0;
    int lH = height(node->left);
    int rH = height(node->right);

    return std::max(lH, rH) + 1;
}

/*
 * Height Difference
 */

int AvlTree::diff(AvlNode* temp)
{
    return (temp->left ? height(temp->left) : 0) - (temp->right ? height(temp->right) : 0);
}

/*
 * Right - Right Rotation
 */

AvlNode *AvlTree::rRot(AvlNode* parent)
{
    AvlNode* temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->left = parent;
    return temp;
}

/*
 * Left - Left Rotation
 */

AvlNode *AvlTree::lRot(AvlNode* parent)
{
    AvlNode *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

/*
 * Balancing AVL Tree
 */

AvlNode *AvlTree::balance(AvlNode* node)
{
    int b_factor = diff(node);

    if (b_factor == 2) {
        if (diff(node->left) < 0)
            node->left = lRot(node->left);
        node = rRot(node);
    } else if (b_factor == -2) {
        if (diff(node->right) > 0)
            node->right = rRot(node->right);
       
        node = lRot(node);
    }

    return node;
}

/*
 * Insert Element into AVL Tree
 */

AvlNode *AvlTree::insert(AvlNode *root, int val)
{
    if (!root) {
        root = new AvlNode(val);
    } else if (root->data > val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }

    return balance(root);
}

/*
 * Display AVL Tree
 */

void AvlTree::display(AvlNode *ptr, int level)
{
    if (!ptr)
        return;

    display(ptr->right, level + 1);
    std::cout << '\n';
    if (ptr == root)
        std::cout << "Root -> ";
    for (int i = 0; i < level && ptr != root; ++i)
        std::cout << "\t";
    std::cout << ptr->data;
    display(ptr->left, level + 1);
}

/*
 * Inorder, preorder, postorder traversals
 */

void AvlTree::inorder(AvlNode* root)
{
    if (!root)
        return;
    inorder(root->left);
    std::cout << root->data << ' ';
    inorder(root->right);
}

void AvlTree::preorder(AvlNode* root)
{
    if (!root)
        return;
    std::cout << root->data << ' ';
    preorder(root->left);
    preorder(root->right);
}

void AvlTree::postorder(AvlNode* root)
{
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    std::cout << root->data << ' ';
}



/*
 * Test ((((
 */


int main()
{
    int choice, item;
    AvlTree avl;
    for ( ;; ) {
        std::cout << "\n---------------------" << std::endl;
        std::cout << "AVL Tree Implementation" << std::endl;
        std::cout << "\n---------------------" << std::endl;
        std::cout << "1.Insert Element into the tree" << std::endl;
        std::cout << "2.Display Balanced AVL Tree" << std::endl;
        std::cout << "3.InOrder traversal" << std::endl;
        std::cout << "4.PreOrder traversal" << std::endl;
        std::cout << "5.PostOrder traversal" << std::endl;
        std::cout << "6.Exit" << std::endl;
        std::cout << "Enter your Choice: ";
        std::cin >> choice;
        switch (choice)
        {
            case 1:
                std::cout << "Enter value to be inserted: ";
                std::cin >> item;
                root = avl.insert(root, item);
//                root = avl.balance(root);
                break;
            case 2:
                if (root == NULL)
                {
                    std::cout << "Tree is Empty" << std::endl;
                    continue;
                }
                std::cout << "Balanced AVL Tree:" << std::endl;
                avl.display(root, 1);
                break;
            case 3:
                std::cout << "Inorder Traversal:" << std::endl;
                avl.inorder(root);
                std::cout << std::endl;
                break;
            case 4:
                std::cout << "Preorder Traversal:" << std::endl;
                avl.preorder(root);
                std::cout << std::endl;
                break;
            case 5:
                std::cout << "Postorder Traversal:" << std::endl;
                avl.postorder(root);
                std::cout << std::endl;
                break;
            case 6:
                exit(1);
                break;
            default:
                std::cout << "Wrong Choice" << std::endl;
                break;
        }
    }
    return 0;
}
