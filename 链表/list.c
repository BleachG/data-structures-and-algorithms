#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "list.h"
void Slistnodeprint(Slistnode* phead)
{
	Slistnode* cur = phead->next;
	while (cur!= NULL)
	{
		printf("%d\n", cur->data);
		cur = cur->next;
	}
}
void Slistnodecreat(Slistnode* phead)
{    
	
	phead->next = NULL;
	int n = 0;
	printf("输入单链表的值\n");
	scanf("%d", &n);
	while (n)
	{
		Slistnode* p = (Slistnode*)malloc(sizeof(Slistnode));
		p->data = n;
		p->next = phead->next;
		phead->next = p;
		printf("输入单链表的值\n");
		scanf("%d", &n);
	}
}
void Slistback(Slistnode* phead)
{
	Slistnode*r= (Slistnode*)malloc(sizeof(Slistnode));
	phead->next = NULL;
	r = phead;
	int n = 0;
	printf("输入单链表的值\n");
	scanf("%d", &n);
	while (n)
	{
		Slistnode* p = (Slistnode*)malloc(sizeof(Slistnode));
		p->data = n;
		p->next = NULL;
		r->next = p;
		r = p;
		printf("输入单链表的值\n");
		scanf("%d", &n);

	}
	
}
int find1(Slistnode* phead, int k)
{
	Slistnode* p = (Slistnode*)malloc(sizeof(Slistnode));
	Slistnode* q = (Slistnode*)malloc(sizeof(Slistnode));
	p= q = phead->next;
	int i = 0;
	while (p != NULL)
	{
		if (i < k)
		{
			i++;
		}
		else
			q = q->next;
		p = p->next;
	}
	if (i < k)
	{
		return 0;
	}
	else
	{
		printf("%d\n", q->data);
		return 1;
	}

}
void find(Slistnode* phead, int m)
{
	Slistnode* p = phead;
	int i = 0;
	while ( i< m)
	{
		p = p->next;
		i++;
	}
	if (p != NULL)
	{
		printf("该元素的值为%d\n", p->data);
	}
	else
		printf("该元素不存在\n");
}
void insert(Slistnode* phead, int i, int m)
{
	Slistnode*p = phead;
	Slistnode* s = (Slistnode*)malloc(sizeof(Slistnode)); 
	int j = 0;
	while (p && j<i-1)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)
	{
		printf("错误\n");
	}
	s->data = m;
	s->next = p->next;
	p->next = s;
}
void omit(Slistnode* phead, int i)
{
	Slistnode* p = phead;
	int j = 0;
	while (p->next && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)
	{
		printf("错误\n");
	}
	Slistnode*q = p->next;
	p->next = p->next->next;
	free(q);	
}

void combine( Slistnode* pa, Slistnode* pb)
{
	Slistnode* phead = (Slistnode*)malloc(sizeof(Slistnode));
	Slistnode* ptail = (Slistnode*)malloc(sizeof(Slistnode));
	phead = NULL;
	phead = ptail;
	Slistnode* a = (Slistnode*)malloc(sizeof(Slistnode));
	Slistnode* b = (Slistnode*)malloc(sizeof(Slistnode));
	a = pa->next;
	b = pb->next;
	
	while (a&& b)
	{
		if (a->data <= b->data)
		{
			ptail->next = b;
			ptail = b;
			b = b->next;
		}
		else
		{
			ptail->next = a;
			ptail = a;
			a =a->next;
		}
	}
	if (a)
	{
		ptail->next=a;
	}
	if (b)
	{
		ptail->next = b;
	}
	Slistnodeprint(phead);
}
void reverlist(Slistnode* head)
{
	Slistnode* n1 = (Slistnode*)malloc(sizeof(Slistnode));
	Slistnode* n2 = (Slistnode*)malloc(sizeof(Slistnode));
	Slistnode* n3 = (Slistnode*)malloc(sizeof(Slistnode));
	n1 = NULL;
	n2 = head->next;
	n3 = n2->next;
	while (n2)
	{   //翻转
		n2->next = n1;
		//迭代
		n1 = n2;
		n2 = n3;
		if (n3)
		n3 = n3->next;
	}
	Slistnodeprint(n1);
}
void split(Slistnode* phead)
{
	Slistnode* pa = (Slistnode*)malloc(sizeof(Slistnode));
	Slistnode* pb = (Slistnode*)malloc(sizeof(Slistnode));
	Slistnode* la = (Slistnode*)malloc(sizeof(Slistnode));
	Slistnode* lb = (Slistnode*)malloc(sizeof(Slistnode));
	Slistnode* p = (Slistnode*)malloc(sizeof(Slistnode));
	pa = la;
	pb = lb;
	p = phead->next;
	while (p != NULL)
	{
		if (p->data < 0)
		{
			pa->next = p;
			p = p->next;
			pa = pa->next;
			pa->next = NULL;
		}
		else
		{
			pb->next = p;
			p = p->next;
			pb = pb->next;
			pb->next = NULL;
		}
	}
	printf("小于0的为");
	Slistnodeprint(la);
	printf("大于0的为");
	Slistnodeprint(lb);

}