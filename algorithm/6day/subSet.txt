#include <stdio.h>
char data[100] = { 'a', 98,99 };
int n;
void subSet() {
	for (int i = 0; i < (1<<n); i++) {
		printf("{");
		for (int j = 0; j < n; j++) {
			if (i & (1 << j)){// == (1<<j)) {
				printf("%c ", data[j]);
			}
		}
		puts("}");
	}
}

int main() {
	n = 3;
	subSet();
	return 0;
}
