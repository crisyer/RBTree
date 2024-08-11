#include <bits/stdc++.h>
using namespace std;

enum RBColor
{
    RED,
    BLACK,
    DOUBLE_BLACK
}; // Red-Black Tree color

struct Node
{
    int data;
    RBColor color;
    Node *left, *right, *parent;
    Node(int val) : data(val), color(RED), left(NULL), right(NULL), parent(NULL) {}
};

class RBTree
{
private:
    Node *root;

protected:
    void leftRotate(Node *&x);
    void rightRotate(Node *&y);

    Node* prePareInsert(Node *&root, Node *& cur);
    void insertFixup(Node *& cur);

    Node *findMin(Node *&root);

    
    Node* prePareDelete(Node *&root, int);
    void deleteFixup(Node *& cur);

    void inorder(Node *&root);
    int getColor(Node *&node);
    void setColor(Node *&node,RBColor color);

public:
    RBTree() : root(nullptr) {}
    void insert(int key);
    void deleteValue(int key);
    void inorder();
};