#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "list.h"
void initstack(stack*s)
{
	s->top = -1;
	s->base = s->top=-1;
	printf("ջ�����ɹ�\n");
}
void creatstack(stack*s)
{
	int n = 0;
	printf("������ջ��ֵ\n");
	scanf("%d", &n);
	while (n&&s->top<maxsize)
	{
		s->data[s->top] = n;
		s->top++;
		printf("������ջ��ֵ\n");
		scanf("%d", &n);
	}
}
void printstack(stack*s)
{
	int i = 0;
	for (i = s->top-1; i >=-1; i--)
	{
		printf("%d\n", s->data[i]);
	}
}
void push(stack* s,int m)
{
	
	if (s->top - s->base == maxsize)
	{
		printf("ջ��\n");
	}
	s->data[s->top] = m;
	s->top++;
}
void pop(stack* s)
{
	if (s->top == s->base )
	{
		printf("ջ��\n");
	}
	s->top--;
	printf("��ջԪ��ֵΪ%d\n", s->data[s->top]);
	printstack(s);
}

void initqueue(queue* s)
{
	s->base = (int*)malloc(maxsize*sizeof(int));
	s->front = s->rear = 0;
}
void creatqueue(queue* s)
{
	int n = 0;
	printf("��������е�ֵ\n");
	scanf("%d", &n);
	while (n)
	{
		s->base[s->rear] = n;
		s->rear = (s->rear + 1) % maxsize;
		if ((s->rear+1)%maxsize!=s->front)
		{printf("��������е�ֵ\n");
		scanf("%d", &n); }
	}
}
void printqueue(queue* s)
{
	while (s->rear != s->front)
	{
		printf("%d\n", s->base[s->front]);
		s->front = (s->front + 1) % maxsize;
	}
}
void enqueue(queue* s)
{
	if ((s->rear + 1) % maxsize == s->front)
	{
		printf("����\n");
	}
	int n = 0;
	printf("��������ӵ�ֵ\n");
	scanf("%d", &n);
	s->base[s->rear] = n;
	s->rear = (s->rear + 1) % maxsize;
	printqueue(s);
}
void dequeue(queue* s)
{
	if (s->front == s->rear)
	{
		printf("�ӿ�\n");
	}
	s->front = (s->front + 1) % maxsize;
	printf("���Ӻ����Ϊ\n");
	printqueue(s);
}
void initstacknode(stacknode*s)
{
	s = NULL;//����ջ�ÿճ�ʼ��
}
void creatstacknode(stacknode* s)
{
	int n = 0;
	s->next = NULL;
	printf("��������ջ��ֵ\n");
	scanf("%d", &n);
	while (n)
	{   stacknode* p = (stacknode*)malloc(sizeof(stack));//�����½�����ֵ
		p->data = n;//��ֵ����p
	    //�ѽ�����s��
		p->next = s->next;
		s->next=p;
		printf("��������ջ��ֵ\n");
		scanf("%d", &n);
	}

}
void printstacknode(stacknode* s)
{
	stacknode* p = (stacknode*)malloc(sizeof(stack));//�����½�����ֵ
	p = s->next;
	if (p == NULL)
	{
		printf("��ջ��\n");
	}
	while (p!=NULL)
	{
		printf("%d\n", p->data);
		p = p->next;//ջ��ָ�����
	}
}
void pushstacknode(stacknode* s)
{
	int n = 0;
	stacknode* p = (stacknode*)malloc(sizeof(stack));//�����½�����ֵ
	printf("��������ջ��ջ��ֵ\n");
	scanf("%d", &n);
	p->data = n;//��n��ֵ��p��������
	p->next = s->next;//��p����ջ��
	s->next= p;//�޸�ջ��ָ��
	printstacknode(s);
}
void popstacknode(stacknode* s)
{
	int n = 0;
	stacknode* p = (stacknode*)malloc(sizeof(stack));//�����½�����ֵ
	if (s->next== NULL)
	{
		printf("��ջ��\n");
	}
	p = s->next;//��s����һ������p
	s->next = p->next;//��sָ��p����һ�����
	free(p);//�ͷ�p���ڴ�
	printstacknode(s);
}