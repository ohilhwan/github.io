#include <stdio.h>
#define MAX 100
int data[MAX + 2][MAX + 2];
int posArr[MAX];

int main() {
	freopen("input.txt", "r", stdin);
	int sel;
	int min;
	int pos;
	int k;
	int sum;
	int cnt;
	int flag;
	for (int testCase = 1; testCase <= 10; testCase++) {

		scanf("%d", &cnt);
		cnt = 0;
		for (int i = 1; i <= MAX; i++) {
			for (int j = 1; j <= MAX; j++) {
				scanf("%d", data[i] + j);
			}
		}
		for (int i = 1; i <= MAX; i++) {
			if (data[MAX][i]) {
				posArr[cnt++] = i;
			}
		}

		sel = 0;
		min = MAX * MAX;

		for (int i = 0; i < cnt; i++) {

			pos = posArr[i];
			k = MAX;
			sum = 0;
			while (k--) {
				flag = 0;
				while (data[k][pos + 1]) {
					sum++;
					pos++;
					flag = 1;
				}

				while (flag == 0 && data[k][pos - 1]) {
					sum++;
					pos--;
				}
			}

			if (sum < min) {
				min = sum;
				sel = pos;
			}
		}
		printf("#%d %d\n", testCase, sel - 1);
	}

	return 0;
}
