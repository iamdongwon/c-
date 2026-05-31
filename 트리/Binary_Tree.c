#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _Node {
	int key;
	struct _Node *left, *right;
} Node;

Node* createLeaf(int key);
void removeTree(Node *root);
int computeHeight(Node *node);
void traverse(Node *node); // in-order traversal

bool isBST(Node *node, int min, int max);
Node* search(int key, Node *root);
Node* insertNode(int key, Node *root);
Node* deleteNode(int key, Node *root);

int main() {
	Node *root = NULL;
	root = insertNode(8, root);
	root = insertNode(4, root);
	root = insertNode(2, root);
	root = insertNode(1, root);
	root = insertNode(3, root);
	root = insertNode(5, root);
	root = insertNode(12, root);
	root = insertNode(9, root);
	root = insertNode(10, root);
	root = insertNode(15, root);
	root = insertNode(13, root);
	root = insertNode(17, root);

	printf("0. Basic information:\n");
	printf("Height: %d\n", computeHeight(root));
	printf("In-order traversal: ");
	traverse(root);
	printf("\n");
	printf("\n");

	printf("1. Check validity of BST:\n");
	if (isBST(root, INT_MIN, INT_MAX)) printf("This tree is a BST\n");
	else printf("This tree is not a BST\n");
	printf("\n");

	printf("2. Insert 7 into BST:\n");
	insertNode(7, root);
	printf("root->left->right->right key: %d\n", root->left->right->right->key);
	printf("In-order traversal in new BST: ");
	traverse(root);
	printf("\n");
	if (isBST(root, INT_MIN, INT_MAX)) printf("This tree is a BST\n");
	else printf("This tree is not a BST\n");
	printf("\n");

	printf("3. Delete 12 from BST:\n");
	root = deleteNode(12, root);
	printf("root->right key: %d\n", root->right->key);
	printf("In-order traversal in new BST: ");
	traverse(root);
	printf("\n");
	if (isBST(root, INT_MIN, INT_MAX)) printf("This tree is a BST\n");
	else printf("This tree is not a BST\n");
	printf("\n");

	removeTree(root);
	return 0;
}

Node* createLeaf(int key) {
	// write your own code
    Node*node=(Node*)malloc(sizeof(Node));
    node->key=key;
    node->left=NULL;
    node->right=NULL;
    return node;
}

void removeTree(Node *root) {
	// write your own code
	/*while(root!=NULL){
		root=deleteNode(root->key,root);
	}*/
	if (root == NULL) return;
	removeTree(root->left);
	removeTree(root->right);
	free(root);
}

int computeHeight(Node *node) {
	// write your own code
    if(node==NULL) return 0;
    int leftH=computeHeight(node->left);
    int rightH=computeHeight(node->right);
    if(leftH>rightH) return leftH+1;
    else return rightH+1; 
}

void traverse(Node *node) {
	// write your own code
    if(node==NULL) return;
    traverse(node->left);
    printf("%d ",node->key);
    traverse(node->right);
}

// Check all keys in the tree ...
// (1) are in the (min,max) interval
// (2) satisfy BST conditions
bool isBST(Node *root, int min, int max) {
	// write your own code
    if(root==NULL) return true;
    if(root->key>=max || root->key<=min) return false;
    if(!isBST(root->right,root->key,max)) return false; 
    if(!isBST(root->left,min,root->key)) return false;
    return true;
}

Node* search(int key, Node *root) {
	// write your own code
    if(root==NULL) return NULL;
    if(key==root->key) return root;
    if(key>root->key) return search(key,root->right);
    else return search(key,root->left);
}

// This returns the root after insertion
Node* insertNode(int key, Node *root) {
	// write your own code
    if(root==NULL) return createLeaf(key);
    if(key>root->key) {
        root->right=insertNode(key,root->right);
        return root;
    }
    else{
        root->left=insertNode(key,root->left);
        return root;
    }
}

// This returns the root after deletion
Node* deleteNode(int key, Node *root) {
	// write your own code
	if(root==NULL){
		printf("NOPE!\n");
		return NULL;
	}
    if(root->key<key){
		root->right=deleteNode(key,root->right);
	}
	else if(root->key>key){
		root->left=deleteNode(key,root->left);
	}
	else{
		if(root->right==NULL && root->left==NULL){
			free(root);
			return NULL;
		}
		else if(root->left==NULL || root->right==NULL){
			Node*node=root->left==NULL?root->right:root->left;
			free(root);
			return node;
		}
		else{
			Node*s=root->right;
			while(s->left != NULL){
				s=s->left;
			}
			root->key=s->key;
			root->right=deleteNode(s->key,root->right);
		}
	}
	return root;
}