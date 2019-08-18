#include <stdio.h>
#define MAX 101
#define INF 987654321
int g[MAX][MAX];
int level[MAX];
int q[MAX*MAX];

int main() {
	freopen("input.txt", "r", stdin);
	int n;
	int sn, en;
	int start;
	for (int testCase = 1; testCase <= 10; testCase++) {
		for (int i = 1; i < MAX; i++) {
			level[i] = INF;
			for (int j = 1; j < MAX; j++) {
				g[i][j] = 0;
			}
		}
		scanf("%d", &n);
		scanf("%d", &start);
		int len = n / 2;
		for (int i = 0; i < len; i++) {
			scanf("%d %d", &sn, &en);
			g[sn][en] = 1;
		}

		int front = 0, rear = 0;
		q[rear++] = start;
		level[start] = 0;
		int u;
		while (front != rear) {
			u = q[front++];

			for (int i = 1; i < MAX; i++) {
				if (g[u][i] && level[i] > level[u] + 1) {
					level[i] = level[u] + 1;
					q[rear++] = i;
				}
			}
		}

		int idx = 1;
		int max = 0;
		for (int i = 1; i < MAX; i++) {
			if (level[i] != INF && max <= level[i]) {
				idx = i;
				max = level[i];
			}
		}

		printf("#%d %d\n", testCase, idx);

	}
	return 0;
}
