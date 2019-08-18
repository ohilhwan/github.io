#include <stdio.h>
#define MAX 100
char src[MAX] = {0,'a', 98,99};
char temp[MAX];
int n, r;
void print() {
	printf("[");
	for (int i = 1; i <= r; i++) {
		printf("%c ", temp[i]);
	}
	puts("]");
}
void perm(int n, int r) {
	if (r == 0) {
		print();
		return;
	}

	for (int i = n; i; i--) {
		int t = src[n];
		src[n] = src[i];
		src[i] = t;

		temp[r] = src[n];
		perm(n - 1, r - 1);

		t = src[n];
		src[n] = src[i];
		src[i] = t;
	}
}
void pi(int n, int r) {
	if (r == 0) {
		print();
		return;
	}
	for (int i = n; i; i--) {
		int t = src[n];
		src[n] = src[i];
		src[i] = t;

		temp[r] = src[n];
		pi(n , r - 1);

		t = src[n];
		src[n] = src[i];
		src[i] = t;
	}
}
void comb(int n, int r) {
	if (r == 0) {
		print();
		return;
	}

	if (n < r) {
		return;
	}
	temp[r] = src[n];
	comb(n - 1, r - 1);
	comb(n - 1, r);
}
void h(int n, int r) {
	if (r == 0) {
		print();
		return;
	}

	if (n == 0) {
		return;
	}
	temp[r] = src[n];
	h(n , r - 1);
	h(n - 1, r);
}
int main() {
	n = 3;
	r = 2;
	perm(n, r);
	puts("=============");
	pi(n, r);
	puts("=============");
	comb(n, r);
	puts("=============");
	h(n, r);
	puts("=============");

	for (int i = 0; i <= n; i++) {
		r = i;
		comb(n, r);
	}
	return 0;
}
