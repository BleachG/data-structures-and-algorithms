#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define maxsize 9
typedef struct
{
	int top;
	int base;
	int data[maxsize];
}stack;//����ջ
typedef struct
{
	int front;
	int rear;
	int *base;
}queue;//��������
typedef struct stacknode
{
	int data;
	struct stacknode* next;
}stacknode;//������ջ
void initstack(stack* s);//��ʼ��ջ
void push(stack* s,int m);//��ջ
void pop(stack* s);//��ջ
void printstack(stack* s);//��ӡջ��Ԫ��
void creatstack(stack* s);//����
void initqueue(queue* s);//��ʼ������
void creatqueue(queue* s);//��������
void printqueue(queue* s);//��ӡ����
void enqueue(queue* s);//���
void dequeue(queue* l);//����
void initstacknode(stacknode* s);//��ʼ����ջ
void creatstacknode(stacknode* s);//������ջ
void printstacknode(stacknode* s);//��ӡ��ջ��ֵ
void pushstacknode(stacknode* s);//��ջ����ջ
void popstacknode(stacknode* s);//��ջ�ĳ�ջ












