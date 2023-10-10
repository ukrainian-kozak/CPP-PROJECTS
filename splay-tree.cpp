#include <iostream>

struct Node {
    int data;
    Node* parent;
    Node* left;
    Node* right;
};

class splay_tree {
    public:
        void insert(int data) {
            Node* node = cretae_node(data);
            void insert_helper(node);
        }

        Node* erase(int data) {
            if (!root)
                return nullptr;
            splay(root, data);
            if (data != root->data)
                return nullptr;
            if (root->left == nullptr) {
                root = root->right;
            } else {
                Node* temp = root;
                splay(root->left, data);
                root->right = temp->right;
                delete temp;
            }

            return root;
        }

    private:
        Node* root;

        Node* create_node(Node* parent, int data) {
            Node* temp = new Node();
            temp->data = data;
            temp->parent = parent;
            temp->left = nullptr;
            temp->right = nullptr;
        }

        void right_rotation(Node* x) {
            Node* y = x->left;
            x->left = y->right;
            if (y->right != nullptr) {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) {
                root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
            y->right = x;
            x->parent = y;
        }

        void left_rotation(Node* x) {
            Node* y = x->right;
            x->right = y->left;
            if (y->left != nullptr) {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) {
                root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        }

        void splay(Node* node) {
            while (n->parent != nullptr) {
                if (n->parent == root) {
                    if (n == n->parent->left) {
                        right_rotation(n->parent);
                    } else {
                        left_rotation(n->parent);
                    }
                } else {
                    Node* p = n->parent;
                    Node* g = p->parent;

                    if (n == n->parent->left && p = p->parent->left) {
                        right_rotation(g);
                        right_rotation(p);
                    } else if (n == n->parent->right && p = p->parent->right) {
                        left_rotation(g);
                        left_rotation(p);
                    } else if (n == n->parent->left && p = p->parent->right) {
                        right_rotation(p);
                        left_rotation(g);
                    } else {
                        left_rotation(p);
                        right_rotation(g);
                    }
                }
            }
            root = node;
        }



        void insert_helper(Node* node) {
            Node* temp = root;
            Node* y = nullptr;
            while (temp != nullptr) {
                y = temp;
                if (n->data < temp->data) {
                    temp = temp->left;
                } else {
                    temp = temp->right;
                }
            }

            n->parent = y;
            if (y == nullptr) {
                root = n;
            } else if (n->data < y->data) {
                y->left = n;
            } else {
                y->right = n;
            }

            splay(n);
        }
};
