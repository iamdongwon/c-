#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


typedef struct _Node {
	int key, height;
	struct _Node *left, *right;
} Node;

Node* createLeaf(int key);
void removeTree(Node *root);
int getHeight(Node *node);
void updateHeight(Node *node);
int computeBalanceFactor(Node *node);
void traverse(Node *node); // in-order traversal

Node* LLRotation(Node *root);
Node* RRRotation(Node *root);
Node* LRRotation(Node *root);
Node* RLRotation(Node *root);
Node* updateNode(Node *root);

bool isAVL(Node *node, int min, int max);
Node* insertNode(int key, Node *root);
Node* deleteNode(int key, Node *root);

int main() {
	Node *root = createLeaf(8);
	root = insertNode(4, root);
	root = insertNode(12, root);
	root = insertNode(2, root);
	root = insertNode(5, root);
	root = insertNode(9, root);
	root = insertNode(15, root);
	root = insertNode(1, root);
	root = insertNode(3, root);
	root = insertNode(10, root);
	root = insertNode(13, root);
	root = insertNode(17, root);

	printf("0. Basic information:\n");
	printf("Height: %d\n", getHeight(root));
	printf("In-order traversal: ");
	traverse(root);
	printf("\n");
	printf("\n");

	printf("1. Check validity of AVL:\n");
	if (isAVL(root, INT_MIN, INT_MAX)) printf("This tree is a AVL tree\n");
	else printf("This tree is not a AVL tree\n");
	printf("\n");

	printf("2. Insert 11 into AVL:\n");
	insertNode(11, root);
	printf("root->right->left->key: %d\n", root->right->left->key);
	printf("root->right->left->left->key: %d\n", root->right->left->left->key);
	printf("root->right->left->right->key: %d\n", root->right->left->right->key);
	printf("In-order traversal in new AVL: ");
	traverse(root);
	printf("\n");
	if (isAVL(root, INT_MIN, INT_MAX)) printf("This tree is a AVL tree\n");
	else printf("This tree is not a AVL tree\n");
	printf("\n");

	printf("3. Delete 5 from BST:\n");
	root = deleteNode(5, root);
	printf("root->left->key: %d\n", root->left->key);
	printf("root->left->left->key: %d\n", root->left->left->key);
	printf("root->left->right->key: %d\n", root->left->right->key);
	printf("root->left->right->left->key: %d\n", root->left->right->left->key);
	printf("In-order traversal in new BST: ");
	traverse(root);
	printf("\n");
	if (isAVL(root, INT_MIN, INT_MAX)) printf("This tree is a AVL tree\n");
	else printf("This tree is not a AVL tree\n");
	printf("\n");

	removeTree(root);
	return 0;
}

Node* createLeaf(int key) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->key = key;
	node->height = 1;
	node->left = node->right = NULL;
	return node;
}

void removeTree(Node *root) {
	if (root == NULL) return;
	removeTree(root->left);
	removeTree(root->right);
	free(root);
}

int getHeight(Node *node) {
	// write your own code
    if(node==NULL) return 0;//바로 밸런스 계선하면 널의 높이에서 에러가 날 수 있읜 여기서 안전하게 해줌.
    return  node->height;
}

void updateHeight(Node *node) {
	// write your own code
    /*if(node->left==NULL && node->right==NULL){
        node->height=1;
        return;
    }
    else if(node->left==NULL){
        updateHeight(node->right);
        node->height=node->right->height+1;
    }
    else if(node->right==NULL){
        updateHeight(node->left);
        node->height=node->left->height+1;
    }
    else{
        updateHeight(node->left);
        updateHeight(node->right);
        node->height=node->left->height>node->right->height?node->left->height+1:node->right->height+1; 
        //여기서 노드 전체의 높이 초기화 하려고 짠거
    }*/
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
	node->height = leftHeight > rightHeight ? leftHeight+1 : rightHeight+1;//이미 아랫부분 높이가 제대로 되어있다고 가정한듯.
}

int computeBalanceFactor(Node *node) {
	// write your own code
    return getHeight(node->left)-getHeight(node->right);
}
void traverse(Node *node) {
	if (node == NULL) return;
	traverse(node->left);
	printf("%d ", node->key);
	traverse(node->right);
}

// Check all keys in the subtree are in the (min,max) interval
bool isAVL(Node *root, int min, int max) {
	// write your own code
}

// This returns the root after insertion
Node* insertNode(int key, Node *root) {
	if (root == NULL) return createLeaf(key);
	if (key < root->key) root->left = insertNode(key, root->left);
	else root->right = insertNode(key, root->right);

	root = updateNode(root);
	return root;
}

// This returns the root after deletion
Node* deleteNode(int key, Node *root) {
	if (key < root->key)
		root->left = deleteNode(key, root->left);
	else if (key > root->key)
		root->right = deleteNode(key, root->right);
	else {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			root = NULL;
			return root;
		}
		else if (root->left == NULL || root->right == NULL) {
			Node *child = root->left != NULL ? root->left : root->right;
			free(root);
			root = child;
			return child;
		}
		else {
			Node *successor = root->right;
			while (successor->left != NULL)
				successor = successor->left;
			root->key = successor->key;
			root->right = deleteNode(successor->key, root->right);
		}
	}

	root = updateNode(root);
	return root;
}

Node* LLRotation(Node *root) {
	// write your own code
    Node*node=root->left;
    root->left=node->right;
    node->right=root;
    root=node;
    return root;
}

Node* RRRotation(Node *root) {
	// write your own code
    Node*node=root->right;
    root->right=node->left;
    node->left=root;
    root=node;
    return root;
}

Node* LRRotation(Node *root) {
	// write your own code
    root->left=RRRotation(root->left);
    
    return LLRotation(root);
}

Node* RLRotation(Node *root) {
	// write your own code
    root->right=LLRotation(root->right);
    return RRRotation(root);
}

// This returns the root after update
Node* updateNode(Node *root) {
	// write your own code
    uodateHeight(root);
    if(computeBalanceFactor(root)==2 && computeBalanceFactor(root)>=0){
        return LLRotaion(root);//자식이 2명의 손자를 데리고 있으면 LL처리한다.
    }
    else if(computeBalanceFactor(root)==2){
        return LRRotation(root);
    }
    else if(computeBalanceFactor(root)==-2 && computeBalanceFactor(root)<=0){
        return RRRotaion(root);//자식이 2명의 손자를 데리고 있으면 RR처리한다.
    }
    else if(computeBalanceFactor(root)==-2){
        return RLRotation(root);
    }


}