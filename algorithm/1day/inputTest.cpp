#include <stdio.h>
#include <iostream>
using namespace std;
int main() {
	freopen("input.txt", "r", stdin);
	int i;
	char ch;
	char str[10];
	double d;
#if 0
	scanf("%d", &i);
	scanf(" %c", &ch);
	scanf("%s", str);
	scanf("%lf", &d);
#endif
	cin >> i;
	cin >> ch;
	cin >> str;
	cin >> d;
	printf("i : %d, ch : %c,  str : %s, d : %.2f\n", i,ch, str, d);
	return 0;
}
