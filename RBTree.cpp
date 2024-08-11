#include "RBTree.h"
#include <bits/stdc++.h>

int RBTree::getColor(Node *&node)
{
    if (node == NULL)
        return BLACK;
    return node->color;
};

void RBTree::setColor(Node *&node, RBColor color)
{
    if (node != NULL)
        node->color = color;
};

void RBTree::inorder(Node *&root)
{
    if (root != NULL)
    {
        inorder(root->left);
        std::cout << root->data << " ";
        inorder(root->right);
    }
};

void RBTree::leftRotate(Node *&x)
{
    Node *y = x->right;
    x->right = y->left;

    if (x->right != NULL)
        x->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
};

void RBTree::rightRotate(Node *&y)
{
    Node *x = y->left;
    y->left = x->right;

    if (y->left != NULL)
    {
        y->left->parent = y;
    }

    x->parent = y->parent;

    if (x->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
};


Node *RBTree::findMin(Node *&node)
{
    Node *tmp = node;
    while (tmp->left != nullptr)
    {
        tmp = tmp->left;
    }
    return tmp;
}

Node *RBTree::prePareInsert(Node *&root, Node *&ptr)
{
    if (root == nullptr)
    {
        return ptr;
    }
    if (root->data > ptr->data)
    {
        root->left = prePareInsert(root->left, ptr);
        root->left->parent = root;
    }

    if (root->data < ptr->data)
    {
        root->right = prePareInsert(root->right, ptr);
        root->right->parent = root;
    }
    return root;
}

void RBTree::insertFixup(Node *&cur)
{
    Node *parent = nullptr;
    Node *grandParent = nullptr;
    Node *uncle = nullptr;
    while (cur != root && getColor(cur) == RED && getColor(cur->parent) == RED)
    {
        parent = cur->parent;
        bool branch = cur == parent->left ? true : false;
        grandParent = parent->parent;
        bool parentBranch = parent == grandParent->left ? true : false;

        if (parentBranch)
            uncle = grandParent->right;
        else
            uncle = grandParent->left;

        if (getColor(uncle) == RED) // black parent has two red no-leaf node
        {
            setColor(uncle, BLACK);
            setColor(parent, BLACK);
            setColor(grandParent, RED);
            cur = grandParent;
        }
        else // uncle nullptr
        {
            if (branch != parentBranch)
            { // cur parent :  different sub direction from their own parent
                if (branch)
                    rightRotate(parent);
                else
                    leftRotate(parent);
                cur = parent;
                parent = cur->parent;
            }
            // here, cur parent all left or all right
            if (parentBranch)
                rightRotate(grandParent);
            else
                leftRotate(grandParent);
            swap(grandParent->color, parent->color);
            cur = parent;
        }
    }
    setColor(root, BLACK);
}

Node *RBTree::prePareDelete(Node *&root, int data)
{
    if (root == nullptr)
        return root; // 没找到节点 返回空节点.

    if (root->data > data) // 向左找
        return prePareDelete(root->left, data);

    if (root->data < data) // 向右找
        return prePareDelete(root->right, data);

	if(root->left == nullptr || root->right == nullptr)
	{
		return root;
	}

    Node* tmp = findMin(root->right); // 找到了.将右子树的最小节点找到,替换并删除该最小节点
    root->data = tmp->data;
    return prePareDelete(root->right,tmp->data);
}

void RBTree::deleteFixup(Node *& cur){
    if(cur == nullptr) return;
    if(cur == root) { 
        cur = nullptr;
        return;
    }

    if(getColor(cur) == RED || getColor(cur->left) == RED || getColor(cur->right) == RED){
        Node* child = cur->left != nullptr ? cur->left : cur->right;
        if(child != nullptr){ // one red/leaf/subnode 
            child->parent = cur->parent;
            if(child->parent->left == cur) child->parent->left = child;
            else child->parent->right = child;
            setColor(child,BLACK);
        }else{// red cur has no child
            if(cur->parent->left == cur)
            {
                cur->parent->left = nullptr;
                cur->parent = nullptr;
            }
            else
            {
                cur->parent->right = nullptr;
                cur->parent = nullptr;
            }
        }
        delete(cur); 
    }else{ // cur = black leaf node. 
        Node* brother = nullptr;
        Node* parent = nullptr;
        Node* ptr = cur;
        setColor(ptr,DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK)
        {   parent = ptr->parent;
            bool branchPtr = ptr == parent->left ? true: false;
            if(branchPtr) brother =parent->right;
            else brother = parent->left;

            if(getColor(brother) == RED){ // red brother has two black leaf node.
                setColor(brother,BLACK);
                setColor(parent,RED);
                ptr = parent;
                if(branchPtr) leftRotate(parent); 
                else rightRotate(parent);
            }else{ 
                if(getColor(brother->left) == RED || getColor(brother->right) == RED){// brother has one red leaf subnode
                    bool brotherBranch = brother->left != nullptr ? true : false;
                    Node* nephew = brotherBranch? brother->left : brother->right;

                    if(branchPtr == brotherBranch){ // brother and brother's subnode :  different sub direction from their own parent
                        setColor(nephew,BLACK);
                        setColor(brother,RED);
                        if(brotherBranch) {
                            leftRotate(brother);
                            brother = parent->left;
                        }else {
                            rightRotate(brother);
                            brother = parent->right;
                        }
                    } // here, brother and nephew all left or all right
                    setColor(brother,parent->color);
                    setColor(parent,BLACK);
                    setColor(nephew,BLACK);
                    if(branchPtr) leftRotate(parent);
                    else rightRotate(parent);
                    break;
                }else if (getColor(brother->left) == BLACK && getColor(brother->right) == BLACK){ // black brother has no child or has two black
                    setColor(brother,RED);
                    if(getColor(parent) == RED) setColor(parent,BLACK);
                    else setColor(parent,DOUBLE_BLACK);
                    ptr = parent;
                }
            }
        }
        if(cur->parent->left == cur) cur->parent->left = nullptr;
        else cur->parent->right = nullptr;
        delete(cur);
        setColor(root,BLACK);
    }
}

void RBTree::insert(int key){
    Node * node = new Node(key);
    root = prePareInsert(root,node);
    insertFixup(node);
}

void RBTree::deleteValue(int key){
    Node * tmp = prePareDelete(root,key);
    deleteFixup(tmp);
}

void RBTree::inorder(){
    inorder(root);
    cout<<"\n"<<endl;
}