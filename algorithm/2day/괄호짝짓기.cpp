#include <stdio.h>
int main() {
	freopen("input.txt", "r", stdin);
	char str[1000];
	char stack[1000];

	int len;
	int flag;
	int top;
	char ch;
	char popCh;

	for (int testCase = 1; testCase <= 10; testCase++) {
		top = 0;
		flag = 1;
		//		scanf("%d %s", &len, str);
		scanf("%d ", &len);

		for (int i = 0; i < len; i++) {
			//			ch = str[i];
			scanf("%c", &ch);
			if (!flag)continue;
			if (ch == '{' || ch == '<' || ch == '[' || ch == '(') {
				stack[top++] = ch;
			}
			else {
				if (top == 0) {
					flag = 0;
					//					break;
				}
				else {

					popCh = stack[--top];

					if (ch == '}' && popCh != '{') {
						flag = 0;
						//					break;
					}
					else if (ch == '>' && popCh != '<') {
						flag = 0;
						//					break;
					}
					else if (ch == ']' && popCh != '[') {
						flag = 0;
						//					break;
					}
					else if (ch == ')' && popCh != '(') {
						flag = 0;
						//					break;
					}
				}
			}
		}

		//		if (top != 0) {flag = 0;}

		printf("#%d %d\n", testCase, flag);
	}


	return 0;
}
