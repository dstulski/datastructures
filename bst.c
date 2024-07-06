#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "bst.h"

// returns pointer to a new treenode
static TreeNode *create_node(int val)
{
	TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
	if (new_node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}

	new_node->val = val;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

BST *bst_create(int *vals, size_t size)
{
	BST *bst = (BST *)malloc(sizeof(BST));
	bst->sentinel = create_node(INT_MIN);
	for (size_t i = 0; i < size; i++) {
		bst_insert(bst, vals[i]);
	}
	return bst;
}

void bst_destroy(BST *bst)
{
	bst_clear(bst);
	free(bst->sentinel);
	free(bst);
}

// takes node instead of BST
static void clear(TreeNode *root)
{
	if (root == NULL) {
		return;
	}
	clear(root->left);
	clear(root->right);
	free(root);
}

void bst_clear(BST *bst)
{
	clear(bst->sentinel->right);
}

// takes node instead of BST
static void insert(TreeNode *root, int val)
{
	if (val < root->val) {
		if (root->left == NULL) {
			root->left = create_node(val);
		} else {
			insert(root->left, val);
		}
	} else {
		if (root->right == NULL) {
			root->right = create_node(val);
		} else {
			insert(root->right, val);
		}
	}
}

void bst_insert(BST *bst, int val)
{
	insert(bst->sentinel, val);
}

// find min value in a subtree for deletion
static int min_value(TreeNode *root)
{
	TreeNode *curr = root;
	while (curr->left != NULL) {
		curr = curr->left;
	}
	return curr->val;
}

// takes node instead of BST
static TreeNode *delete(TreeNode *root, int val)
{
	if (root == NULL) {
		return root;
	}
	if (val < root->val) {
		root->left = delete(root->left, val);
	} else if (val > root->val) {
		root->right = delete(root->right, val);
	} else {
		if (root->left == NULL) {
			TreeNode *temp = root->right;
			free(root);
			return temp;
		} else if (root->right == NULL) {
			TreeNode *temp = root->left;
			free(root);
			return temp;
		}
		root->val = min_value(root->right);
		root->right = delete(root->right, root->val);
	}
	return root;
}

void bst_delete(BST *bst, int val)
{
	bst->sentinel->right = delete(bst->sentinel->right, val);
}

// takes node instead of BST
static bool find(TreeNode *root, int val)
{
	if (root == NULL) {
		return false;
	}
	if (val < root->val) {
		return find(root->left, val);
	}
	if (val > root->val) {
		return find(root->right, val);
	}
	return true;
}

bool bst_find(BST *bst, int val)
{
	return find(bst->sentinel->right, val);
}
