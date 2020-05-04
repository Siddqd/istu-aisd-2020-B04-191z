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
    if (nd==NULL) return 0;
    else return nd->height;
}

/*void upd_height (node nd*) {
 	int8_t h_left = height(nd->left);
	int8_t h_right = height(nd->right);
	nd->height = (h_left>h_right?h_left:h_right)+1;
}*/

int8_t b_f(node* nd)
{
    return node_h(nd->left) - node_h(nd->right);
}

node* node_r_r(node* nd) {
    node* _left = nd->left;
    nd->left = _left->right;
    _left->right = nd;
    nd->height = max_ab(node_h(nd->left), node_h(nd->right))+1;
    _left->height = max_ab(node_h(_left->left), nd->height)+1;
    return _left;
}

node* node_l_r(node* nd) {
    node* _right = nd->right;
    nd->right = _right->left;
    _right->left = nd;
    nd->height= max_ab(node_h(nd->left), node_h(nd->right)) + 1;
    _right->height = max_ab(node_h(_right->right), nd->height) + 1;
    return _right;
}

/*node* node_lr_rot(node* nd) {
    nd->left = node_l_r(nd->left);
    return node_r_r(nd);
}

node* node_rl_rot(node* nd) {
    nd->right = node_r_r(nd->right);
    return node_l_r(nd);
}*/

node* balance(node* nd) {
	nd->height = max_ab(node_h(nd->right),node_h(nd->left))+1;
	if( b_f(nd)==-2 ) {
		if( b_f(nd->right) > 0 )
			nd->right = node_r_r(nd->right);
		return node_l_r(nd);
	}
	if( b_f(nd)==2 ) {
		if( b_f(nd->left) < 0  )
			nd->left = node_l_r(nd->left);
		return node_r_r(nd);
	}
	return nd;
}

node* add(node* nd, int new_key)
{
    if (nd == NULL) return new node(new_key);
    if (new_key < nd->key) nd->left = add(nd->left, new_key);
    else if (new_key > nd->key) nd->right = add(nd->right, new_key);
    return balance(nd);
}

node* max_node(node* nd) {
    if (!nd->right) return nd;
    return max_node(nd->right);
}

node* min_node ( node* nd) {
    if(!nd->left) return nd;
    return min_node (nd->left);
}


node* find_node(node* nd, int k) {
    if (!nd) return 0;
    if (k < nd->key) find_node(nd->left, k);
    else if (k > nd->key) find_node(nd->right, k);
    else return nd;
}

/*node* del_max_node(node* nd) {
    if (nd->right == 0) return nd->left;
    nd->left = del_max_node(nd->right);
    nd->height = node_h(nd);
    return balance(nd);
}*/

node* del_node(node* nd, int k) {
      int maxx;
      if (!nd) return 0;
      if (k < nd->key) nd->left=del_node(nd->left, k); //
      else if (k > nd->key) nd->right=del_node(nd->right, k); //
      else{ //
      node* _left = nd->left; //
      node* _right = nd->right;
      delete nd; //
      if (!_right and !_left) return NULL;
      else if (!_right) return _left;
      else if (!_left) return _right; //
      else //if (node->left->height>node->right->height)
      {    //
      node* max_n = max_node(_left); //)
      //maxx=max_n->key;
      if (_left==max_n) {            //
            max_n->right=_right;
            return max_n;
            }
      else if (max_n->left!=0) {     //
            _left->right=max_n->left;
            max_n->left->left=_left ;
            max_n->right = _right;
            return max_n;
            }
      else {                        //
            _left->right=max_n->left;
            max_n->left=_left;
            max_n->right=_right;
            return max_n;
            }

      //maxmin=nd->key = max_n->key;
      //max_n->left = del_max_node(_left);//
      //max_n->right = _right;
      //max_n->height = node_h(max_n);
      //balance(max_n);
      //return del_node(_left, maxx );
      //}
      //else maxmin=nd->key=m
      }
    }
    return balance(nd);

}

void printTree(node * nd) {
    if (!nd) return;
    printTree(nd->left);
    cout << "   " << nd->key <<" ("<<int(nd->height)<<")    ";
    printTree(nd->right);
    cout<<endl;
}


int main()
{
    node* head = NULL;
    int k;

    //head = new node(k);
    head = add(head, 15);
    printTree(head);
    head = add(head, 21);
    printTree(head);
    head = add(head, 34);
    printTree(head);
    head = add(head, 11);
    printTree(head);
    head = add(head, 16);
    printTree(head);
    head = add(head, 18);
    printTree(head);
    head = add(head, 20);
    printTree(head);
    head = add(head, 14);
    printTree(head);
    head = add(head, 13);
    printTree(head);
    cout<<endl <<"Enter a key to del >>  ";
    cin >> k;
    head=del_node(head, k);
    printTree(head);

    return 0;
}
