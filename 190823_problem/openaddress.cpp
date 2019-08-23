#define MAX_N 50000
#define FIELD_MAX 5

#define HASH_MAX (50000 * 2 + 7)

struct DATABASE {
    int active;
    char str[FIELD_MAX][20];
};
DATABASE Db[MAX_N];
int DbCnt;

int HashTable[FIELD_MAX][HASH_MAX];

void mstrcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != 0) ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
	int c = 0;
	while (str1[c] != 0 && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

void InitDB()
{
    DbCnt = 0;
    for (int i = 0; i < FIELD_MAX; ++i)
        for (int k = 0; k < HASH_MAX; ++k)
            HashTable[i][k] = -1;
}

int putHash(int dbidx, char* str, int field)
{
    int hkey = getHashCode(str);

    for (int i = 0; i < HASH_MAX; ++i) {
        if (HashTable[field][hkey] == -1
		    || HashTable[field][hkey] == MAX_N ) {            
            HashTable[field][hkey] = dbidx;
            return hkey;
        }

        hkey++;
        hkey %= HASH_MAX;
    }
    return -1;
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
    Db[DbCnt].active = 1;
    mstrcpy(Db[DbCnt].str[0], name);
    mstrcpy(Db[DbCnt].str[1], number);
    mstrcpy(Db[DbCnt].str[2], birthday);
    mstrcpy(Db[DbCnt].str[3], email);
    mstrcpy(Db[DbCnt].str[4], memo);

    for (int i = 0; i < FIELD_MAX; ++i)
        putHash(DbCnt, Db[DbCnt].str[i], i);
    DbCnt++;
}

int Delete(FIELD field, char* str)
{
    int ret = 0;
    int hkey = getHashCode(str);    
    
    for (int i = 0; i < HASH_MAX; ++i) {
        int dbidx = HashTable[field][hkey];
        if (dbidx == -1) break;

        if (dbidx != MAX_N && Db[dbidx].active == 1 &&
            !mstrcmp(str, Db[dbidx].str[field])) {
				
			HashTable[field][hkey] = MAX_N;

            Db[dbidx].active = 0;
            ret++;
        }
        hkey++;
        hkey %= HASH_MAX;
    }
    return ret;
}

int Change(FIELD field, char* str, FIELD chfield, char* dst)
{
    int ret = 0;
    int hkey = getHashCode(str);    
    
    for (int i = 0; i < HASH_MAX; ++i) {
        int dbidx = HashTable[field][hkey];
        if (dbidx == -1) break;

        if (dbidx != MAX_N && Db[dbidx].active == 1 && 
            !mstrcmp(str, Db[dbidx].str[field])) {
				
			HashTable[field][hkey] = MAX_N;

            mstrcpy(Db[dbidx].str[chfield], dst);
            putHash(dbidx, dst, chfield);            
            ret++;
        }
        hkey++;
        hkey %= HASH_MAX;
    }
    return ret;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
    RESULT result;
    result.count = 0;

    int hkey = getHashCode(str); 

    for (int i = 0; i < HASH_MAX; ++i) {
        int dbidx = HashTable[field][hkey];
        if (dbidx == -1) break;

        if (dbidx != MAX_N && Db[dbidx].active == 1 &&
            !mstrcmp(str, Db[dbidx].str[field])) {

            mstrcpy(result.str, Db[dbidx].str[ret_field]);
            result.count++;            
        }
        hkey++;
        hkey %= HASH_MAX;
    }

    return result;
}
