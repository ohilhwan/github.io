#include <stdio.h>

static char splitSTR[8][20];

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != 0) { dest[i] = src[i]; i++; }
	dest[i] = src[i];
}
void mstrcpylen(char *dest, const char *src, int num)
{
	int i;
	for (i = 0; i < num; i++) { dest[i] = src[i]; }
	dest[num] = '\0';
}

int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != 0; i++) { if (a[i] != b[i]) return a[i] - b[i]; }
	return a[i] - b[i];
}

void split(char *input, char splitSTR[][20]) {
	int i = 0;
	int j = 0;
	int cnt = 0;
	
	while (input[i]) {
		if (input[i] == ',') {
			splitSTR[cnt][j] = '\0';
			i++; cnt++; j = 0;
			continue;
		}
		else {
			splitSTR[cnt][j++] = input[i];
			i++;
		}
	}

	splitSTR[cnt][j-1] = '\0';
}

int atoi(char *str) {
	int tmp = 0;
	while (*str) {
		tmp = tmp * 10 + (int)(*str - 48);
		str++;
	}
	return tmp;
}
int atoiphone(char *str) {
	int tmp = 0;
	str = str + 4;
	while (*str) {
		if (*str == '-') {
			str++;
			continue;
		}
		tmp = tmp * 10 + (int)(*str - 48);
		str++;
	}
	return tmp;
}

#define NUM_FIELD_MAX 10
#define NAME_FIELD_MAX 3
#define NAME_LEN_MAX 16
#define FIELD_MAX (NUM_FIELD_MAX + NAME_FIELD_MAX)
#define RET_MAX 5

// 테이블에 들어올 수 있는 최대 레코드 개수는 5만이지만
// 레코드에게 메모리 할당할 레코드의 Pool인 Record 배열의 크기는 10만으로 잡았다
// 삽입 삭제가 빈번히 발생하는 경우, 중간에 삭제되어 빵꾸난 슬롯을 회수하지 않으므로, 인덱스가 5만을 벗어날 수 있기 때문이다.
#define MAX_N 200000
#define HASH_MAX 400009

typedef struct RECORD {
	int num_data[NUM_FIELD_MAX];
	//int join_year;
	//int emp_no;
	//int cl;
	//int phone;
	//int phone_front;
	//int phone_rear;
	//int birth;
	//int birth_year;
	//int birth_month;
	//int birth_day;
	char name_data[NAME_FIELD_MAX][NAME_LEN_MAX];
	//char full_name[NAME_LEN_MAX];
	//char family_name[NAME_LEN_MAX];
	//char first_name[NAME_LEN_MAX];
};

struct NODE {
	NODE* next[FIELD_MAX];	// 각 필드별 next와 prev에 위치한 노드
	NODE* prev[FIELD_MAX];	// 각 필드별 next와 prev에 위치한 노드
	RECORD* record;
};

NODE HashTable[HASH_MAX];

unsigned long getHashCode(const char* input)
{
	unsigned long hash = 5381;
	int c;
	// 33진법으로 변환
	while (c = *input++) { hash = ((hash << 5) + hash) + c; }
	return hash % HASH_MAX;
}

unsigned long getHashCode(int input)
{
	return (input % HASH_MAX);
}

RECORD Record[MAX_N];
int RCnt;

NODE Node[MAX_N];
int NCnt;

void InitDB()
{
	// 새로운 TC 시작 전 메모리 해제 & 재할당 대신 Record, Node 카운터 0으로 초기화
	// 실제 메모리 해제 & 재할당보다 빠름
	RCnt = NCnt = 0;
	for (int i = 0; i < HASH_MAX; ++i)	
		for (int k = 0; k < FIELD_MAX; ++k) {
			// 필드값을 널포인터로 초기화
			HashTable[i].next[k] = 0;
			HashTable[i].prev[k] = 0;
		}
}

RECORD* makeNewRecord(int emp_no, char name[16], int cl, int phone, int birth) {
	RECORD* newRecord = &Record[RCnt++];
	newRecord->num_data[0] = emp_no / 1000000 + 1900;
	if (newRecord->num_data[0] < 1990) { newRecord->num_data[0] += 100; }
	newRecord->num_data[1] = emp_no;
	newRecord->num_data[2] = cl;
	newRecord->num_data[3] = phone;
	newRecord->num_data[4] = phone / 10000;
	newRecord->num_data[5] = phone % 10000;
	newRecord->num_data[6] = birth;
	newRecord->num_data[7] = birth / 10000;
	newRecord->num_data[8] = birth / 100 % 100;
	newRecord->num_data[9] = birth % 100;
	int i = 0;
	while (name[i] != ' ') {
		newRecord->name_data[0][i] = name[i];
		newRecord->name_data[1][i] = name[i];
		i++;
	}
	newRecord->name_data[0][i] = ' ';
	newRecord->name_data[1][i] = 0;
	i++;
	int family_i = 0;
	while (name[i]) {
		newRecord->name_data[0][i] = name[i];
		newRecord->name_data[2][family_i] = name[i];
		i++; family_i++;
	}
	newRecord->name_data[0][i] = 0;
	newRecord->name_data[2][family_i] = 0;
	
	return newRecord;
}

