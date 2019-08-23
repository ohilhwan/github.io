#include <stdio.h>

int main() {
	freopen("input.txt", "r", stdin);
	int num[1000];
	for (int testCase = 1; testCase <= 10; testCase++) {
		int sum = 0;
		int n;
		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%d", &num[i]);// num + i);
		}
		int len = n - 2;
		for (int i = 2; i < len; i++) {
			int max = num[i - 2];
			if (max < num[i - 1])
				max = num[i - 1];
			if (max < num[i + 1])
				max = num[i + 1];
			if (max < num[i + 2])
				max = num[i + 2];

			if (max < num[i]) {
				sum += num[i] - max;
				i += 2;
			}
		}
		printf("#%d %d\n", testCase, sum);
	}
	return 0;
}
