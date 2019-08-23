#include <stdio.h>
#include<time.h>
#define MAX 101
int dp1[MAX];
int dp2[MAX];
int dp3[3];
int cnt1;
int cnt2;
int fibo(int n) {
	cnt1++;
	if (n < 2) {
		return n;
	}
	return fibo(n - 1) + fibo(n - 2);
}
int fibo_rec_dp(int n) {
	cnt2++;
	if (n < 2) {
		return n;
	}
	if (dp1[n] == 0) {
		dp1[n] = fibo_rec_dp(n - 1) + fibo_rec_dp(n - 2);
	}
	return dp1[n];
}
int fibo_iter_dp(int n) {
	dp2[1] = 1;
	for (int i = 2; i <= n; i++) {
		dp2[i] = dp2[i - 1] + dp2[i - 2];
	}
	return dp2[n];
}
int fibo_iter_dp2(int n) {
	dp3[1] = 1;
	for (int i = 2; i <= n; i++) {
		dp3[i%3] = dp3[(i - 1)%3] + dp3[(i - 2)%3];
	}
	return dp3[n%3];
}
int main() {
	time_t start = clock();
	int n = 1000;
//	printf("fibo(%d) : %d\n", n, fibo(n));
//	printf("fibo_rec_dp(%d) : %d\n", n, fibo_rec_dp(n));
//	printf("fibo_iter_dp(%d) : %d\n", n, fibo_iter_dp(n));
	printf("fibo_iter_dp2(%d) : %d\n", n, fibo_iter_dp2(n));
	//	printf("cnt1 : %d, cnt2 : %d\n", cnt1, cnt2);
	time_t end = clock();
	printf("time : %f\n", (double)(end-start));
	return 0;
}
