#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#define MaxInt 32767//表示极大值
#define MVNum 100//最大顶点数
int Path[20][20];//记录最短路径上的顶点的前一个序号
int d[20][20];//记录最短路径的路径值
#define maxsize 9//栈的最大值
using namespace std;
typedef struct
{
	char stationname[20];//站名
}station[10];
typedef struct
{
	char busid[10];//公交车编号
	station busstation;//经过站点名字
	int stationnum;//车站的数目
	int stationnumsave;//车站数目的备份
}bus;
typedef struct busnode
{
	bus data;//公交车数据
	struct busnode* next;//公交车链表的指针域
}busnode, * buslinknode;
typedef struct
{
	char vexs[MVNum];
}vex[MVNum];
typedef struct
{
	vex vex_s;//顶点表
	int arcs[MVNum][MVNum];//邻接矩阵
	int vexnum, arcnum;//图的当前点数和边数
}AMGraph;
typedef struct
{
	int top;//栈顶指针
	int data[maxsize];
}stack;//创建顺序栈
int save[15];//用来储存最短路径上站点在图中的下标
int exsit[10][20];
//每一行代表每个公交编号，每一列代表图中每个结点，值为1表明该点在该公交车路线上，值为0反之，从文件读取
void initstack(stack* s)
{
	s->top = 0;
}
void push(stack* s, int m,int i,int arr[15])
{

	if (s->top == maxsize - 1)
	{
		printf("栈满\n");
	}
	s->data[s->top] = m;
	arr[i] = m;//赋值save数组
	s->top++;
}
void pop(stack* s, AMGraph G)
{
	int i = 0;
	while (s->top != 0)
	{
			s->top--;
			int n = s->data[s->top];
			cout << G.vex_s[n].vexs << "->";
	}
}
void initbuslinknode(buslinknode& l)
{//初始化，把整形值初始化为0，字符串初始化为'\0'
	l = new busnode;
	l->next = NULL;
	l->data.stationnum = 0;
	l->data.stationnumsave = 0;
	l->data.busid[10] = {'\0'};
	int i = 0;
	for (i = 0; i < 9; i++)
	{
		l->data.busstation[i].stationname[20] = {'\0'};
	}
}
void creatbusid(buslinknode& l)
{//尾插法创建链表
	initbuslinknode(l);
	buslinknode r = l;//初始化尾指针
	fstream file;
	file.open("busid.txt");
	if (!file)
	{
		cout << "busid.txt文件打开失败" << endl;
	}
	while (!file.eof())
	{//文件未读完时按行读取公交车编号数据
		buslinknode p = new busnode;
			file.getline(p->data.busid, 10);
			p->next = NULL;//生成新节点把指针域置空
			r->next = p;//把新节点放在尾节点后面
			r = p;//尾节点移动
	}
	file.close();
}
void creatstationnum(buslinknode& l)
{
	buslinknode p = l->next;//定义首元结点
	FILE* fp = fopen("busstationnum.txt", "r");//只读打开
	if (!fp)
	{
		cout << "busstationnum.txt文件打开失败" << endl;
	}
	while (p)
	{//以遍历链表方式把数据赋值给对应链表
		fscanf(fp, "%d", &p->data.stationnum);
		p->data.stationnumsave = p->data.stationnum;//站数的备份，以防止站数被删除后无法录入其他数据
		p = p->next;
	}
	fclose(fp);
}
void creatstation(buslinknode& l)
{
	buslinknode p = l->next;
	int i = 0;
	FILE* fp = fopen("busstation.txt", "r");
	if (!fp)
	{
		cout << "busstation.txt文件打开失败" << endl;
	}
	while (p)
	{
		for (i = 0; i < p->data.stationnum; i++)
		{
			fscanf(fp, "%s", p->data.busstation[i].stationname);
		}
		p = p->next;
	}

	fclose(fp);
}
void updata(buslinknode& l)
{//每次进行数据增加，删除，修改后将对应文档更新
	buslinknode p = l->next;
	FILE* fp1 = fopen("busstation.txt", "w");
	FILE* fp2 = fopen("busstationnum.txt", "w");
	FILE* fp3 = fopen("busid.txt", "w");
	int i = 0;
	int j = 0;
	char a[20] = { '\0'};
	char b[10] = { '\0'};
	while (p)
	{
		if (strcmp(b, p->data.busid) != 0)//不为初值写入
		{
			fprintf(fp3, "%s\n", p->data.busid);
		}
		if (p->data.stationnum >= 0)//大于等于0时写入
		{
			fprintf(fp2, "%d\n", p->data.stationnum);
		}
		for (i = 0; i < p->data.stationnumsave; i++)
		{
			if (strcmp(a, p->data.busstation[i].stationname) != 0)//不为初值写入
			{
				fprintf(fp1, "%s ", p->data.busstation[i].stationname);
			}
		}
		fprintf(fp1, "\n");
		p = p->next;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}
void updataG(AMGraph G)
{
	FILE* fp1 = fopen("num.txt", "w");
	FILE* fp2 = fopen("graphstation.txt", "w");
	FILE* fp3 = fopen("adjancentmatrix.txt", "w");
	int i = 0;
	int j = 0;
	char a[20] = { '\0' };
	if (G.vexnum > 0 && G.arcnum > 0)
	{
		fprintf(fp1, "%d ", G.vexnum);
		fprintf(fp1, "%d ", G.arcnum);
	}
	for (i = 0; i < G.vexnum; i++)
	{
		if (strcmp(a, G.vex_s[i].vexs) != 0)
		{
			fprintf(fp2, "%s ", G.vex_s[i].vexs);
		}
	}
	for (i = 0; i < G.vexnum; i++)
	{
		for (j = 0; j < G.vexnum; j++)
		{
			if (G.arcs[i][j] > 0)
			{
				if (G.arcs[i][j] == MaxInt)
				{
					int n = 0;
					fprintf(fp3, "%d ", n);
				}
				else
				{
					fprintf(fp3, "%d ", G.arcs[i][j]);
				}
			}
			else
			{
				fprintf(fp3, " ");
			}
		}
		fprintf(fp3, "\n");
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}
int LocateVex(AMGraph& G, char a[20])//存在顶点，返回顶点在图中的位置，否则返回-1
{
	int i = 0;
	for (i = 0; i < G.vexnum; i++)
	{
		if (strcmp(a, G.vex_s[i].vexs) == 0)
		{
			return i;
		}
	}
	return -1;
}
void addGraph(AMGraph& G)
{
	int choose = -1;
	int i = 0;
	int j = 0;
	while (choose)
	{
		cout << "请选择你要操作的对象" << endl;
		cout << "1.点" << endl;
		cout << "2.边" << endl;
		cout << "0.exit" << endl;
		cin >> choose;
		if (choose == 1)
		{
			G.vexnum=G.vexnum+1;
			cout << "请输入你要加入图中的点" << endl;
			cin >> G.vex_s[G.vexnum - 1].vexs;
			for (i = 0; i < G.vexnum; i++)
			{
				G.arcs[i][G.vexnum - 1] = MaxInt;
			}
			for (j = 0; j < G.vexnum; j++)
			{
				G.arcs[G.vexnum - 1][j] = MaxInt;
			}
			cout << "增加完成" << endl;
		}
		if (choose == 2)
		{
			G.arcnum = G.arcnum + 1;
			cout << "请输入增加边依附2顶点的下标" << endl;
			int a = 0;
			int b = 0;
			cin >> a;
			cin >> b;
			cout << "请输入对应权值" << endl;
			cin >> G.arcs[a][b];
			cout << "增加完成" << endl;
		}
	}
	updataG(G);
}
void addbuslinknode(buslinknode& l, int j)
{
		int choose = -1;
		int n = 0;
			buslinknode p =l;
			int i = 0;
			while (p && i < j - 1)
			{//找到要增加节点的前一个结点
				p = p->next;
				i++;
			}
			if (!p && i > j - 1)
			{
				cout << "错误" << endl;
			}
			int choice = -1;
			while (choice)
			{
				buslinknode s = new busnode;//生成新结点
				memset(s->data.busid, '\0', sizeof(s->data.busid));
				s->data.stationnum = 0;
				cout << "请选择你操作的对象" << endl;
				cout << "1.公交车" << endl;
				cout << "2.车站" << endl;
				cout << "0.exit" << endl;
				cin >> choice;
				if (choice == 1)
				{//更新增加的数据
					cout << "请输入增加的公交车的编号" << endl;
					cin >> s->data.busid;
					cout << "请输入增加为几站" << endl;
					cin >> s->data.stationnum;
					s->data.stationnumsave = s->data.stationnum;
					for (i = 0; i < s->data.stationnum; i++)
					{
						cout << "请输入站名" << endl;
						cin >> s->data.busstation[i].stationname;
					}
					s->next = p->next;//让s和待增加节点往后的节点连接
					p->next = s;//把结点加入
					cout << "添加完成" << endl;
				}
				if (choice == 2)
				{
					p = p->next;
					cout << "请输入增加哪个位置后" << endl;
					cin >> n;
					cout << "请输入站名" << endl;
					for (i = p->data.stationnum - 1; i >= n - 1; i--)
					{
						p->data.busstation[i + 1] = p->data.busstation[i];
					}
					p->data.stationnum++;
					p->data.stationnumsave++;
					cin >> p->data.busstation[n-1].stationname;
					cout << "添加完成" << endl;
				}
			}
			updata(l);//更新数据
} 
void omitGraph(AMGraph& G)
{
	int choose = -1;
	int i = 0;
	int j = 0;
	int a=0;
	int m = 0;
	while (choose)
	{
		cout << "请选择你要操作的对象" << endl;
		cout << "1.点" << endl;
		cout << "2.边" << endl;
		cout << "0.exit" << endl;
		cin >> choose;
		if (choose == 1)
		{
			G.vexnum = G.vexnum - 1;
			cout << "请输入你要删除图中的点的下标" << endl;
			cin >> a;
			memset(G.vex_s[a].vexs, '\0', sizeof(G.vex_s[a].vexs));
			for (i = 0; i < G.vexnum; i++)
			{
				if (G.arcs[i][j] != MaxInt)
				{
					m++;
				}
				G.arcs[i][a] = -1;
			}
			for (j = 0; j < G.vexnum; j++)
			{
				if (G.arcs[i][j] != MaxInt)
				{
					m++;
				}
				G.arcs[a][j] = -1;
			}
			G.arcnum = G.arcnum - m;
			cout << "删除完成" << endl;
		}
		if (choose == 2)
		{
			G.arcnum = G.arcnum - 1;
			cout << "请输入删除边依附2顶点的下标" << endl;
			int a = 0;
			int b = 0;
			cin >> a;
			cin >> b;
			G.arcs[a][b] = -1;
			cout << "删除完成" << endl;
		}
	}
	updataG(G);
}
void omitbuslinknode(buslinknode& l, int j)
{
		buslinknode p = l;//头结点
		int i = 0;
		while (p->next && i< j - 1)
		{//找到要删除结点的前一个结点
			p = p->next;
			i++;
		}
		if (!(p->next) || i> j- 1)
		{
			cout << "错误" << endl;
		}
		int choice = -1;
		while (choice)
		{
			buslinknode s ;//新结点s
			cout << "请选择你操作的对象" << endl;
			cout << "1.公交车" << endl;
			cout << "2.车站" << endl;
			cout << "0.exit" << endl;
			cin >> choice;
			if (choice == 1)
			{
				s = p->next;//s为要删除的结点
				p->next = s->next;//把s前一个结点与s后一个结点相连接
				delete s;//释放s
				cout << "删除完成" << endl;
			}
			if (choice == 2)
			{
				int flag = 0;//定义标志量
				s = p->next;
				char m[20] = {'\0'};
				cout << "请输入你要删除的车站的名称" << endl;
				cin >> m;
				for (i = 0; i < s->data.stationnumsave; i++)
				{//如果输入车站名在该公交车路线
					if (strcmp(m, s->data.busstation[i].stationname) == 0)
					{//把车站名初始化，以便更新数据时不会传文档上
						memset(s->data.busstation[i].stationname, '\0', sizeof(s->data.busstation[i].stationname));
						//找到要删除的站时
						flag = 1;
						cout << "删除完成" << endl;
						break;
					}
					
				}
				if (flag == 0 && i == s->data.stationnumsave - 1)
				{
					cout << "未找到该站" << endl;
				}
				else
				{
					s->data.stationnum--;
				}
			}
			
		}
		updata(l);//更新数据
}
void changebuslinknode(buslinknode& l, int j)
{
		buslinknode p = l->next;
		int i = 0;
		while (p && i < j-1 )
		{//找到要修改的节点
			p = p->next;
			i++;
		}
		if (!p && i> j - 1)
		{
			cout << "错误" << endl;
		}
		int choose = -1;
		char b[20];
		while (choose)
		{
			cout << "*     请选择要修改的内容  *" << endl;
			cout << "*       1.修改公交车      *" << endl;
			cout << "*       2.修改站名        *" << endl;
			cout << "*         0.exit          *" << endl;
			int k = 0;
			cin >> choose;
			switch (choose)
			{
			case 1:
				  cout << "请输入新公交车编号" << endl;
				   cin >> p->data.busid;//修改后的公交车编号
				   cout << "请输入新公交车的站数" << endl;
				   cin >> p->data.stationnum;//修改后的车站数
				   p->data.stationnumsave = p->data.stationnum;//同步车站数备份值
				   cout <<" 修改完成 "<< endl;
				    break;
			case 2:
				cout << "请输入修改第几个站点" << endl;
				cin >> k;
				getchar();//清空回车符
				cout << "请输入新站点名字" << endl;
				cin >> p->data.busstation[k - 1].stationname;//输入修改后的站名
				cout << "修改完成" << endl;
				break;
			default:
				cout << "选择错误，请重新选择" << endl;
				break;
			}
		}
		updata(l);//更新数据
}
void changeGraph(AMGraph&G)
{
	int choose = -1;
	int i = 0;
	int j = 0;
	int m = 0;
	while (choose)
	{
		cout << "请选择你要操作的对象" << endl;
		cout << "1.点" << endl;
		cout << "2.边" << endl;
		cout << "0.exit" << endl;
		cin >> choose;
		if (choose == 1)
		{
			cout << "请输入把点的数目修改为" << endl;
			cin >> G.vexnum;
			cout << "请输入你要修改图中点的下标" << endl;
			cin >> m;
			cout << "请输入修改后的名字" << endl;
			cin >> G.vex_s[m].vexs;
			cout << "修改完成" << endl;
		}
		if (choose == 2)
		{
			cout << "请输入把边的数目修改为" << endl;
			cin >> G.arcnum;
			cout << "请输入修改边依附2顶点的下标" << endl;
			int a = 0;
			int b = 0;
			cin >> a;
			cin >> b;
			cout << "请输入对应权值" << endl;
			cin >> G.arcs[a][b];
			cout << "修改完成" << endl;
		}
	}
	updataG(G);
}
void busfind(buslinknode &l,char a[10])
{
	buslinknode p=l->next;
	int i = 0;
	while (p && strcmp(a,p->data.busid)!=0)
	{//找到文档里对应公交车
		p = p->next;
	}
	if (!p )
	{
		cout << "错误" << endl;
	}
	cout << "公交车编号为:" << p->data.busid << endl;
	cout << "公交车站数为" <<p->data.stationnum<< endl;
	int k = 0;
	while (k<p->data.stationnum-1)
	{//打印车站名
		cout << p->data.busstation[k].stationname << "->";
		k++;
	}
	cout << p->data.busstation[k].stationname << endl;
}
void stationfind(buslinknode&l,char a[20])
{
	buslinknode p = l->next;
	int i = 0;
	int flag = 0;
	cout << "经过此站的公交车编号为:";
	while (p)
	{//遍历整个车站
		for (i = 0; i < p->data.stationnum; i++)
		{//找到含有该车站的公交车编号
			if (strcmp(p->data.busstation[i].stationname, a) == 0)
			{
				cout << p->data.busid << endl;
				flag++;
			}
		}
		p = p->next;
	}
	if (flag == 0)
	{
		cout << "错误" << endl;
	}
}
void CreateUDN(AMGraph& G)
{
	int i = 0;
	int j = 0;
	int k = 0;
	char v1, v2;
	int w = 0;
	FILE* fp1 = fopen("num.txt", "r");
	FILE* fp2 = fopen("graphstation.txt", "r");
	FILE* fp3 = fopen("adjancentmatrix.txt", "r");
	if (!fp1)
	{
		cout << "num.txt文件打开失败" << endl;
	}
	if (!fp2)
	{
		cout << "graphstation.txt文件打开失败" << endl;
	}
	if (!fp3)
	{
		cout << "adjancentmatrix.txt文件打开失败" << endl;
	}
	fscanf(fp1, "%d", &G.vexnum);
	fscanf(fp1, "%d", &G.arcnum);
	for (i = 0; i < G.vexnum; i++)
	{
		fscanf(fp2,"%s", G.vex_s[i].vexs);
	}
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
		{
			int n=0;//初始化邻接矩阵，边的权值为MaxInt
			fscanf(fp3, "%d", &n);
			if (n == 0)
			{
				G.arcs[i][j] = MaxInt;
			}
			else
			{
				G.arcs[i][j] = n;
			}
		}
}
void createxsit(AMGraph G)
{//对save数组和exsit数组初始化，顺便读取值创建
	int i = 0;
	int j = 0;
	for (i = 0; i < 15; i++)
	{
		save[i] = 0;
	}
	for (i = 0; i < 10; i++)
		for (j = 0; j < 20; j++)
		{
			exsit[i][j] = 0;
		}
	FILE* fp = fopen("exsit.txt", "r");
	if (!fp)
	{
		cout << "exsit.txt文件打开失败" << endl;
	}
	for (i=0;i<5;i++)
		for (j = 0; j < G.vexnum; j++)
		{
			fscanf(fp, "%d", &exsit[i][j]);
		}
}
void printbusid(buslinknode& l, int i)
{
	buslinknode p = l->next;//首元结点
	int m = 0;
	while (m < i)
	{
		m++;
		p = p->next;
	}//找到对应的链结点
	cout << p->data.busid << " ";
}
void destory(int arr[][20],int a,int ac[10],int m)
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		arr[i][a] = 0;//把已经打印的exsit数组还原初始化
	}
	ac[m] = 18;//把已经打印的save数组赋值标记
}
void busidfind(buslinknode&l,int a[10],int arr[][20],int m)
{
	int i = 0;
	int j = 0;
	int flag = 0;
	for (i = 0; i < 5; i++)
	{
		while (arr[i][a[0]] == 0&&a[0]<18)//没有被标记并且第一个站点可以查询
		{
			i++;
		}
		for (j = 0; j <= m; j++)
		{
			if (a[j] < 18)//没有被标记
			{
				if (arr[i][a[j]] == 1)
				{
					destory(arr, a[j], a,j);//摧毁数组
					printbusid(l, i);//输出编号
					if (arr[i][a[j + 1]] == 1)
					{
						destory(arr, a[j + 1], a,j+1);//如果与上一个公交编号一样，打印并摧毁
						printbusid(l, i);
					}
					else
					{
						flag++;
					}
				}
			}

		}
	}
	cout << "\n";
	//最后一个元素也进入else选择，票价上一次车1元
	cout << "换乘" << flag-1 << "次" << "票价为" << flag << "元" << endl;
}
void shortpathfloyd(AMGraph G, int v0, int vn,buslinknode&l)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < G.vexnum; i++)//初始化d数组为2结点权值边，Paths数组若存在为前驱值，否则为-1
		for (j = 0; j < G.vexnum; j++)
		{
			d[i][j] = G.arcs[i][j];
			if (d[i][j] < MaxInt && i != j)
			{
				Path[i][j] = i;
			}
			else
			{
				Path[i][j] = -1;
			}
		}
	for (k = 0; k < G.vexnum; k++)
		for (i = 0; i < G.vexnum; i++)
			for (j = 0; j < G.vexnum; j++)
				if (d[i][k] + d[k][j] < d[i][j])//如果从i经k到j的路径更短更新数组
				{
					d[i][j] = d[i][k] + d[k][j];
					Path[i][j] = Path[k][j];
				}
	
	int h = 0;
	int n = 0;
	cout << "输入起始时间时" << endl;
	cin >> h;
	cout << "输入起始时间分" << endl;
	cin >> n;
	n = n + d[v0][vn];//d[v0][vn]为最短距离
	h = h + n / 60;//计算时
	n = n % 60;//计算分
	cout << "预计达到时间为" <<h <<"时"<<n<<"分"<< endl;
	createxsit(G);//创建二维数组exsit
	stack* s = NULL;
	s = (stack*)malloc(sizeof(stack));//申请栈的内存
	initstack(s);
	int m = 0;
	save[0] = v0;//把下标v0加入数组
	i = 1;
	cout << G.vex_s[v0].vexs << "->";
	while (Path[v0][vn] != v0)
	{
		push(s, Path[v0][vn],i,save);//入栈
		m = Path[v0][vn];
		Path[v0][vn] = Path[v0][m];//更新path数组
		i++;
	}
	pop(s, G);//出栈
	cout << G.vex_s[vn].vexs << endl;
	save[i] = vn;//把下标vn加入数组
	cout << "对应公交车编号为" << endl;
	busidfind(l, save, exsit, i);//查找每个站的编号
}
void menu()
{//打印菜单
	cout <<"        欢迎使用智能公交管理系统          " << endl;
	cout <<"******************************************" << endl;
	cout <<"*           1.增加公交基本信息           *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*           2.删除公交基本信息           *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*           3.修改公交基本信息           *"<< endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*           4.查询公交基本信息           *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*           5.查询最短的线路             *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*       6.查询某站所有公交基本信息       *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*                0.exit                  *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"******************************************" << endl;
}
int secureregist()
{//管理员权限登录
	int flag = 0;//记录账号密码正确的次数
	int i = 0;
	char a[15] = { '\0' };
	char b[15] = {'\0'};
	char c[15] = { "1003" };
	char d[15] = { "gyd123" };
	cout << "请输入管理员账号" << endl;
	cin >> a;
	if (strcmp(a, c) == 0)
	{
		flag++;
	}
	cout << "请输入管理员密码（6到13数字字母）" << endl;
	while ((b[i] = _getch()) != '\r'&&i<=12)//判断是否为回车符,隐藏输入的字符
	{

		if (b[i] == '\b')//判断是否为回退键
		{
			int j = 0;
			i--;
			system("cls");//清空屏幕
			//还原屏幕
			cout << "请输入管理员账号" << endl;
			cout << a << endl;
			cout << "请输入管理员密码（6到13数字字母）" << endl;
			//还原*号数目
			for (j=0; j < i; j++)
			{
				putchar('*');
			}
			continue;//略去后面语句继续循环
		}
		putchar('*');//用*覆盖密码
		i++;//字符指针加1
	}
	b[i] = { '\0' };//把最后一位回车键变为初值'\0'
	printf("\n");
	if (i > 12)
	{
		cout << "密码位数超出限制" << endl;
	}
	if (strcmp(b, d) == 0)
	{
		flag++;
	}
	return flag;
}
int main()
{
	buslinknode l;
	AMGraph G;
	int choice = -1;
	creatbusid(l);
	creatstationnum(l);
	creatstation(l);
	CreateUDN(G);
	char arr[10];//公交车编号
	char a[20];//车站
	char b[20];//车站
	int a_v = 0;
	int b_v = 0;
	while (choice)
	{
		menu();
		cout << "请选择要进行的操作" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			break;
		case 1:
			if (secureregist() == 2)
			{
				int b = 0;
				cout << "1.链表" << endl;
				cout << "2.图" << endl;
				int a = 0;
				cin >> b;
				if (b == 1)
				{
					cout << "请输入你想加在第几个车或哪个车的车站" << endl;
					cin >> a;
					addbuslinknode(l, a);
				}
				if (b == 2)
				{
					addGraph(G);
				}
			}
			else
			{
				cout << "账号或密码错误请重试" << endl;
			}
			break;
		case 2:
			if (secureregist() == 2)
			{
				int b = 0;
				cout << "1.链表" << endl;
				cout << "2.图" << endl;
				int a = 0;
				cin >> b;
				if (b == 1)
				{
					cout << "请输入你想删除第几个公交车的信息" << endl;
					cin >> a;
					omitbuslinknode(l, a);
				}
				if (b == 2)
				{
					omitGraph(G);
				}
			}
			else
			{
				cout << "账号或密码错误请重试" << endl;
			}
			break;
		case 3:
			if (secureregist() == 2)
			{
				int b = 0;
				cout << "1.链表" << endl;
				cout << "2.图" << endl;
				cin >> b;
				int a = 0;
				if (b == 1)
				{
					cout << "请输入你想修改第几个车的信息" << endl;
					cin >> a;
					changebuslinknode(l, a);
				}
				else
				{
					changeGraph(G);
				}
			}
			else
			{
				cout << "账号或密码错误请重试" << endl;
			}
			break;
		case 4:
			cout << "请输入公交车编号" << endl;
			cin >> arr;
			busfind(l,arr);
			break;
		case 5:
		    cout << "请输入起点站" << endl;
		    cin >> a;
		    a_v = LocateVex(G, a);
		    while (a_v == -1)
		    {
			cout << "起点站错误" << endl;
			cout << "请输入起点站" << endl;
			cin >> a;
			a_v = LocateVex(G, a);
		     }
		     cout << "请输入终点站" << endl;
		     cin >> b;
		     b_v = LocateVex(G, b);
			 while (b_v == -1)
			 {
				 cout << "终点站错误" << endl;
				 cout << "请输入终点站" << endl;
				 cin >> b;
				 b_v = LocateVex(G, b);
			 }
			 shortpathfloyd(G, a_v, b_v,l);
		break;
		case 6:
			cout << "请输入站名" << endl;
			cin >> arr;
			stationfind(l,arr);
			break;
		default:
			cout << "选择错误，请重新选择" << endl;
		}
	}
	return 0;
}