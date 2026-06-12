#include <iostream>
#include <fstream>
#include <string>
#include "color.hpp"
using namespace std;

enum Color { RED, BLACK };

template <typename Key, typename Value>
class Node {
public:
    Key key;
    Value value;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(Key k, Value v, Color c = RED){
    this->key=k;
    this->value=v ;
    this->color=c;
    this->parent=NULL;
    this->left=NULL;
    this->right=NULL;

}
};

template <typename Key, typename Value>
class RedBlackTree{
public:
    Node<Key, Value>* root;

        RedBlackTree() {
        this->root=NULL;
    }

    void printInOrder(Node<Key, Value>* node) const {
        if (node != NULL) {
            printInOrder(node->left);
            cout << node->key << " => " << node->value <<endl;
            printInOrder(node->right);
        }
    }

     void printInOrderTree(Node<Key, Value>* node,ostream& output) const {
        if (node != NULL) {
            printInOrderTree(node->left, output);
            output << node->key;
            if (!node->value.empty()) {
                output << " => " << node->value;
            }
            output <<endl;
            printInOrderTree(node->right, output);
        }
    }

    void printTree(Node<Key, Value>* node,ostream& output)const {
    if (node != NULL) {
        output << node->key << "_" << node->value;
        if (node->left != NULL || node->right != NULL) {
            output << "(";
            printTree(node->left, output);
            output << ",";
            printTree(node->right, output);
            output << ")";
        }
    }
}

    int countSize(Node<Key, Value>* node) const {
        if (node == NULL) {
            return 0;
        }
        return 1 + countSize(node->left) + countSize(node->right);
    }

    void leftRotation(Node<Key, Value>* x) {
if (x == nullptr || x->right == nullptr) {
        return; 
    }
Node<Key, Value>* y = x->right;
        x->right = y->left;

        if (y->left != NULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent ==NULL) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void rightRotation(Node<Key, Value>* y) {
          if (y == nullptr || y->left == nullptr) {
        return;
    }
        Node<Key, Value>* x = y->left;
        y->left = x->right;

        if (x->right != NULL) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == NULL) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        x->right = y;
        y->parent = x;
    }

   


   void insertFlip(Node<Key, Value>* &z) {
    while (z != nullptr && z->parent != nullptr && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            LeftCase(z);
        } else {
            RightCase(z);
        }
    }

    root->color = BLACK;
}

void LeftCase(Node<Key, Value>* &z) {
    Node<Key, Value>* y = z->parent->parent->right;
    if (y != NULL && y->color == RED) {
        Node<Key, Value>* y = z->parent->parent->right;
                if (y != NULL && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
    } 
    }else {
        if (z == z->parent->right) {
            z = z->parent;
            leftRotation(z);
        }

        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rightRotation(z->parent->parent);
    }
}

void RightCase(Node<Key, Value>* &z) {
    Node<Key, Value>* y = z->parent->parent->left;
                if (y != NULL && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
    } else {
        if (z == z->parent->left) {
            z = z->parent;
            rightRotation(z);
        }

        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        leftRotation(z->parent->parent);
    }
}

    void transplant(Node<Key, Value>* u, Node<Key, Value>* v) {
    if (!u->parent) {
        root = v;
        if (v)
            v->parent = NULL;
        return;
    }

    if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v)
        v->parent = u->parent;
}


    Node<Key, Value>* treeMin(Node<Key, Value>* x) {
    if (x == NULL) {
        return NULL;  
    }
    while (x->left != NULL) {
        x = x->left;
    }

    return x;
}


void eraseFlip(Node<Key, Value>* x) {
    while (x != NULL && x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            LeftErase(x);
        } else {
            RightErase(x);
        }
    }

    if (x != NULL) {
        x->color = BLACK;
    }
}

void LeftErase(Node<Key, Value>* &x) {
  Node<Key, Value>* newN = x->parent->right;
            if (newN != NULL) {
                if (newN->color == RED) {
                    newN->color = BLACK;
                    x->parent->color = RED;
                    leftRotation(x->parent);
                    newN = x->parent->right;
                }

                if ((newN->left == NULL || newN->left->color == BLACK) &&(newN->right == NULL || newN->right->color == BLACK)) {
                   newN->color = RED;
                    x = x->parent;
                } else {
                    if (newN->right == NULL ||newN->right->color == BLACK) {
                        if (newN->left != NULL) {
                            newN->left->color = BLACK;
                        }
                        newN->color = RED;
                        rightRotation(newN);
                       newN = x->parent->right;
                    }

                   newN->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (newN->right != NULL) {
                       newN->right->color = BLACK;
                    }
                    leftRotation(x->parent);
                    x = root;
                }
            }
}

void RightErase(Node<Key, Value>* &x) {
    Node<Key, Value>* newN = x->parent->left;
   if (newN != NULL) {
                if (newN->color == RED) {
                    newN->color = BLACK;
                    x->parent->color = RED;
                    rightRotation(x->parent);
                   newN = x->parent->left;
                }

                if ((newN->right == NULL ||newN->right->color == BLACK) &&
                    (newN->left == NULL || newN->left->color == BLACK)) {
                    newN->color = RED;
                    x = x->parent;
                } else {
                    if (newN->left == NULL || newN->left->color == BLACK) {
                        if (newN->right != NULL) {
                            newN->right->color = BLACK;
                        }
                        newN->color = RED;
                        leftRotation(newN);
                     newN = x->parent->left;
                    }

                    newN->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (newN->left !=NULL) {
                        newN->left->color = BLACK;
                    }
                    rightRotation(x->parent);
                    x = root;
                }
            }
        }


