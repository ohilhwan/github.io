#include <stdio.h>
#include <malloc.h>
typedef struct data {
	int x;
	int y;
}Data;
int main() {
	char buf1[10];
	char buf2[10];
	printf("buf1 : %d, buf2 : %d\n", buf1, buf2);
	buf2[20] = 100;
	printf("%d\n", buf1[0]);
	/*
	int x = 20;
	int y;
	int * p = &y;
	*(p + 3) = 100;
	printf("xaddr : %d, yaddr : %d\n", &x, &y);
	printf("x : %d", x);
	/*
	int size = 10;
//	int buf[size];
	int * buf1 = (int*)malloc(size*sizeof(int));
	int buf2[10];

	int * buf3 = new int[size];

//	*(buf1+10) = 100;
	printf("buf1[10] : %d\n", buf1[10]);
	printf("size1 : %d, size2 : %d\n", sizeof(buf1), sizeof(buf2));
	free(buf1);
	delete(buf3);
//	delete buf3;
	/*
	buf2[10] = 100;
	printf("buf2[10] : %d\n", buf2[10]);
	*/
#if 0
	Data d = {10,20};
	printf("x : %d\n", d.x);
	Data * pd = &d;
	printf("x : %d\n", (*pd).x);
	printf("x : %d\n", pd->x);
#endif
#if 0
	char name1[100] = "hong";
	const char * name2 = "hong";
	char * name3 = name1;
#endif
#if 0
	int x = 100;
	int y = 200;
	int * const p1 = &x;
	const int *  p2 = &x;
	const int * const p3 = &x;
	//p1 = &y;
	//*p2 = 200;
	*p1 = 300;
#endif
#if 0
	int ** pp = &p;
	printf("x : %d\n", x);
	printf("x : %d\n", *p);
	printf("x : %d\n", **pp);
#endif
	return 0;
}
