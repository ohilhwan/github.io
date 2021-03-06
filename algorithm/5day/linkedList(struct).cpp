#include <stdio.h>
#include <malloc.h>
typedef struct node {
	int data;
	struct node * lLink;
	struct node * rLink;
}Node;

typedef struct linkedList {
	Node * head;
	Node * tail;
}LinkedList;
LinkedList * list;
int cnt;
void init() {
	cnt = 0;
	list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = (Node*)malloc(sizeof(Node));
	list->tail = (Node*)malloc(sizeof(Node));

	list->head->lLink = NULL;
	list->head->rLink = list->tail;
	list->tail->rLink = NULL;
	list->tail->lLink = list->head;
}

void freeMemory() {
	Node * temp = list->head->rLink;

	while (temp) {
		free(temp->lLink);
		temp = temp->rLink;
	}
	free(list->tail);
	free(list);
}
void print() {
	Node * temp = list->head->rLink;
	printf("[");
	while (temp != list->tail) {
		printf("%d ", temp->data);
		temp = temp->rLink;
	}
	puts("]");
}
void appendF(int data) {
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	list->tail->lLink->rLink = newNode;
	newNode->lLink = list->tail->lLink;
	newNode->rLink = list->tail;
	list->tail->lLink = newNode;
	cnt++;
}
bool deleteF(int idx, int * d) {
	
	if (idx >= cnt) {
		puts("error");
		return false;
	}
	else {
		Node* pos = list->head;
		for (int i = 0; i <= idx; i++) {
			pos = pos->rLink;
		}
	
		pos->lLink->rLink = pos->rLink;
		pos->rLink->lLink = pos->lLink;
		*d = pos->data;
		free(pos);
		return true;
	}

	
}
bool updateF(int idx, int data) {
	if (idx >= cnt) {
		puts("error");
		return false;
	}
	else {
		Node* pos = list->head;
		for (int i = 0; i <= idx; i++) {
			pos = pos->rLink;
		}
		pos->data = data;
		return true;
	}
}

void insertF(int idx, int data) {
	if (idx > cnt) {
		appendF(data);
	}
	else {
		Node * newNode = (Node*)malloc(sizeof(Node));
		newNode->data = data;

		Node* pos = list->head;
		for (int i = 0; i < idx; i++) {
			pos = pos->rLink;
		}
		pos->rLink->lLink = newNode;
		newNode->rLink = pos->rLink;
		pos->rLink = newNode;
		newNode->lLink = pos;
		cnt++;
	}

}
int main() {
	init();
	print();
	appendF(10);
	print();
	appendF(30);
	print();
	appendF(20);
	print();

	insertF(0, 40);
	print();
	insertF(2, 50);
	print();

	updateF(1, 100);
	print();

	int data;
	if (deleteF(2, &data)) {
		printf("del : %d\n", data);
	}
	print();
	freeMemory();

	puts("end");
	return 0;
}
