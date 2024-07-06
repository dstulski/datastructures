#ifndef BST_H
#define BST_H

#include <stdbool.h>

typedef struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef struct {
	TreeNode *sentinel;
} BST;

// initializes a BST from an empty struct and populates it with vals
BST *bst_create(int *vals, size_t size);

// deallocates all memory allocated by the BST
void bst_destroy(BST *bst);

// clears all values in the BST
void bst_clear(BST *bst);

// inserts a value into the BST
void bst_insert(BST *bst, int val);

// deletes a value from the BST
void bst_delete(BST *bst, int val);

// returns bool if val exists in BST
bool bst_find(BST *bst, int val);

#endif
