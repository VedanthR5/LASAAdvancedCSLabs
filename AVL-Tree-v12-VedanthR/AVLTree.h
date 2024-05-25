
#ifndef AVLTREE_H
#define AVLTREE_H

#include<stdlib.h>  
#include<stdio.h>  

 
//#define HEIGHT 1  
#define HEIGHT(t) ((t == NULL) ? 0 : t->height)

struct node
{  
	int key_value; 
struct node* parent;
	struct node* left;
	struct node* right;  
	int height;  
};


class AVLTree
{
public:
	AVLTree();
	~AVLTree();

	node*	root;
	
	struct node* get_node(int val);
	int get_height(struct node* root);
	int get_balance(struct node* root);
	int max(int a, int b);
	struct node* left_rotate(struct node* root);
	struct node* right_rotate(struct node* root);
	struct node* insert(struct node* root, int val);
	struct node* balance_tree(struct node* root);
	struct node* deletion(struct node* root, int val);
	struct node* inorder_succ_right_tree(struct node* root);
	void preorder(struct node* root);
	void inorder(struct node* root);
	void inorder_level(struct node* tree, int level);
	int max_level(struct node* tree, int level, int max);
	int min_level(struct node* tree, int level, int min);

	int sumorder(struct node* tree);
	void clear(struct node* tree);
	void display(node*, int level, int dir);
	 
};

#endif // AVLTREE_H
