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
void Slistnodecreat(Slistnode* phead);//前插法
void Slistback(Slistnode* phead);//后插法
void find(Slistnode* head, int m);//查找第m个数据
void insert(Slistnode* phead, int i, int m);//在第i个位置插入为m的值
void omit(Slistnode* phead, int i);//删除第i个链表结点
void combine( Slistnode* pa, Slistnode* pb);//把a表和b表合成p表
void reverlist(Slistnode* head);//翻转链表
void split(Slistnode* phead);//分割链表
int find1(Slistnode* ptail, int k);//查找倒数第k个


