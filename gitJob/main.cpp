#include <stdio.h>

//prototype
void mstrcpy(char *dest, const char *src);
void mstrcpylen(char *dest, const char *src, int num);
int mstrcmp(const char *a, const char *b);
void InitDB();
void ADD(char *option1, char *option2, char *option3, int emp_no, char name[16], int cl, int phone, int birth);
void DEL(char *option1, char *option2, char *option3, char *condition, char *value, FILE* wf);
void MOD(char *option1, char *option2, char *option3, char *condition, char *value, char *changeColumn, char *chaneValue);
void SCH(char *option1, char *option2, char *option3, char *condition, char *value);
void split(char *input, char splitSTR[][20]);
int atoi(char *str);
int atoiphone(char *str);

int main(int argc, char** argv)
{
	if (argc != 3) {
		printf("전달인자가 정확하지 않습니다.\n");
		return 0;
	}


	FILE *rf, *wf;
	rf = fopen(argv[1], "r");
	wf = fopen(argv[2], "w");
	if (rf == NULL || wf == NULL) {
		printf("txtfile open fail. . . \n");
		return 0;
	}
	printf("read %s file. . . \n", argv[1]);
	InitDB();
	char strLine[100];
	char *pStr;
	char command[4];
	char splitStr[9][20];
	while (!feof(rf)) {
		pStr = fgets(strLine, sizeof(strLine), rf);
		if (pStr == NULL) continue;

		split(strLine, splitStr);

		if (!mstrcmp(splitStr[0], "ADD")) {
			ADD(splitStr[1], splitStr[2], splitStr[3], atoi(splitStr[4]), splitStr[5], splitStr[6][2] - 48, atoiphone(splitStr[7]), atoi(splitStr[8]));
		}
		else if (!mstrcmp(splitStr[0], "DEL")) {
			DEL(splitStr[1], splitStr[2], splitStr[3], splitStr[4], splitStr[5], wf);
		}
		else if (!mstrcmp(splitStr[0], "MOD")) { //수정
			MOD(splitStr[1], splitStr[2], splitStr[3], splitStr[4], splitStr[5], splitStr[6], splitStr[7]);
		}
		else if (!mstrcmp(splitStr[0], "SCH")) {
			SCH(splitStr[1], splitStr[2], splitStr[3], splitStr[4], splitStr[5]);
		}
		else {
			printf("wrong command. . .\n");
			continue;
		}
	}
	fclose(rf);
	fclose(wf);
	return 0;
}