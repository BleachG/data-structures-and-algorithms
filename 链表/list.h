#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef int SLTDataType;

typedef struct Slist
{
	SLTDataType data;
	struct Slist* next;
}Slistnode;
void Slistnodeprint(Slistnode* phead);
void Slistnodecreat(Slistnode* phead);//ǰ�巨
void Slistback(Slistnode* phead);//��巨
void find(Slistnode* head, int m);//���ҵ�m������
void insert(Slistnode* phead, int i, int m);//�ڵ�i��λ�ò���Ϊm��ֵ
void omit(Slistnode* phead, int i);//ɾ����i��������
void combine( Slistnode* pa, Slistnode* pb);//��a���b��ϳ�p��
void reverlist(Slistnode* head);//��ת����
void split(Slistnode* phead);//�ָ�����
int find1(Slistnode* ptail, int k);//���ҵ�����k��


