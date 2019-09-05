#include <stdio.h>
#define MAX 100
char src[MAX] = {0,'a', 98,99};
int a[MAX];
int visited[MAX];
int n;
void print() {
	printf("[");
	for (int i = 1; i <= n; i++) {
		if (a[i]) {
			printf("%c ", src[i]);
		}
	}
	puts("]");
}
void btr_subset(int k) {
	if (k == n) {
		print();
		return;
	}
	k++;
#if 0
	for (int i = 0; i <2; i++) {
		a[k] = i;
		btr_subset(k);
	}
#endif
	a[k] = 0;
	btr_subset(k);

	a[k] = 1;
	btr_subset(k);

}
int main() {
	n = 3;
	
	btr_subset(0);
	return 0;
}
