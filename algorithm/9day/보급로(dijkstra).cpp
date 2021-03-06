#include <stdio.h>
#include <time.h>
#define MAX 100
#define INF 987654321
typedef struct point {
	int y;
	int x;
}Point;


Point priorityQueue[MAX*MAX + 1];

int distance[MAX + 2][MAX + 2];

int size;
int data[MAX + 2][MAX + 2];
int queueCount;

void push(int idx) {
	while (idx > 1 && distance[priorityQueue[idx / 2].y][priorityQueue[idx / 2].x] >
		distance[priorityQueue[idx].y][priorityQueue[idx].x]) {
		Point t = priorityQueue[idx];
		priorityQueue[idx] = priorityQueue[idx / 2];
		priorityQueue[idx / 2] = t;

		idx = idx / 2;
	}
}

Point pop() {
	Point val = priorityQueue[1];
	priorityQueue[1] = priorityQueue[queueCount--];
	int idx = 1;
	int next = -1;
	while (1) {
		next = idx * 2;

		if (next < queueCount && distance[priorityQueue[next].y][priorityQueue[next].x] >
			distance[priorityQueue[next + 1].y][priorityQueue[next + 1].x]) {
			next = next + 1;
		}

		if (next > queueCount || distance[priorityQueue[idx].y][priorityQueue[idx].x] <
			distance[priorityQueue[next].y][priorityQueue[next].x]) {
			break;
		}
		Point t = priorityQueue[idx];
		priorityQueue[idx] = priorityQueue[next];
		priorityQueue[next] = t;

		idx = next;
	}
	return val;
}

void dijkstra() {

	Point u;
	int ux, uy, tx, ty;
	// ÃÊ±âÈ­
	queueCount = 0;
	for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
			distance[i][j] = INF;
			priorityQueue[++queueCount].y = i;
			priorityQueue[queueCount].x = j;
		}
	}
	distance[1][1] = 0;

	while (queueCount) {
		u = pop();
		uy = u.y;
		ux = u.x;

		if (uy == size && ux == size) {
			break;
		}

		for (int i = 1; i <= queueCount; i++) {
			ty = priorityQueue[i].y;
			tx = priorityQueue[i].x;
			if ((ux - tx == 0 && uy - ty == 1)||
				(ux - tx == 0 && uy - ty == -1)||
				(ux - tx == 1 && uy - ty == 0)||
				(ux - tx == -1 && uy - ty == 0)
			){
				if (distance[ty][tx] > distance[uy][ux] + data[ty][tx]) {
					distance[ty][tx] = distance[uy][ux] + data[ty][tx];
					push(i);
				}
			}
		}
	}
}

int main() {
	time_t start = clock();
	freopen("input.txt", "r", stdin);
	int tc;
	scanf("%d", &tc);
	for (int testCase = 1; testCase <= tc; testCase++) {
		scanf("%d", &size);

		for (int i = 1; i <= size; i++) {
			for (int j = 1; j <= size; j++) {
				scanf("%1d", &data[i][j]);
			}
		}
		dijkstra();

		printf("#%d %d\n", testCase, distance[size][size]);
	}
	time_t end = clock();
	printf("time : %f\n", (double)(end - start));
	return 0;
}
