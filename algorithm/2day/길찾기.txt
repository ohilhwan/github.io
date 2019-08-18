#include <stdio.h>
#define MAX 100
int left[MAX];
int right[MAX];

int s[MAX];
int top;
int flag;
void dfs_iter(int start) {
	flag = 0;
	int u;
	s[top++] = 0;

	while (top) {
		u = s[--top];
		if (u == 99) {
			flag = 1;
			break;
		}
		if (left[u]) {
			s[top++] = left[u];
		}

		if (right[u]) {
			s[top++] = right[u];
		}
	}

}
int cnt = 0;
void dfs_rec(int start) {
	cnt++;
	if (start == 99) {
		flag = 1;
		return;
	}

	if (left[start]){// && !flag) {
		dfs_rec(left[start]);
	}
	if (right[start]){// && !flag) {
		dfs_rec(right[start]);
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	int E;
	int sn, en;

	for (int testCase = 1; testCase <= 10; testCase++) {
		flag = 0;
		cnt = 0;
		for (int i = 0; i < MAX; i++) {
			left[i] = 0;
			right[i] = 0;
		}
		scanf("%d %d", &E, &E);

		for (int i = 0; i < E; i++) {
			scanf("%d %d", &sn, &en);
			if (left[sn]) {
				right[sn] = en;
			}
			else {
				left[sn] = en;
			}
		}
//		dfs_iter(0);
		dfs_rec(0);
		printf("#%d %d:%d\n", testCase, flag, cnt);
	}

	return 0;
}
