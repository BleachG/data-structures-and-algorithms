#include <iostream>
#include <cstring>
#include <algorithm>
#define maxbit 100
#define maxvalue 10000
#define maxleaf 30
#define maxnode maxleaf*2-1
using namespace std;
typedef struct
{
	double w;//Ȩֵ
	int pa;//˫�׽ڵ�
	int lch;//���ӽ��
	int rch;//�Һ��ӽ��
	char val;//�ַ�
}HNodeType;//���ṹ��
typedef struct
{
	int bit[maxbit];
		int start;
}HCodeType;//����ṹ��
HNodeType HuffNode[maxnode];//������ṹ��
HCodeType HuffCode[maxleaf];//�������ṹ��
void HuffmanTree(HNodeType HuffNode[], int n)
{
	int x1 = 0; int x2=0;//��������2����СֵȨֵ��Ȩֵ���
	double m1, m2;//��������2����СֵȨֵ��Ȩֵ
	int i, j;//ѭ������
	for (i = 0; i < 2 * n - 1; i++)//�࿪n-1��������½��
	{//��ʼ��˫�ף����Һ��ӽ�㣬Ȩ��
		HuffNode[i].w = 0;
		HuffNode[i].pa = -1;
		HuffNode[i].lch= -1;
		HuffNode[i].rch = -1;
	}
	//����n��Ҷ�ӽ��Ȩֵ
	for (i = 0; i < n; i++)
	{
		cout << "������ֵ��Ȩ��" << i + 1 << endl;
		cin >> HuffNode[i].val >> HuffNode[i].w;
	}
	for (i = 0; i < n - 1; i++)
	{
		m1 = m2 = maxvalue;//��СȨ����Ĭ�����ֵ
		x1 = x2 = -1;//2����СȨֵֵ���Ϊ-1
		//����Сֵ�ʹ�Сֵ
		for (j = 0; j < n + i; j++)
		{
			if (HuffNode[j].w < m1 && HuffNode[j].pa == -1)
			{
				m2 = m1;
				x2 = x1;
				m1 = HuffNode[j].w;//����С���Ȩֵ��m1
				x1 = j;
			}

			else if (HuffNode[j].w < m2 && HuffNode[j].pa == -1)
				m2 = HuffNode[j].w;//����С���Ȩֵ��m2
			{
				x2 = j;
			}
		}
		//���ºϳɸ�����2���ӽڵ��˫�׽ڵ�
		HuffNode[x1].pa = n + i;
		HuffNode[x2].pa = n + i;
		HuffNode[n + i].w = m1 + m2;
		HuffNode[n + i].lch = x1;
		HuffNode[n + i].rch = x2;
	}
}
void HuffmanCode(HCodeType HuffCode[], int n)
{
	HCodeType cd;//������ʱ�����洢�����Ϣ
	int c, p, i, j;
	for (i = 0; i < n; i++)//����Ҷ�ӽ�㣬ͨ��Ҷ�ӽ�㵽���ڵ�����д������������
	{
		cd.start = n - 1;//�Ӻ���ǰ���±���ֵ
		c = i;//��¼��ǰ������
		p = HuffNode[c].pa;//��¼��ǰ���ĸ��׽��
		while (p != -1)
		{//���֧Ϊ0���ҷ�֧Ϊ1
			if (HuffNode[p].lch == c)cd.bit[cd.start] = 0;
			else
			{
				cd.bit[cd.start] = 1;
			}
			cd.start--;//cd��ǰ�ƶ�һλ
				c = p;//c���³ɸ������
				p = HuffNode[c].pa;//pҲ����Ϊc
			
		}
		//�ѹ��ɵĹ������������Ҷ�ӽ���Ӧ���ڽӱ���
		for (j = cd.start + 1; j < n; j++)
		{
			HuffCode[i].bit[j] = cd.bit[j];
			HuffCode[i].start = cd.start;
		}
	}
}
int main()
{
	int n;
	int i = 0;
	int j = 0;
	cout << "�����������" << endl;
	cin >> n;
	HuffmanTree(HuffNode, n);
	HuffmanCode(HuffCode, n);
	for ( i = 0; i < n; i++)
	{
		cout << HuffNode[i].val << ":������������:" ;
		//startָ������ڱ�����λǰһλ
		for ( j = HuffCode[i].start + 1; j < n; j++)
		{
			cout << HuffCode[i].bit[j];
			cout << '\n';
		}
	}
	cout << "���е�211050100305\n" << endl;
	return 0;
}