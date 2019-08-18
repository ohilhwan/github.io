#include <stdio.h>
#define SWAP(x, y) {int temp = y; y = x; x = temp;}
#define MAX 1
#define MIN 100


int main() {
	freopen("input.txt", "r", stdin);
	int data[101];
	int N;
	int max_idx, min_idx;
	for (int testCase = 1; testCase <= 10; testCase++) {
		scanf("%d", &N);
		for (int i = 1; i < 101; i++) {
			scanf("%d", data + i);
			int t;
			for (int j = i - 1; j; j--) {
				if (data[j] < data[j + 1]) {
					SWAP(data[j], data[j + 1]);
				}
				else {
					break;
				}
			}
		}

		while (N--) {
			max_idx = MAX;
			min_idx = MIN;
			data[MAX]--;
			data[MIN]++;

			while (data[max_idx] < data[max_idx + 1]) {
				SWAP(data[max_idx], data[max_idx + 1]);
				max_idx++;
			}


			while (data[min_idx] > data[min_idx - 1]) {
				SWAP(data[min_idx], data[min_idx - 1]);
				min_idx--;
			}
		}

		printf("#%d %d\n", testCase, data[MAX] - data[MIN]);
	}
	return 0;
}
