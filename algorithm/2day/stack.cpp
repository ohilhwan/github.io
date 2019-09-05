#include <stdio.h>
#define MAX  100
int stack[MAX];
int top;
void print() {
	printf("s : [");
	for (int i = 0; i < top; i++) {
		printf("%d ", stack[i]);
	}
	puts("]");
}
int isFull() {
	return top == MAX;
}
int isEmpty() {
	return top == 0;
}
int push(int data) {
	if (isFull()) {
		return 0;
	}
	else {
		stack[top++] = data;
		return 1;
	}
}
int pop(int * d) {
	if (isEmpty()) {
		return 0;
	}
	else {
		*d = stack[--top];
		return 1;
	}
}
int peek(int * d) {
	if (isEmpty()) {
		return 0;
	}
	else {
		*d = stack[top-1];
		return 1;
	}
}
int main() {
#if 0
	print();
	push(100);
	print();
	push(50);
	print();
	int val;
	if (peek(&val)) {
		printf("val : %d\n", val);
	}
	print();
#endif
	if (top < MAX) {
		stack[top++] = 100;
	}
	print();
	int val;
	if(top) {
		val = stack[--top];
	}
	printf("val : %d\n", val);
	print();
	return 0;
}