void ADD(char *option1, char *option2, char *option3, int emp_no, char name[16], int cl, int phone, int birth) {
	RECORD* newRecord = makeNewRecord(emp_no, name, cl, phone, birth);
	NODE* newNode = &Node[NCnt++];
	newNode->record = newRecord;
	for (int field_idx = 0; field_idx < FIELD_MAX; field_idx++) {
		int hkey;
		if (field_idx < NUM_FIELD_MAX) { // 숫자 데이터
			hkey = getHashCode(newNode->record->num_data[field_idx]);
		}
		else { // 문자열 데이터
			hkey = getHashCode(newNode->record->name_data[field_idx - NUM_FIELD_MAX]);
		}
		// HashTable[hkey]는 더미노드, 실질적 첫 노드는 그 다음 노드
		NODE* firstNode = HashTable[hkey].next[field_idx];
		// 더미가 아닌 실질적 첫 노드(더미의 next)를 newNode의 next로 지정
		// 맨 앞 더미노드(HashTable[hkey])를 newNode의 prev로 지정
		newNode->next[field_idx] = firstNode;
		newNode->prev[field_idx] = &HashTable[hkey];
		// 맨 앞 더미노드의 next인 head가 존재한다면 (0이 아니라면, 즉 널이 아니라면)
		// head의 prev를 새로운 노드로 지정
		if (firstNode != 0) { firstNode->prev[field_idx] = newNode; }
		// 맨앞 더미노드의 next를 새로운 노드로 지정
		HashTable[hkey].next[field_idx] = newNode;
	}
}
void DEL(char *option1, char *option2, char *option3, char *condition, char *value, FILE* wf) {
	bool print = !(mstrcmp(option1, "-p"));
	int ret_num = 0;
	RECORD* ret[RET_MAX];

	int field_idx, hkey;
	int value_int;

	// 문자열 value에 대한 hkey값 연산
	if (!mstrcmp(condition, "name")) {
		field_idx = 10;
		hkey = getHashCode(value);
	}
	// 숫자 value에 대한 hkey값 연산
	else {
		if (!mstrcmp(condition, "employeeNum")) {
			field_idx = 1;
			value_int = atoi(value);
		}
		else if (!mstrcmp(condition, "cl")) {
			field_idx = 2;
			value_int = (value[2]) - '0';
		}
		else if (!mstrcmp(condition, "phoneNum")) {
			field_idx = 3;
			value_int = atoiphone(value);
		}
		else {	// else if (mstrcmp(condition, "birthday")) {
			field_idx = 6;
			value_int = atoi(value);
		}
		hkey = getHashCode(value_int);
	}
	NODE* node = HashTable[hkey].next[field_idx];
	while (node) {
		NODE* next = node->next[field_idx];
		// 삭제할 노드 발견
		if ((field_idx < NUM_FIELD_MAX && node->record->num_data[field_idx] == value_int) ||
			(field_idx >= NUM_FIELD_MAX && !mstrcmp(node->record->name_data[field_idx - NUM_FIELD_MAX], value))) {
			if (print) {
				// 입사년도 순으로 삽입정렬
				ret[ret_num] = node->record;
				int tmp_idx = ret_num;
				while (tmp_idx > 0 && ret[tmp_idx - 1]->num_data[0] > ret[tmp_idx]->num_data[0]) {
					RECORD* tmp = ret[tmp_idx - 1];
					ret[tmp_idx - 1] = ret[tmp_idx];
					ret[tmp_idx] = tmp;
					tmp_idx--;
				}
			}
			// 삭제할 노드의 모든 필드에 대해 노드 앞뒤(prev, next) 포인터값 조정
			for (int field_idx = 0; field_idx < FIELD_MAX; ++field_idx) {
				if (node->prev[field_idx] != 0) node->prev[field_idx]->next[field_idx] = node->next[field_idx];
				if (node->next[field_idx] != 0) node->next[field_idx]->prev[field_idx] = node->prev[field_idx];
			}
			ret_num++;
			if (print && ret_num == RET_MAX) { break; }
		}
		node = next;
	}
	// 삭제될 레코드 없음
	if (ret_num == 0) {
		//printf("DEL,NONE\n");
		fprintf(wf, "DEL,NONE\n");
	}
	// 삭제될 레코드 있음
	else {
		// p옵션 활성화, 삭제된 레코드 내용 출력
		if (print) {
			for (int i = 0; i < ret_num; i++) {
				int zero_num_before_emp_no = 0;
				if (ret[i]->num_data[1] < 10000000) {
					// 사원번호가 0으로 시작되서 int 형변환 과정에서 앞의 0들 날아간 것 복구
					int emp_no_tmp = ret[i]->num_data[1];
					while (emp_no_tmp < 10000000) {
						emp_no_tmp *= 10;
						zero_num_before_emp_no++;
					}
				}
				//printf("DEL,");
				fprintf(wf, "DEL,");
				for (int i = 0; i < zero_num_before_emp_no; i++) {
					//printf("0");
					fprintf(wf, "0");
				}
				/*printf("%d,%s,CL%d,010-%d-%d,%d\n",
					ret[i]->num_data[1], ret[i]->name_data[0],
					ret[i]->num_data[2], ret[i]->num_data[4],
					ret[i]->num_data[5], ret[i]->num_data[6]);*/
				fprintf(wf, "%d,%s,CL%d,010-%d-%d,%d\n",
					ret[i]->num_data[1], ret[i]->name_data[0],
					ret[i]->num_data[2], ret[i]->num_data[4],
					ret[i]->num_data[5], ret[i]->num_data[6]);
			}
		}
		// p옵션 비활성화, 삭제된 레코드 개수만 출력
		else {
			//printf("DEL,%d\n", ret_num);
			fprintf(wf, "DEL,%d\n", ret_num);
		}
	}
}
void MOD(char *option1, char *option2, char *option3, char *condition, char *value, char *changeColumn, char *chaneValue) {

}
void SCH(char *option1, char *option2, char *option3, char *condition, char *value) {

}