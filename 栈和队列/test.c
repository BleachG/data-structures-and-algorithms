#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "list.h"
int main()
{
	int a = 0;
	stacknode* l = (stacknode*)malloc(sizeof(stacknode));
	initstacknode(l);
	creatstacknode(l);
	popstacknode(l);
	printf("¸ßÓÐµä211050100305\n");
	return 0;
}
