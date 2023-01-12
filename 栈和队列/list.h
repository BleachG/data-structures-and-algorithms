#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define maxsize 9
typedef struct
{
	int top;
	int base;
	int data[maxsize];
}stack;//创建栈
typedef struct
{
	int front;
	int rear;
	int *base;
}queue;//创建队列
typedef struct stacknode
{
	int data;
	struct stacknode* next;
}stacknode;//创建链栈
void initstack(stack* s);//初始化栈
void push(stack* s,int m);//入栈
void pop(stack* s);//出栈
void printstack(stack* s);//打印栈中元素
void creatstack(stack* s);//创建
void initqueue(queue* s);//初始化队列
void creatqueue(queue* s);//创建队列
void printqueue(queue* s);//打印队列
void enqueue(queue* s);//入队
void dequeue(queue* l);//出队
void initstacknode(stacknode* s);//初始化链栈
void creatstacknode(stacknode* s);//创建链栈
void printstacknode(stacknode* s);//打印链栈的值
void pushstacknode(stacknode* s);//链栈的入栈
void popstacknode(stacknode* s);//链栈的出栈












