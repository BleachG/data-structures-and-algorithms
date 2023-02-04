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
	double w;//权值
	int pa;//双亲节点
	int lch;//左孩子结点
	int rch;//右孩子结点
	char val;//字符
}HNodeType;//结点结构体
typedef struct
{
	int bit[maxbit];
		int start;
}HCodeType;//编码结构体
HNodeType HuffNode[maxnode];//定义结点结构体
HCodeType HuffCode[maxleaf];//定义编码结构体
void HuffmanTree(HNodeType HuffNode[], int n)
{
	int x1 = 0; int x2=0;//哈夫曼树2个最小值权值点权值序号
	double m1, m2;//哈夫曼树2个最小值权值点权值
	int i, j;//循环变量
	for (i = 0; i < 2 * n - 1; i++)//多开n-1结点存放在新结点
	{//初始化双亲，左，右孩子结点，权重
		HuffNode[i].w = 0;
		HuffNode[i].pa = -1;
		HuffNode[i].lch= -1;
		HuffNode[i].rch = -1;
	}
	//输入n个叶子结点权值
	for (i = 0; i < n; i++)
	{
		cout << "请输入值和权重" << i + 1 << endl;
		cin >> HuffNode[i].val >> HuffNode[i].w;
	}
	for (i = 0; i < n - 1; i++)
	{
		m1 = m2 = maxvalue;//最小权重数默认最大值
		x1 = x2 = -1;//2个最小权值值序号为-1
		//找最小值和次小值
		for (j = 0; j < n + i; j++)
		{
			if (HuffNode[j].w < m1 && HuffNode[j].pa == -1)
			{
				m2 = m1;
				x2 = x1;
				m1 = HuffNode[j].w;//把最小结点权值给m1
				x1 = j;
			}

			else if (HuffNode[j].w < m2 && HuffNode[j].pa == -1)
				m2 = HuffNode[j].w;//把最小结点权值给m2
			{
				x2 = j;
			}
		}
		//更新合成该树的2个子节点和双亲节点
		HuffNode[x1].pa = n + i;
		HuffNode[x2].pa = n + i;
		HuffNode[n + i].w = m1 + m2;
		HuffNode[n + i].lch = x1;
		HuffNode[n + i].rch = x2;
	}
}
void HuffmanCode(HCodeType HuffCode[], int n)
{
	HCodeType cd;//定义临时变量存储结点信息
	int c, p, i, j;
	for (i = 0; i < n; i++)//遍历叶子结点，通过叶子结点到根节点逆向写出哈夫曼编码
	{
		cd.start = n - 1;//从后向前更新编码值
		c = i;//记录当前结点序号
		p = HuffNode[c].pa;//记录当前结点的父亲结点
		while (p != -1)
		{//左分支为0，右分支为1
			if (HuffNode[p].lch == c)cd.bit[cd.start] = 0;
			else
			{
				cd.bit[cd.start] = 1;
			}
			cd.start--;//cd向前移动一位
				c = p;//c更新成父结点编号
				p = HuffNode[c].pa;//p也更新为c
			
		}
		//把构成的哈夫曼编码存入叶子结点对应的邻接表中
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
	cout << "请输入结点个数" << endl;
	cin >> n;
	HuffmanTree(HuffNode, n);
	HuffmanCode(HuffCode, n);
	for ( i = 0; i < n; i++)
	{
		cout << HuffNode[i].val << ":哈夫曼编码是:" ;
		//start指向相对于编码首位前一位
		for ( j = HuffCode[i].start + 1; j < n; j++)
		{
			cout << HuffCode[i].bit[j];
			cout << '\n';
		}
	}
	cout << "高有典211050100305\n" << endl;
	return 0;
}