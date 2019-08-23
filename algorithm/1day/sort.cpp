#include <stdio.h>
#include <malloc.h>
#define MAX 100
#define MYSWAP(a,b){int t = a; a = b; b = t;} 
const int MAX2 = 200;
int src[] = { 2,3,1,6,4,5,8,7,9 };
int n;

void print(const char * str) {
	printf("%s : [",str);
	for (int i = 0; i < n; i++) {
		printf("%d ", src[i]);
	}
	puts("]");
}
void selectSort(int size) {
	int iLen = size - 1;
//	int max;
	for (int i = 0; i < iLen; i++ ) {
		int maxIdx = 0;
		int jLen = size - i;
		for (int j = 1; j < jLen; j++) {
			if (src[j] > src[maxIdx]) {
				maxIdx = j;
			}
		}
#if 0
		int t = src[maxIdx];
		src[maxIdx] = src[jLen-1];
		src[jLen-1] = t;
#endif
		MYSWAP(src[maxIdx], src[jLen - 1]);
	}
}
void bubbleSort(int size) {
	int iLen = size - 1;
	//	int max;
	for (int i = 0; i < iLen; i++) {
		
		int jLen = size - i-1;
		for (int j = 0; j < jLen; j++) {
			if (src[j] > src[j+1]) {
				int t = src[j];
				src[j] = src[j + 1];
				src[j + 1] = t;
			}
	}
}

}
int main() {
#if 0
	int n = 10;
	int * p1 = (int *)malloc(n * sizeof(int));
	int * p2 = (int *)calloc(n , sizeof(int));
	printf("p1[0] : %d, p2[0]:%d\n", p1[0], p2[0]);
	
#endif
#if 1
	n = 9;
	print("Á¤·ÄÀü");
	selectSort(n);
//	bubbleSort(n);
	print("Á¤·ÄÈÄ");
#endif
	return 0;
}
