#include <stdio.h>
#define MAX 100
char src[MAX] = {0,'a', 98,99};
int a[MAX];
int visited[MAX];
int n, r;
void print() {
	printf("[");
	for (int i = 1; i <= r; i++) {
		printf("%c ", src[a[i]]);
	}
	puts("]");
}
void btr_perm(int k) {
	if (k == r) {
		print();
		return;
	}
	k++;
	for (int i = 1; i <= n; i++) {
		if (!visited[i]) {
			visited[i] = 1;
			a[k] = i;
			btr_perm(k);
			visited[i] = 0;
		}
	}
}
void btr_pi(int k) {
	if (k == r) {
		print();
		return;
	}
	k++;
	for (int i = 1; i <= n; i++) {
		a[k] = i;
		btr_pi(k);
	}
}
int main() {
	n = 3;
	r = 2;
	btr_perm(0);
	puts("============");
	btr_pi(0);
	return 0;
}