void handleBlackSibling(Node<Key, Value>* &x, Node<Key, Value>* &newN) {
    if (newN != nullptr) {
        if (newN->left == NULL ||newN->left->color == BLACK) {
            if (newN->right != NULL) {
                newN->right->color = BLACK;
            }
            newN->color = RED;
            //rotate(w, RIGHT);
            newN = x->parent->right;
        }

        newN->color = x->parent->color;
        x->parent->color = BLACK;
        if (newN->right != NULL) {
            newN->right->color = BLACK;
        }
        //rotate(x->parent, LEFT);
        x = root;
    }
}





      Node<Key, Value>* getRoot() const {
        return root;
    }

    void insert(Key key, Value value) {
        Node<Key, Value>* newN = new Node<Key, Value>(key, value);
        Node<Key, Value>* y = NULL;
        Node<Key, Value>* x = root;

        while (x != NULL) {
            y = x;
            if (newN->key < x->key) {
                x = x->left;
            } else if (newN->key > x->key) {
                x = x->right;
            } else {
                x->value = newN->value;
                delete newN;
                return;
            }
        }

        newN->parent = y;
        if (y == NULL) {
            root = newN;
        } else if (newN->key < y->key) {
            y->left =newN;
        } else {
            y->right = newN;
        }

        insertFlip(newN);
    }



Node<Key, Value>* traverseTree(Node<Key, Value>* root, Node<Key, Value>* newN) {
    Node<Key, Value>* parent = NULL;
    Node<Key, Value>* curr = root;

    while (curr != nullptr) {
        parent = curr;
        if (newN->key < curr->key) {
            curr = curr->left;
        } else if (newN->key > curr->key) {
            curr = curr->right;
        } else {
            curr->value = newN->value;
            delete newN;
            return NULL;
        }
    }


    newN->parent = parent;
    if (parent == NULL) {
        root = newN;
    } else if (newN->key < parent->key) {
        parent->left = newN;
    } else {
        parent->right = newN;
    }

    return newN;
}

void eraseN(Node<Key, Value>* node , Node<Key, Value>* y, Node<Key, Value>* x, Color color) {
    delete node ;

    if (color == BLACK) {
        eraseFlip(x);
    }
}
void handleChild(Node<Key, Value>* node, Node<Key, Value>* y, Node<Key, Value>* x) {
    y = treeMin(node->right);
    Color color = y->color;
    x = y->right;

    if (y->parent == node) {
        if (x != NULL) {
            x->parent = y;
        }
    } else {
        transplant(y, y->right);
        y->right = node->right;
        if (y->right != NULL) {
            y->right->parent = y;
        }
    }

    transplant(node, y);
    y->left = node->left;
    y->left->parent = y;
    y->color = node->color;

    eraseN(node, y, x, color);
}

void erase(Key key, ostream& output) {
    Node<Key, Value>* node = root;
    while (node != NULL) {
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            Node<Key, Value>* y = node;
            Node<Key, Value>* x = NULL;

            if (node->left == NULL) {
                x = node->right;
                transplant(node, node->right);
               eraseN(node, y, x, y->color);
            } else if (node->right == NULL) {
                x = node->left;
                transplant(node, node->left);
                eraseN(node, y, x, y->color);
            } else {
                handleChild(node, y, x);
            }
            return;
        }
    }

    output << key << " not found" << endl;
}





  void clear(ostream& output) {
    if (root == NULL) {
        output << "unsuccessful" <<endl;
    } else {
        while (root != NULL) {
            erase(root->key,output);
        }
        output << "successful" <<endl;
    }
}


    void find(Key key,ostream& output) {
        Node<Key, Value>* current = root;
        while (current != NULL) {
            if (key < current->key) {
                current = current->left;
            } else if (key > current->key) {
                current = current->right;
            } else {
                output<<key << " found" <<endl;
                return;
            }
        }
        output <<key<< " not found" <<endl;
    }

    bool empty() const {
        return root == NULL;
    }

    int size() const {
        return countSize(root);
    }

      void inorderTraversal() const {
        printInOrder(root);
    }


    void printRedBlackTree(ostream& output)const{
       printTree(root, output);
    }
     void inorder(ostream& output) const {
        printInOrderTree(root, output);
    }

    void inorderHelp(Node<Key, Value>* node) const {
        if (node !=NULL) {
            inorderHelper(node->left);
            cout << node->key << " => " << node->value << endl;
            inorderHelper(node->right);
        }
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    RedBlackTree<int,string> RB;

    string operation;
    while (in >> operation) {
        if (operation == "I") {
            int key;
            string value;
            in >> key >> value;
            RB.insert(key, value);
           RB.printRedBlackTree( out);
            out <<endl;
        }
          else if (operation == "E") {
            int key;
            in >> key;
            RB.erase(key, out);
             RB.printRedBlackTree( out);
             out<<endl;

        } else if (operation == "Clr") {
            RB.clear(out);
        } else if (operation == "F") {
            int key;
            in >> key;
            RB.find(key,out);
        } else if (operation == "Em") {
                if(RB.empty()){
                    out<<"yes"<<endl;
                }else{
                    out<<"no"<<endl;
                }
        } else if (operation == "S") {
            out << RB.size() <<endl;
        } else if (operation == "Itr") {
            RB.inorder(out);
        }

    }

    return 0;
}