#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "list.h"

int main()
{
	int k = 0;
	printf("请输入查找倒数第几个\n");
	scanf("%d", &k);
	Slistnode* l = (Slistnode*)malloc(sizeof(Slistnode));
	Slistback(l);
	find1(l, k);
	printf("高有典\n");
	printf("211050100305\n");
	return 0;
}