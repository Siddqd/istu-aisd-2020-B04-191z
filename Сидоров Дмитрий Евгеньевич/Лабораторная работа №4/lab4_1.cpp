// lab4_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
using namespace std;

struct node {
    int key;
    int8_t height;
    node* left;
    node* right;

    node(int new_key) { key = new_key; left = right = 0; height = 1; }
};

int8_t max_ab(int8_t a, int8_t b) {
    return (a > b) ? a : b;
}

int8_t node_h(node* nd)
{
    return (nd != NULL) ? nd->height : 0;
}

int8_t b_f(node* nd)
{
    return node_h(nd->left) - node_h(nd->right);
}

node* node_r_rot(node* nd) {
    node* _left = nd->left;
    nd->left = _left->right;
    _left->right = nd;
    nd->height = max_ab(node_h(nd->left), node_h(nd->right))+1;
    _left->height = max_ab(node_h(_left->left), nd->height)+1;
    return _left;
}

node* node_l_rot(node* nd) {
    node* _right = nd->right;
    nd->right = _right->left;
    _right->left = nd;
    nd->height= max_ab(node_h(nd->left), node_h(nd->right)) + 1;
    _right->height = max_ab(node_h(_right->right), nd->height) + 1;
    return _right;
}

node* node_lr_rot(node* nd) {
    nd->left = node_l_rot(nd->left);
    return node_r_rot(nd);
}

node* node_rl_rot(node* nd) {
    nd->right = node_r_rot(nd->right);
    return node_l_rot(nd);
}


node* add(node* nd, int new_key)
{
    if (nd == NULL) { nd = new node(new_key); return nd; }
    if (new_key < nd->key) {
        nd->left = add(nd->left, new_key);
        if (b_f(nd) == 2) {
            if (new_key < nd->left->key) { nd = node_r_rot(nd); }
            else { nd = node_lr_rot(nd); }
        }
    }
    else if (new_key > nd->key) {
        nd->right = add(nd->right, new_key);
        if (b_f(nd) == -2) {
            if (new_key > nd->right->key) { nd = node_l_rot(nd); }
            else { nd = node_rl_rot(nd); }
        }
    }
    nd->height = max_ab(node_h(nd->left) , node_h(nd->right))+1;
    return nd;
}

void printTree(node * nd) {
    if (!nd) return;
    printTree(nd->left);
    cout << "   " << nd->key <<" ("<<int(b_f(nd))<<")    ";
    printTree(nd->right);
}


int main()
{
    node* head;
    int k;
    cin >> k;
    head = new node(k);
    head = add(head, 15);
    //printTree(head);
    head = add(head, 21);
    //printTree(head);
    head = add(head, 34);
    //printTree(head);
    head = add(head, 11);
    //printTree(head);
    head = add(head, 16);
    //printTree(head);
    head = add(head, 18);
    //printTree(head);
    head = add(head, 20);
    printTree(head);
    return 0;
}
