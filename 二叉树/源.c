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
 {//创建菜单
	 printf("**********************************************\n");
	 printf("**************    1.先序遍历     *************\n");
	 printf("**************    2.中序遍历     *************\n");
	 printf("**************    3.后序遍历     *************\n");
	 printf("**************   4.创建二叉树    *************\n");
	 printf("**************      0.exit       *************\n");
	 printf("**********************************************\n");
 }
 void preordertraverse(bitree T)
 {//先序遍历二叉树
	 if (T)//二叉树不为空
	 {
		 printf("%c", T->data);//访问根结点
		 preordertraverse(T->lchild);//先序遍历左子树
		 preordertraverse(T->rchild);//先序遍历右子树
	 }
 }
 void inordertraverse(bitree T)
 {//中序遍历二叉树
	 if (T)//二叉树不为空
	 {
		 inordertraverse(T->lchild);//中序遍历左子树
		 printf("%c", T->data);//访问根结点
		 inordertraverse(T->rchild);//中遍历右子树
	 }

 }void backordertraverse(bitree T)
 {//后序遍历二叉树
	 if (T)//二叉树不为空
	 {
		 backordertraverse(T->lchild);//后序遍历左子树
		 backordertraverse(T->rchild);//后序遍历右子树
		 printf("%c", T->data);//访问根结点
	 }

 }
 void creatbitnode(bitree *T)
 {//创建二叉树
	 char ch = '0';
	 scanf("%c",&ch);//输入一个字符
		 if (ch == '#')
		 {
			 *T = NULL;//字符等于#将该结点置空
		 }
		 else
		 {
			 *T = (bitree)malloc(sizeof(BiTnode));//申请一个新结点
			 (*T)->data = ch;//把输入字符赋给树的数据域
			 creatbitnode(&((*T)->lchild));//递归创建左孩子
			 creatbitnode(&((*T)->rchild));//递归创建右孩子
		 }
 }
int main()
{
	menu();
	int a = -1;
	bitree* p;//创建一个新结点
	p = NULL;//把该结点置空
	while (a!=0)
	{
		printf("请选择要进行的操作\n");
		scanf("%d", &a);
		getchar();//吞掉回车符
		switch (a)
		{
		case 1:
			printf("二叉树的先序序列为:");
			preordertraverse(p);
			break;
		case 2:
			printf("二叉树的中序序列为:");
			inordertraverse(p);
			break;
		case 3:
			printf("二叉树的后序序列为:");
			backordertraverse(p);
			break;
		case 4:
			printf("请输入先序建立二叉树的序列:");
			creatbitnode(&p);
			break;
		default:
			printf("选择错误请重新选择\n");
			break;
		}
		printf("高有典211050100305\n");
	}
	return 0;
}
 