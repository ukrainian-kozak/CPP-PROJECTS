#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    int color;
};

typedef Node* NodePtr;

class RedBlackTree {
    private:
            NodePtr root;
            NodePtr TNULL;

            void initializeNULLNode(NodePtr node, NodePtr parent) {
                node->data = 0;
                node->left = nullptr;
                node->right = nullptr;
                node->parent = parent;
                node->color = 0;
            }

            void preorder(NodePtr node) {
                if (node == TNULL)
                    return;
                std::cout << node->data << ' ';
                preorder(node->left);
                preorder(node->right);
            }

            void inorder(NodePtr node) {
                if (node == TNULL)
                    return;
                inorder(node->left);
                std::cout << node->data << ' ';
                inorder(node->right);
            }

            void postorder(NodePtr node) {
                if (node == TNULL)
                    return;
                postorder(node->left);
                postorder(node->right);
                std::cout << node->data << ' ';
            }


            NodePtr search_helper(NodePtr node, int key) {
                if (node == TNULL || key == node->data) {
                    return node;
                }

                if (key < node->data)
                    return search_helper(node->left, key);
                else
                    return search_helper(node->right, key);
            }

            void insert_fix(NodePtr x) {
                NodePtr y;
                while (x->parent->color == 1) {
                    if (x->parent == x->parent->parent->right) {
                        y = x->parent->parent->left;
                        if (y->color == 1) {
                            y->color = 0;
                            x->parent->color = 0;
                            y->parent->color = 1;
                            x = x->parent->parent;
                        } else {
                            if (x == x->parent->left) {
                                x = x->parent;
                                right_rotation(x);
                            }
                            x->parent->color = 0;
                            x->parent->parent->color = 1;
                            left_rotation(x->parent->parent);
                        }
                    } else {
                        y = x->parent->parent->right;
                        if (y->color == 1) {
                            y->color = 0;
                            x->parent->color = 0;
                            y->parent->color = 1;
                            x = x->parent->parent;
                        } else {
                            if (x == x->parent->right) {
                                x = x->parent;
                                left_rotation(x);
                            }
                            x->parent->color = 0;
                            x->parent->parent->color = 1;
                            right_rotation(x->parent->parent);
                        }
                    }
                    if (x == root)
                        break;
                }
                root->color = 0;
            }

            void erase_fix(NodePtr x) {
                NodePtr s;
                while (x != root && x->color == 0) {
                    if (x == x->parent->left) {
                        s = x->parent->right;
                        if (s->color = 1) {
                            s->color = 0;
                            x->parent->color = 1;
                            left_rotation(x->parent);
                            s = x->parent->right;
                        }

                        if (s->left->color == 0 && s->right->color == 0) {
                            s->color = 1;
                            x = x->parent;
                        } else {
                            if (s->right->color == 0) {
                                s->left->color = 0;
                                s->color = 1;
                                right_rotation(s);
                                s = x->parent->right;
                            }

                            s->color = x->parent->color;
                            x->parent->color = 0;
                            s->right->color = 0;
                            left_rotation(x->parent);
                            x = root;
                        }
                    } else {
                        s = x->parent->left;
                        if (s->color == 1) {
                            s->color = 0;
                            x->parent->color = 1;
                            right_rotation(x->parent);
                            s = x->parent->left;
                        }

                        if (s->right->color == 0 && s->left->color == 0) {
                            s->color - 1;
                            x = x->parent;
                        } else {
                            if (s->left->color == 0) {
                                s->right->color = 0;
                                s->color = 1;
                                left_rotation(s);
                                s = x->parent->left;
                            }

                            s->color = x->parent->color;
                            x->parent->color = 0;
                            s->left->color = 0;
                            right_rotation(x->parent);
                            x = root;
                        }
                    }
                }
                x->color = 0;
            }

            void rb_transplant(NodePtr x, NodePtr y) {
                if (!x->parent)
                    root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                y->parent = x->parent;
            }

