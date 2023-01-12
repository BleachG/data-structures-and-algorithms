#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "list.h"
void initstack(stack*s)
{
	s->top = -1;
	s->base = s->top=-1;
	printf("栈建立成功\n");
}
void creatstack(stack*s)
{
	int n = 0;
	printf("请输入栈的值\n");
	scanf("%d", &n);
	while (n&&s->top<maxsize)
	{
		s->data[s->top] = n;
		s->top++;
		printf("请输入栈的值\n");
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
		printf("栈满\n");
	}
	s->data[s->top] = m;
	s->top++;
}
void pop(stack* s)
{
	if (s->top == s->base )
	{
		printf("栈空\n");
	}
	s->top--;
	printf("出栈元素值为%d\n", s->data[s->top]);
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
	printf("请输入队列的值\n");
	scanf("%d", &n);
	while (n)
	{
		s->base[s->rear] = n;
		s->rear = (s->rear + 1) % maxsize;
		if ((s->rear+1)%maxsize!=s->front)
		{printf("请输入队列的值\n");
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
		printf("队满\n");
	}
	int n = 0;
	printf("请输入入队的值\n");
	scanf("%d", &n);
	s->base[s->rear] = n;
	s->rear = (s->rear + 1) % maxsize;
	printqueue(s);
}
void dequeue(queue* s)
{
	if (s->front == s->rear)
	{
		printf("队空\n");
	}
	s->front = (s->front + 1) % maxsize;
	printf("出队后队列为\n");
	printqueue(s);
}
void initstacknode(stacknode*s)
{
	s = NULL;//把链栈置空初始化
}
void creatstacknode(stacknode* s)
{
	int n = 0;
	s->next = NULL;
	printf("请输入链栈的值\n");
	scanf("%d", &n);
	while (n)
	{   stacknode* p = (stacknode*)malloc(sizeof(stack));//创建新结点接收值
		p->data = n;//把值赋给p
	    //把结点插入s后
		p->next = s->next;
		s->next=p;
		printf("请输入链栈的值\n");
		scanf("%d", &n);
	}

}
void printstacknode(stacknode* s)
{
	stacknode* p = (stacknode*)malloc(sizeof(stack));//创建新结点接收值
	p = s->next;
	if (p == NULL)
	{
		printf("链栈空\n");
	}
	while (p!=NULL)
	{
		printf("%d\n", p->data);
		p = p->next;//栈顶指针后移
	}
}
void pushstacknode(stacknode* s)
{
	int n = 0;
	stacknode* p = (stacknode*)malloc(sizeof(stack));//创建新结点接收值
	printf("请输入链栈入栈的值\n");
	scanf("%d", &n);
	p->data = n;//把n的值给p的数据域
	p->next = s->next;//把p插入栈顶
	s->next= p;//修改栈顶指针
	printstacknode(s);
}
void popstacknode(stacknode* s)
{
	int n = 0;
	stacknode* p = (stacknode*)malloc(sizeof(stack));//创建新结点接收值
	if (s->next== NULL)
	{
		printf("链栈空\n");
	}
	p = s->next;//把s的下一个结点给p
	s->next = p->next;//让s指向p的下一个结点
	free(p);//释放p的内存
	printstacknode(s);
}