#include <stdio.h>
#define MAX 100
int g[MAX][MAX];
int visited[MAX];
int s[MAX];
int top;
int flag;
void dfs_iter(int start) {

	flag = 0;
	int u;
	s[top++] = start;
	visited[start] = 0;
	while (top) {
		u = s[--top];
		if (u == 99) {
			flag = 1;
			break;
		}
		for (int i = 0; i < MAX; i++) {
			if (visited[i] && g[u][i]) {
				s[top++] = i;
				visited[i] = 0;
			}
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
	visited[start] = 0;
	for (int i = 0; i < MAX; i++) {
		if (visited[i] && g[start][i] && !flag) {
			dfs_rec(i);
		}
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
			visited[i] = 1;
			for (int j = 0; j < MAX; j++) {
				g[i][j] = 0;
			}
		}
		scanf("%d %d", &E, &E);

		for (int i = 0; i < E; i++) {
			scanf("%d %d", &sn, &en);
			g[sn][en] = 1;
		}
		dfs_iter(0);
//		dfs_rec(0);
		printf("#%d %d:%d\n", testCase, flag, cnt);
	}

	return 0;
}
