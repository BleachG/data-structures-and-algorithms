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
{//LL�͵���,��������
	AVLtree p = T->lchild;//�ҵ���ƽ��������p
	T->lchild = p->rchild;
	p->rchild = T;
	return p;
}
AVLtree RR(AVLtree& T)
{//RR�͵�����������
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
	//����������ƽ������
	int bf = blance(T);
	if (bf > 1 && val < T->lchild->data)
	{
		//LL�͵���
		return LL(T);
	}
	if (bf > 1 && val > T->lchild->data)
	{
		//LR�͵������⿴T������ΪRR�ͣ�RR�͵�����T��ת��ΪLL��
		T->lchild = RR(T->lchild);
		return LL(T);
	}
	if (bf<-1 && val>T->rchild->data)
	{
		//RR�͵���
		return RR(T);
	}
	if (bf <-1 && val < T->rchild->data)
	{
		//RL�͵������⿴�Һ���ΪLL�ͣ�LL������T����ΪRR��
		T->rchild = LL(T->rchild);
		return RR(T);
	}
	return T;
}
AVLtree find(AVLtree T, int val)
{//����ָ��ֵ
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
{//������������ɾ��
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
		cout << "δ�ҵ��ý��" << endl;
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
{//Ѱ��ĳ����ֱ�Ӻ��
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
	{//�����Һ��Ӷ����ڣ�
		AVLtree p = findback(T->rchild);//�ҵ���ɾ�����ֱ�Ӻ��
		T->data = p->data;//�Ѵ�ɾ�����ֵ��Ϊ��̵�ֵ
		T->rchild = Delete( T->rchild, p->data);//�Ѻ�̽��ɾ�����ƶ���̽������ͨ���ݹ�����else���
	}
	else
	{//���ֻ��һ������
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
	{//ɾ������е���
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