            void erase_helper(NodePtr node, int key) {
                NodePtr z = TNULL;
                NodePtr x, y;
                while (node != TNULL) {
                    if (node->data == key) {
                        z = node;
                    }

                    if (node->data <= key) {
                        node = node->right;
                    } else {
                        node = node->left;
                    }
                }

                if (z == TNULL) {
                    std::cout << "Key not found in the tree\n";
                    return;
                }

                y = z;
                int y_orig_color = y->color;
                if (z->left == TNULL) {
                    x = z->right;
                    rb_transplant(z, z->right);
                } else if (z->right == TNULL) {
                    x = z->left;
                    rb_transplant(z, z->left);
                } else {
                    y = minimum(z->right);
                    y_orig_color = y->color;
                    x = y->right;
                    if (y->parent == z) {
                        x->parent = y;
                    } else {
                        rb_transplant(y, y->right);
                        y->right = z->right;
                        y->right->parent = y;
                    }

                    rb_transplant(z, y);
                    y->left = z->left;
                    y->left->parent = y;
                    y->color = z->color;
                }

                delete z;
                if (y_orig_color == 0)
                    erase_fix(x);
            }

            void printHelper(NodePtr root, std::string indent, bool last) {
                if (root != TNULL) {
                    std::cout << indent;
                    if (last) {
                        std::cout << "R----";
                        indent += "   ";
                    } else {
                        std::cout << "L----";
                        indent += "|  ";
                    }

                    std::string sColor = root->color ? "RED" : "BLACK";
                    std::cout << root->data << "(" << sColor << ")" << std::endl;
                    printHelper(root->left, indent, false);
                    printHelper(root->right, indent, true);
                }
            }

    public:
            RedBlackTree() {
                TNULL = new Node;
                TNULL->color = 0;
                TNULL->left = nullptr;
                TNULL->right = nullptr;
                root = TNULL;
            }

            void preorder() {
                preorder(root);
            }

            void inorder() {
                inorder(root);
            }

            void postorder() {
                postorder(root);
            }

            NodePtr search(int key) {
                return search_helper(root, key);
            }

            NodePtr minimum(NodePtr node) {
                while (node->left != TNULL)
                    node = node->left;
                return node;
            }

            NodePtr maximum(NodePtr node) {
                while (node->right != TNULL)
                    node = node->right;
                return node;
            }

            NodePtr successor(NodePtr x) {
                if (x->right != TNULL)
                    return minimum(x->right);
                
                NodePtr y = x->parent;
                while (y != TNULL && x == y->right) {
                    x = y;
                    y = y->parent;
                }
                return y;
            }

            NodePtr predecessor(NodePtr x) {
                if (x->left != TNULL)
                    return maximum(x->left);

                NodePtr y = x->parent;
                while (y != TNULL && x == y->left) {
                    x = y;
                    y = y->parent;
                }
                return y;
            }

            void left_rotation(NodePtr x) {
                NodePtr y = x->right;
                x->right = y->left;
                if (y->left != TNULL) {
                    y->left->parent = x;
                }
                y->parent = x->parent;
                if (x->parent == nullptr)
                    root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else 
                    x->parent->right = y;
                y->left = x;
                x->parent = y;
            }

            void right_rotation(NodePtr y) {
                NodePtr x = y->left;
                y->left = x->right;
                if (x->right != TNULL) {
                    x->right->parent = y;
                }
                x->parent = y->parent;
                if (y->parent == nullptr)
                    root = x;
                else if (y = y->parent->left)
                    y->parent->left = x;
                else
                    y->parent->right = x;
                x->right = y;
                y->parent = x;
            }

            void insert(int key) {
                NodePtr node = new Node;
                node->parent = nullptr;
                node->data = key;
                node->left = TNULL;
                node->right = TNULL;
                node->color = 1;

                NodePtr y = nullptr;
                NodePtr x = root;

                while (x != TNULL) {
                    y = x;
                    if (node->data < x->data) {
                        x = x->left;
                    } else {
                        x = x->right;
                    }   
                }

                node->parent = y;
                if (!y) {
                    root = node;
                } else if (node->data < y->data) {
                    y->left = node;
                } else {
                    y->right = node;
                }

                if (!node->parent) {
                    node->color = 0;
                    return;
                }

                if (!node->parent->parent) {
                    return;
                }

                insert_fix(node);
            }

            NodePtr get_root() {
                return root;
            }

            void erase(int key) {
                erase_helper(root, key);
            }

            void print_tree() {
                if (root)
                    printHelper(root, "", true);
            }
};

int main()
{
  RedBlackTree bst;
  bst.insert(55);
  bst.insert(40);
  bst.insert(65);
  bst.insert(60);
  bst.insert(75);
  bst.insert(57);

  bst.print_tree();
  std::cout << std::endl
     << "After deleting" << std::endl;
  bst.erase(40);
  bst.print_tree();
}
