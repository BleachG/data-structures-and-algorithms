#include <iostream>
using namespace std;
typedef struct AVLnode
{
	struct AVLnode* rchild;
	struct AVLnode* lchild;
	struct AVLnode* parent;
	int data;
}AVLnode, * AVLtree; 
int depth(AVLtree T)
{
	if (T == NULL)
	{
		return 1;
	}
	else
	{
		int m = depth(T->lchild);
		int n = depth(T->rchild);
		return m >n ? (m + 1) : (n + 1);
	}
}
int blance(AVLtree T)
{
	if (T ==NULL)
	{
		return 0;
	}
	else
	{
		return depth(T->lchild) - depth(T->rchild);
	}
}
void mid(AVLtree T)
{
	if (T)
	{
		mid(T->lchild);
		cout << T->data << " ";
		mid(T->rchild);
	}
}
void pre(AVLtree T)
{
	if (T)
	{
		cout << T->data << " ";
		pre(T->lchild);
		pre(T->rchild);
	}
}
AVLtree LL(AVLtree& T)
{//LL型调整,左子树高
	AVLtree p = T->lchild;//找到不平衡结点左孩子p
	T->lchild = p->rchild;
	p->rchild = T;
	return p;
}
AVLtree RR(AVLtree& T)
{//RR型调整右子树高
	AVLtree p = T->rchild;
	T->rchild = p->lchild;
	p->lchild = T;
	return p;
}
AVLtree AVLinsert(AVLtree&T,int val)
{
	if (T == NULL)
	{
		T = new AVLnode;
		T->lchild = NULL;
		T->rchild = NULL;
		T->data = val;
		return T;
	}
	else if (val < T->data)
	{
		T->lchild = AVLinsert(T->lchild, val);
	}
	else if (val > T->data)
	{
		T->rchild = AVLinsert(T->rchild, val);
	}
	else
	{
		return T;
	}
	//计算插入结点的平衡因子
	int bf = blance(T);
	if (bf > 1 && val < T->lchild->data)
	{
		//LL型调整
		return LL(T);
	}
	if (bf > 1 && val > T->lchild->data)
	{
		//LR型调整，光看T的左孩子为RR型，RR型调整把T其转换为LL型
		T->lchild = RR(T->lchild);
		return LL(T);
	}
	if (bf<-1 && val>T->rchild->data)
	{
		//RR型调整
		return RR(T);
	}
	if (bf <-1 && val < T->rchild->data)
	{
		//RL型调整，光看右孩子为LL型，LL调整把T调整为RR型
		T->rchild = LL(T->rchild);
		return RR(T);
	}
	return T;
}
AVLtree find(AVLtree T, int val)
{//搜索指定值
	if (!T || T->data == val)
	{
		return T;
	}
	else if (val < T->data)
	{
		return find(T->lchild, val);
	}
	else if (val > T->data)
	{
		return find(T->rchild, val);
	}
}
void omit(AVLtree&T,int val)
{//二叉搜索树的删除
	AVLtree p = T;
	AVLtree f = NULL;
	while (p)
	{
		if (p->data == val)
		{
			break;
		}
		f = p;
	     if (p->data < val)
		{
			 p = p->rchild;
		}
		 else
		 {
			 p = p->lchild;
		 }
	}
	if (!p)
	{
		cout << "未找到该结点" << endl;
		return;
	}
	AVLtree q = new AVLnode;
	q = p;
	if (p->lchild && p->rchild)
	{
		AVLtree s = new AVLnode;
		 s = p->lchild;
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		p ->data = s->data;
		if (q != p)
		{
			q->rchild = s->lchild;
		}
		else
		{
			q->lchild = s->lchild;
		}
		delete s;
		return;
	}
	else if (!p->rchild)
	{
		p = p->lchild;
	}
	else if (!p->lchild)
	{
		p = p->rchild;
	}
	if (!f)
	{
		T = p;
	}
	else if (q == f->lchild)
	{
		f->lchild = p;
	}
	else
	{
		f->rchild = p;
	}
	delete q;
}
AVLtree findback(AVLtree p)
{//寻找某结点的直接后继
	if (p == NULL)
	{
		return p;
	}
	if (p->lchild == NULL)
	{
		return p;
	}
	else
	{
		return findback(p->lchild);
	}
}
AVLtree adjust(AVLtree& T)
{
	if (depth(T->lchild) - depth(T->rchild) >= 2)
	{
		if (depth(T->lchild->lchild) > depth(T->lchild->rchild))
		{
			/*T->lchild = LL(T->lchild);*/
			T = LL(T);
		}
		else if (depth(T->lchild->lchild) < depth(T->lchild->rchild))
		{
			T->lchild = RR(T->lchild);
			T= LL(T);
		}
	}
	else if (depth(T->rchild) - depth(T->lchild) >= 2)
	{
		if (depth(T->rchild->rchild) > depth(T->rchild->lchild))
		{
			/*T->rchild = RR(T->rchild);*/
			T = RR(T);
		}
		else if (depth(T->rchild->rchild)<depth(T->rchild->lchild))
		{
			T->rchild = LL(T->rchild);
			T= RR(T);
		}
	}
	return T;
}
AVLtree Delete(AVLtree& T, int val)
{
	if (T == NULL)
	{
		return T;
	}
	else if (val < T->data)
	{
		T->lchild = Delete(T->lchild, val);
	}
	else if (val>T->data)
	{
		T->rchild = Delete(T->rchild, val);
	}
	else if (T->lchild && T->rchild)
	{//左孩子右孩子都存在，
		AVLtree p = findback(T->rchild);//找到待删除结点直接后继
		T->data = p->data;//把待删除结点值变为后继的值
		T->rchild = Delete( T->rchild, p->data);//把后继结点删除并移动后继结点子树通过递归下面else语句
	}
	else
	{//结点只有一个孩子
		AVLtree p = T;
		if (T->rchild == NULL)
		{
			T = T->lchild;
		}
		else if (T->lchild == NULL)
		{
			T = T->rchild;
		}
		delete(p);
	}
	if (T)
	{//删除后进行调整
		T = adjust(T);
	}
	return T;
}
int main()
{
	AVLtree T = NULL;
	/*T = AVLinsert(T, 40) ;
	T = AVLinsert(T, 20);
	T = AVLinsert(T, 30);
	T = AVLinsert(T, 10);
	T = AVLinsert(T, 25);	
	T = AVLinsert(T, 50);*/
	T = AVLinsert(T, 100);
	T = AVLinsert(T, 80);
	T = AVLinsert(T, 110);
	T = AVLinsert(T, 70);
	T = AVLinsert(T, 90);
	T = AVLinsert(T, 50);
	T = AVLinsert(T, 30);
	T = AVLinsert(T, 20);
	T = AVLinsert(T, 85);

	Delete(T, 50);
	pre(T);
	cout << endl;
	mid(T);
	return 0;
}
