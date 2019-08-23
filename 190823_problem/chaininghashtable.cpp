
typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;

typedef struct
{
	int count;
	char str[20];
} RESULT;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define MAX_N 50000
#define FIELD_MAX 5

#define HASH_MAX (MAX_N * 2 + 7)

struct RECORD {
	char str[FIELD_MAX][20];
};

struct NODE {
	NODE* next[FIELD_MAX];
	NODE* prev[FIELD_MAX];
	RECORD* record;
};

NODE HashTable[HASH_MAX];

unsigned long getHashCode(const char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++) {
		hash = (((hash << 5) + hash) + c) % HASH_MAX;
	}

	return hash % HASH_MAX;
}

////////////////////////////////////////////////////////////////////////////////

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != 0) { dest[i] = src[i]; i++; }
	dest[i] = src[i];
}

int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != 0; i++) { if (a[i] != b[i]) return a[i] - b[i]; }
	return a[i] - b[i];
}

////////////////////////////////////////////////////////////////////////////////

RECORD Record[MAX_N];
int RCnt;

NODE Node[MAX_N];
int NCnt;

void meminit()
{
	RCnt = NCnt = 0;
}

RECORD* newRecord()
{
	RECORD* record = &Record[RCnt++];
	for (int i = 0; i < FIELD_MAX; ++i)
		record->str[i][0] = 0;
	return record;
}

NODE* newNode()
{
	NODE* node = &Node[NCnt++];
	for (int i = 0; i < FIELD_MAX; ++i) {
		node->next[i] = 0;
		node->prev[i] = 0;
	}
	node->record = 0;
	return node;
}

void deleteRecord(RECORD* record)
{
}

void deleteNode(NODE* node)
{
}

////////////////////////////////////////////////////////////////////////////////

void InitDB()
{
	meminit();

	for (int i = 0; i < HASH_MAX; ++i)
		for (int k = 0; k < FIELD_MAX; ++k) {
			HashTable[i].next[k] = 0;
			HashTable[i].prev[k] = 0;
		}
}

void addlinkedlist(NODE* node, int field)
{
	int hkey = getHashCode(node->record->str[field]);

	NODE* head = HashTable[hkey].next[field];
	
	node->next[field] = head;
	node->prev[field] = &HashTable[hkey];
	if (head != 0) head->prev[field] = node;	
	HashTable[hkey].next[field] = node;
}

void deletelinkedlist(NODE* node, int field)
{
	if (node->prev[field] != 0) node->prev[field]->next[field] = node->next[field];
	if (node->next[field] != 0) node->next[field]->prev[field] = node->prev[field];
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	RECORD* record = newRecord();
	mstrcpy(record->str[0], name);
	mstrcpy(record->str[1], number);
	mstrcpy(record->str[2], birthday);
	mstrcpy(record->str[3], email);
	mstrcpy(record->str[4], memo);

	NODE* node = newNode();
	node->record = record;

	for (int i = 0; i < FIELD_MAX; ++i) {
		addlinkedlist(node, i);
	}
}

int Delete(FIELD field, char* str)
{
	int ret = 0;
	int hkey = getHashCode(str);

	NODE* node = HashTable[hkey].next[field];
	while (node) {
		NODE* next = node->next[field];
		if (!mstrcmp(str, node->record->str[field])) {
			ret++;

			for (int i = 0; i < FIELD_MAX; ++i) {
				deletelinkedlist(node, i);
			}
			deleteRecord(node->record);
			deleteNode(node);
		}
		node = next;
	}
	return ret;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int ret = 0;
	int hkey = getHashCode(str);

	NODE* node = HashTable[hkey].next[field];
	while (node) {
		NODE* next = node->next[field];
		if (!mstrcmp(str, node->record->str[field])) {
			ret++;

			deletelinkedlist(node, changefield);

			mstrcpy(node->record->str[changefield], changestr);
			addlinkedlist(node, changefield);
		}
		node = next;
	}
	return ret;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
	RESULT result;
	result.count = 0;

	int hkey = getHashCode(str);
	NODE* node = HashTable[hkey].next[field];
	while (node) {
		NODE* next = node->next[field];
		if (!mstrcmp(str, node->record->str[field])) {
			result.count++;
			mstrcpy(result.str, node->record->str[ret_field]);
		}
		node = next;
	}

	return result;
}