#include <stdio.h>
#define MAX 100
char src[MAX] = { 0,'a', 98,99 };
int a[MAX];
int visited[MAX];
int n, r;
void process() {
	printf("[");
	for (int i = 1; i <= r; i++) {
		printf("%c ", src[a[i]]);
	}
	puts("]");
}
int isFinished(int k) {
	return k == r;
}

int makeCandidate(int k,  int * candi) {
	int cnt = 0;
	int inperm[MAX] = { 0 };
	for (int i = 1; i < k; i++) {
		inperm[a[i]] = 1;
	}

	for (int i = 1; i <= n; i++) {
		if (!inperm[i]) {
			candi[cnt++] = i;
		}
	}
	return cnt;
}
void btr_perm(int k) {
	int candi[MAX];
	int cCnt;
	if (isFinished(k)) {
		process();
		return;
	}
	k++;
	cCnt = makeCandidate(k, candi);
	for (int i = 0; i <cCnt; i++) {
		a[k] = candi[i];
		btr_perm(k);
	}
}

int main() {
	n = 3;
	r = 2;
	btr_perm(0);
	return 0;
}
