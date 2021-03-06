#include <stdio.h>
#define MAXN 101
#define MAXW 1001
int N;
int W;
int jw[] = {0,10,25,10};
int jp[] = {0,9,10,5};
int dpMemo1[MAXW];
int dpmemo2[MAXN][MAXW];

void dp1() {
	//º¸¼®ÀÌ ¹«ÇÑ´ë
	for (int i = 1; i <= W; i++) {
		for (int j = 1; j <= N; j++) {
			if (i >= jw[j]) {
				if (dpMemo1[i] < dpMemo1[i - jw[j]] + jp[j]) {
					dpMemo1[i] = dpMemo1[i - jw[j]] + jp[j];
				}
			}
		}
	}
}
void dp2() {
	//º¸¼®ÀÌ 1°³
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= W; j++) {
			dpmemo2[i][j] = dpmemo2[i - 1][j];
			if (j >= jw[i]) {
				if (dpmemo2[i][j] < dpmemo2[i - 1][j - jw[i]] + jp[i]) {
					dpmemo2[i][j] = dpmemo2[i - 1][j - jw[i]] + jp[i];
				}
			}
		}
	}
}
int main() {
	N = 3;
	W = 30;

	dp1();
	printf("max1 : %d\n", dpMemo1[W]);
	dp2();
	printf("max2 : %d\n", dpmemo2[N][W]);
	return 0;
}
