#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct _SegmentTree {
	int nodes[2*MAX_SIZE+1];
	int size;
} SegmentTree;

int max(int a, int b);
void construct(int items[], int n, SegmentTree *tree);
void update(SegmentTree *tree, int item, int index);
int computeMax(SegmentTree *tree, int left, int right);
void print(SegmentTree *tree);

int main() {
	int items[9] = { 0, 5, 6, 1, 3, 8, 2, 7, 4 }, n = 8;
	SegmentTree tree;
	construct(items, n, &tree);
	print(&tree);

	printf("max between %d and %d elements: %d\n", 1, 4, computeMax(&tree, 1, 4));
	printf("max between %d and %d elements: %d\n", 2, 5, computeMax(&tree, 2, 5));
	printf("max between %d and %d elements: %d\n", 6, 8, computeMax(&tree, 6, 8));

	update(&tree, 9, 3);
	print(&tree);
	printf("max between %d and %d elements: %d\n", 1, 4, computeMax(&tree, 1, 4));
	printf("max between %d and %d elements: %d\n", 2, 5, computeMax(&tree, 2, 5));
	printf("max between %d and %d elements: %d\n", 6, 8, computeMax(&tree, 6, 8));
	return 0;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void construct(int items[], int n, SegmentTree *tree) {
	int NumLeafs=1;
    while(NumLeafs<n) NumLeafs*=2;
    tree->size=NumLeafs*2-1;

    for(int i=(tree->size)/2+1;i<n+(tree->size)/2+1;i++){
        tree->nodes[i]=items[i-(tree->size)/2];
    }
	for(int i=n+(tree->size)/2+1;i<tree->size+1;i++){
		tree->nodes[i]=0;
	}
	for(int i=(tree->size)/2;i>0;i--){
		tree->nodes[i]=max(tree->nodes[i*2],tree->nodes[i*2+1]);
	}

}//n=0은 상정하지 않는다.

void update(SegmentTree *tree, int item, int index) {
	int i=index+(tree->size)/2;
	tree->nodes[i]=item;
	
	while(i>1){
		i/=2;
		tree->nodes[i]=max(tree->nodes[i*2],tree->nodes[i*2+1]);
	}
}

int computeMax(SegmentTree *tree, int left, int right) {
	int result=0;
	left+=(tree->size)/2;
	right+=(tree->size)/2;

	while(left<=right){
		if(left%2==1) result=max(tree->nodes[left],result);
		if(right%2==0) result=max(tree->nodes[right],result);
		left=(left+1)/2;
		right=(right-1)/2;
	}

	return result;
}

void print(SegmentTree *tree) {
	printf("tree: ");
	for (int i = 1; i <= tree->size; i ++) printf("%d ", tree->nodes[i]);
	printf("\n");
}