#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
 typedef struct BiTnode
{
	 char data;
	 struct BiTnode* lchild;
	 struct BiTnode* rchild;
}BiTnode,*bitree;
 
 void menu()
 {//�����˵�
	 printf("**********************************************\n");
	 printf("**************    1.�������     *************\n");
	 printf("**************    2.�������     *************\n");
	 printf("**************    3.�������     *************\n");
	 printf("**************   4.����������    *************\n");
	 printf("**************      0.exit       *************\n");
	 printf("**********************************************\n");
 }
 void preordertraverse(bitree T)
 {//�������������
	 if (T)//��������Ϊ��
	 {
		 printf("%c", T->data);//���ʸ����
		 preordertraverse(T->lchild);//�������������
		 preordertraverse(T->rchild);//�������������
	 }
 }
 void inordertraverse(bitree T)
 {//�������������
	 if (T)//��������Ϊ��
	 {
		 inordertraverse(T->lchild);//�������������
		 printf("%c", T->data);//���ʸ����
		 inordertraverse(T->rchild);//�б���������
	 }

 }void backordertraverse(bitree T)
 {//�������������
	 if (T)//��������Ϊ��
	 {
		 backordertraverse(T->lchild);//�������������
		 backordertraverse(T->rchild);//�������������
		 printf("%c", T->data);//���ʸ����
	 }

 }
 void creatbitnode(bitree *T)
 {//����������
	 char ch = '0';
	 scanf("%c",&ch);//����һ���ַ�
		 if (ch == '#')
		 {
			 *T = NULL;//�ַ�����#���ý���ÿ�
		 }
		 else
		 {
			 *T = (bitree)malloc(sizeof(BiTnode));//����һ���½��
			 (*T)->data = ch;//�������ַ���������������
			 creatbitnode(&((*T)->lchild));//�ݹ鴴������
			 creatbitnode(&((*T)->rchild));//�ݹ鴴���Һ���
		 }
 }
int main()
{
	menu();
	int a = -1;
	bitree* p;//����һ���½��
	p = NULL;//�Ѹý���ÿ�
	while (a!=0)
	{
		printf("��ѡ��Ҫ���еĲ���\n");
		scanf("%d", &a);
		getchar();//�̵��س���
		switch (a)
		{
		case 1:
			printf("����������������Ϊ:");
			preordertraverse(p);
			break;
		case 2:
			printf("����������������Ϊ:");
			inordertraverse(p);
			break;
		case 3:
			printf("�������ĺ�������Ϊ:");
			backordertraverse(p);
			break;
		case 4:
			printf("������������������������:");
			creatbitnode(&p);
			break;
		default:
			printf("ѡ�����������ѡ��\n");
			break;
		}
		printf("���е�211050100305\n");
	}
	return 0;
}
 