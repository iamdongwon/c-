#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*생성,삽입,전체제거,제거,크기,노드얻기,반대,출력*/

typedef struct Node{
    int data;
    struct Node*next;
}Node;

typedef struct Linked_list{
    Node*head;
}Linked_list;

void insert(Linked_list*list,int data,int index);
void removeLinkedList(Linked_list *list);
int getSize(Linked_list *list);
Node *getNode(Linked_list *list, int index);
void delete(Linked_list *list, int index);
void deleteAll(Linked_list *list);
void reverse(Linked_list *list);
void printItems(Linked_list *list);


int main(){
    Linked_list list;
    list.head=NULL;

    printf("1. Insertion:\n");
	insert(&list, 1, 0);
	printItems(&list); // 1 -> NULL

	insert(&list, 2, 1);
	printItems(&list); // 1 -> 2 -> NULL

	insert(&list, 3, 1);
	printItems(&list); // 1 -> 3 -> 2 -> NULL

	insert(&list, 4, 1);
	printItems(&list); // 1 -> 4 -> 3 -> 2 -> NULL

	insert(&list, 4, 6); // Error: index is out of range
	insert(&list, 4, -1); // Error: index is out of range

	// 2. Deletion
	printf("\n2. Deletion:\n");
	delete(&list, 0);
	printItems(&list); // 4 -> 3 -> 2 -> NULL

	delete(&list, 1);
	printItems(&list); // 4 -> 2 -> NULL

	delete(&list, -1); // Error: index is out of range
	delete(&list, 2); // Error: index is out of range

	deleteAll(&list);
	printItems(&list); // NULL

	// 3. Reversion
	printf("\n3. Reversion:\n");
	insert(&list, 1, 0);
	insert(&list, 2, 1);
	insert(&list, 3, 1);
	insert(&list, 4, 1);
	printItems(&list); // 1 -> 4 -> 3 -> 2 -> NULL
	reverse(&list);
	printItems(&list); // 2 -> 3 -> 4 -> 1 -> NULL

	removeLinkedList(&list);


    return 0;
}

void removeLinkedList(Linked_list *list) {
	deleteAll(list);
}

void deleteAll(Linked_list *list){
    while(list->head!=NULL){
        delete(list,0);
    }
}

int getSize(Linked_list *list){
    Node*curr=list->head;
    int sum=0;
    while(curr != NULL){
        curr=curr->next;
        sum+=1;
    }
    return sum;
}

Node *getNode(Linked_list *list, int index){
    Node*curr=list->head;
    
    while(curr != NULL && index>=0){
        if(index==0) return curr;
        curr=curr->next;
        index--;
    }

    return NULL;
}

void insert(Linked_list*list,int data,int index){
    if(index==0){
        Node*new=(Node*)malloc(sizeof(Node));
        new->data=data;
        new->next=list->head;
        list->head=new;
        return;
    }
    Node*prev=getNode(list,index-1);
    if(prev==NULL){
        printf("ERROR\n");
        return;
    }
    Node*new=(Node*)malloc(sizeof(Node));
    new->data=data;
    new->next=prev->next;
    prev->next=new;
}


void delete(Linked_list *list, int index){
    if(list->head==NULL){
        printf("ERROR\n");
        return;
    }
    if(index==0){
        Node*node=list->head;
        list->head=list->head->next;
        free(node);
        return;
    }
    Node*curr=getNode(list,index);
    Node*prev=getNode(list,index-1);
    if(curr==NULL || prev==NULL){
        printf("ERROR\n");
        return;
    }
    prev->next=curr->next;
    free(curr);
    return;
}

void reverse(Linked_list *list){
    if(list->head==NULL || list->head->next==NULL) return;

    Node *prevNode=NULL,*currNode=list->head,*nextNode;
    while(currNode != NULL){
        nextNode=currNode->next;
        currNode->next=prevNode;
        prevNode=currNode;
        currNode=nextNode;
    }
    list->head=prevNode;
}


void printItems(Linked_list *list){
    Node*curr=list->head;
    while(curr != NULL){
        printf("%d->",curr->data);
        curr=curr->next;
    }
    printf("NULL\n");
}