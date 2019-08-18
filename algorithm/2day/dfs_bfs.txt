/*
7 8
1 2
1 3
2 4
2 5
4 6
5 6
3 7
6 7
*/
#include <stdio.h>
#define MAX 1001
int g[MAX][MAX];
int stack[MAX];
int top;
int visited[MAX];
int V;
int E;

int queue[MAX];
int front, rear;
void init() {
	for (int i = 1; i <= V; i++) {
		visited[i] = 1;
	}
}
void dfs1(int start) {
	init();
	stack[top++] = start;
	visited[start] = 0;
	printf("dfs1 : [");
	int u;
	while (top) {
		u = stack[--top];
		printf("%d ", u);

		for (int i = 1; i <= V; i++) {
			if (visited[i] && g[u][i]) {
				stack[top++] = i;
				visited[i] = 0;
			}
		}
	}

	puts("]");
}
void bfs(int start) {
	init();
//	stack[top++] = start;
	queue[rear++] = start;
	visited[start] = 0;
	printf("bfs : [");
	int u;
	while (front!=rear) {
//		u = stack[--top];
		u = queue[front++];
		printf("%d ", u);

		for (int i = 1; i <= V; i++) {
			if (visited[i] && g[u][i]) {
				queue[rear++] = i;
				visited[i] = 0;
			}
		}
	}

	puts("]");
}
void dfs2(int start) {
	init();
	stack[top++] = start;
//	visited[start] = 1;
	printf("dfs2 : [");
	int u;
	while (top) {
		u = stack[--top];
		if (visited[u]) {
			visited[u] = 0;

			printf("%d ", u);

			for (int i = 1; i <= V; i++) {
				if (visited[i] && g[u][i]) {
					stack[top++] = i;
					//			visited[i] = 1;
				}
			}
		}
	}

	puts("]");
}
void dfs_rec(int start) {
	printf("%d ", start);
	visited[start] = 0;

	for (int i = 1; i <= V; i++) {
		if (visited[i] && g[start][i]) {
			dfs_rec(i);
		}
	
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &V, &E);
	for (int i = 0; i < E; i++) {
		int sn, en;
		scanf("%d %d", &sn, &en);
		g[sn][en] = g[en][sn] = 1;
	}
#if 0
	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			printf("%d ", g[i][j]);
		}
		puts("");
	}
#endif
	dfs1(1);
	dfs2(1);
	init();
	printf("dfs_rec : [");
	dfs_rec(1);
	puts("]");
	bfs(1);
	return 0;
}
