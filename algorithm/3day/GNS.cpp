#include <stdio.h>
//#include <time.h>
char keys[][4] = { "ZRO", "ONE", "TWO", "THR","FOR", "FIV", "SIX", "SVN", "EGT", "NIN" };
int getNum(char * sNum) {
	int idx = 0;
	int flag = 1;
	for (int i = 0; i < 10; i++) {
		flag = 1;
		idx = 0;
		while (keys[i][idx]) {
			if (keys[i][idx] != sNum[idx]) {
				flag = 0;
				break;
			}
			idx++;
		}
		if (flag) {
			return i;
		}
	}
	return 10;
}
int main() {
	//	time_t start = clock();
	freopen("input.txt", "r", stdin);
	int tc;
	char sNum[4];
	int cnt;

	int nums[11];
	scanf("%d", &tc);

	for (int testCase = 1; testCase <= tc; testCase++) {
		for (int i = 0; i < 10; i++) {
			nums[i] = 0;
		}
		scanf("%s %d", sNum, &cnt);

		for (int i = 0; i < cnt; i++) {
			scanf("%s", sNum);
			//			nums[getNum(sNum)]++;
#if 1
			if (sNum[0] == 'Z') {
				nums[0]++;
			}
			else if (sNum[0] == 'O') {
				nums[1]++;
			}
			else if (sNum[1] == 'W') {
				nums[2]++;
			}
			else if (sNum[1] == 'H') {
				nums[3]++;
			}
			else if (sNum[1] == 'O') {
				nums[4]++;
			}
			else if (sNum[2] == 'V') {
				nums[5]++;
			}
			else if (sNum[2] == 'X') {
				nums[6]++;
			}
			else if (sNum[1] == 'V') {
				nums[7]++;
			}
			else if (sNum[0] == 'E') {
				nums[8]++;
			}
			else if (sNum[0] == 'N') {
				nums[9]++;
			}
#endif
		}
#if 0
		int sum = 0;
		for (int i = 0; i < 10; i++) {
			sum += nums[i];
		}
		printf("%d : %d\n", cnt, sum);
#endif
#if 1
		printf("#%d ", testCase);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < nums[i]; j++) {
				printf("%s ", keys[i]);
			}
		}
		puts("");

#endif

	}

	//	time_t end = clock();
	//	printf("time : %f\n", (double)(end-start));
	return 0;
}


