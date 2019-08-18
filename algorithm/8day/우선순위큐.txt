#include <stdio.h>
#define MAX 101
int heap[MAX];
int hCnt;
void print() {
	printf("heap : [");
	for (int i = 1; i <= hCnt; i++) {
		printf("%d ", heap[i]);
	}
	puts("]");
}
void push(int data) {
	heap[++hCnt] = data;
	int idx = hCnt;
	while (idx>1 && heap[idx] < heap[idx/2]) {
//		if (idx==1 || (heap[idx]  > heap[idx/2])) {break;}

		int t = heap[idx];
		heap[idx] = heap[idx / 2];
		heap[idx / 2] = t;
		idx = idx / 2;
	}
}
int pop() {
	int val = heap[1];
	heap[1] = heap[hCnt--];
	int idx = 1;
	int next;
	while (1) {
		next = idx * 2;
		if (next < hCnt && heap[next] > heap[next + 1]) {next++;}
		if (next > hCnt || heap[idx] < heap[next]) {break;}
		int t = heap[idx];
		heap[idx] = heap[next];
		heap[next] = t;
		idx = next;
	}

	return val;
}
int main() {
	print();
	push(2);
	print();
	push(4);
	print();
	push(3);
	print();
	printf("pop : %d\n", pop());
	print();
	printf("pop : %d\n", pop());
	print();
	printf("pop : %d\n", pop());
	print();
	if (hCnt) {
		printf("pop : %d\n", pop());
		print();
	}
	return 0;
}
