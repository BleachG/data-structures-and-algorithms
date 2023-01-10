#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#define MaxInt 32767//��ʾ����ֵ
#define MVNum 100//��󶥵���
int Path[20][20];//��¼���·���ϵĶ����ǰһ�����
int d[20][20];//��¼���·����·��ֵ
#define maxsize 9//ջ�����ֵ
using namespace std;
typedef struct
{
	char stationname[20];//վ��
}station[10];
typedef struct
{
	char busid[10];//���������
	station busstation;//����վ������
	int stationnum;//��վ����Ŀ
	int stationnumsave;//��վ��Ŀ�ı���
}bus;
typedef struct busnode
{
	bus data;//����������
	struct busnode* next;//�����������ָ����
}busnode, * buslinknode;
typedef struct
{
	char vexs[MVNum];
}vex[MVNum];
typedef struct
{
	vex vex_s;//�����
	int arcs[MVNum][MVNum];//�ڽӾ���
	int vexnum, arcnum;//ͼ�ĵ�ǰ�����ͱ���
}AMGraph;
typedef struct
{
	int top;//ջ��ָ��
	int data[maxsize];
}stack;//����˳��ջ
int save[15];//�����������·����վ����ͼ�е��±�
int exsit[10][20];
//ÿһ�д���ÿ��������ţ�ÿһ�д���ͼ��ÿ����㣬ֵΪ1�����õ��ڸù�����·���ϣ�ֵΪ0��֮�����ļ���ȡ
void initstack(stack* s)
{
	s->top = 0;
}
void push(stack* s, int m,int i,int arr[15])
{

	if (s->top == maxsize - 1)
	{
		printf("ջ��\n");
	}
	s->data[s->top] = m;
	arr[i] = m;//��ֵsave����
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
{//��ʼ����������ֵ��ʼ��Ϊ0���ַ�����ʼ��Ϊ'\0'
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
{//β�巨��������
	initbuslinknode(l);
	buslinknode r = l;//��ʼ��βָ��
	fstream file;
	file.open("busid.txt");
	if (!file)
	{
		cout << "busid.txt�ļ���ʧ��" << endl;
	}
	while (!file.eof())
	{//�ļ�δ����ʱ���ж�ȡ�������������
		buslinknode p = new busnode;
			file.getline(p->data.busid, 10);
			p->next = NULL;//�����½ڵ��ָ�����ÿ�
			r->next = p;//���½ڵ����β�ڵ����
			r = p;//β�ڵ��ƶ�
	}
	file.close();
}
void creatstationnum(buslinknode& l)
{
	buslinknode p = l->next;//������Ԫ���
	FILE* fp = fopen("busstationnum.txt", "r");//ֻ����
	if (!fp)
	{
		cout << "busstationnum.txt�ļ���ʧ��" << endl;
	}
	while (p)
	{//�Ա�������ʽ�����ݸ�ֵ����Ӧ����
		fscanf(fp, "%d", &p->data.stationnum);
		p->data.stationnumsave = p->data.stationnum;//վ���ı��ݣ��Է�ֹվ����ɾ�����޷�¼����������
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
		cout << "busstation.txt�ļ���ʧ��" << endl;
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
{//ÿ�ν����������ӣ�ɾ�����޸ĺ󽫶�Ӧ�ĵ�����
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
		if (strcmp(b, p->data.busid) != 0)//��Ϊ��ֵд��
		{
			fprintf(fp3, "%s\n", p->data.busid);
		}
		if (p->data.stationnum >= 0)//���ڵ���0ʱд��
		{
			fprintf(fp2, "%d\n", p->data.stationnum);
		}
		for (i = 0; i < p->data.stationnumsave; i++)
		{
			if (strcmp(a, p->data.busstation[i].stationname) != 0)//��Ϊ��ֵд��
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
int LocateVex(AMGraph& G, char a[20])//���ڶ��㣬���ض�����ͼ�е�λ�ã����򷵻�-1
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
		cout << "��ѡ����Ҫ�����Ķ���" << endl;
		cout << "1.��" << endl;
		cout << "2.��" << endl;
		cout << "0.exit" << endl;
		cin >> choose;
		if (choose == 1)
		{
			G.vexnum=G.vexnum+1;
			cout << "��������Ҫ����ͼ�еĵ�" << endl;
			cin >> G.vex_s[G.vexnum - 1].vexs;
			for (i = 0; i < G.vexnum; i++)
			{
				G.arcs[i][G.vexnum - 1] = MaxInt;
			}
			for (j = 0; j < G.vexnum; j++)
			{
				G.arcs[G.vexnum - 1][j] = MaxInt;
			}
			cout << "�������" << endl;
		}
		if (choose == 2)
		{
			G.arcnum = G.arcnum + 1;
			cout << "���������ӱ�����2������±�" << endl;
			int a = 0;
			int b = 0;
			cin >> a;
			cin >> b;
			cout << "�������ӦȨֵ" << endl;
			cin >> G.arcs[a][b];
			cout << "�������" << endl;
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
			{//�ҵ�Ҫ���ӽڵ��ǰһ�����
				p = p->next;
				i++;
			}
			if (!p && i > j - 1)
			{
				cout << "����" << endl;
			}
			int choice = -1;
			while (choice)
			{
				buslinknode s = new busnode;//�����½��
				memset(s->data.busid, '\0', sizeof(s->data.busid));
				s->data.stationnum = 0;
				cout << "��ѡ��������Ķ���" << endl;
				cout << "1.������" << endl;
				cout << "2.��վ" << endl;
				cout << "0.exit" << endl;
				cin >> choice;
				if (choice == 1)
				{//�������ӵ�����
					cout << "���������ӵĹ������ı��" << endl;
					cin >> s->data.busid;
					cout << "����������Ϊ��վ" << endl;
					cin >> s->data.stationnum;
					s->data.stationnumsave = s->data.stationnum;
					for (i = 0; i < s->data.stationnum; i++)
					{
						cout << "������վ��" << endl;
						cin >> s->data.busstation[i].stationname;
					}
					s->next = p->next;//��s�ʹ����ӽڵ�����Ľڵ�����
					p->next = s;//�ѽ�����
					cout << "������" << endl;
				}
				if (choice == 2)
				{
					p = p->next;
					cout << "�����������ĸ�λ�ú�" << endl;
					cin >> n;
					cout << "������վ��" << endl;
					for (i = p->data.stationnum - 1; i >= n - 1; i--)
					{
						p->data.busstation[i + 1] = p->data.busstation[i];
					}
					p->data.stationnum++;
					p->data.stationnumsave++;
					cin >> p->data.busstation[n-1].stationname;
					cout << "������" << endl;
				}
			}
			updata(l);//��������
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
		cout << "��ѡ����Ҫ�����Ķ���" << endl;
		cout << "1.��" << endl;
		cout << "2.��" << endl;
		cout << "0.exit" << endl;
		cin >> choose;
		if (choose == 1)
		{
			G.vexnum = G.vexnum - 1;
			cout << "��������Ҫɾ��ͼ�еĵ���±�" << endl;
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
			cout << "ɾ�����" << endl;
		}
		if (choose == 2)
		{
			G.arcnum = G.arcnum - 1;
			cout << "������ɾ��������2������±�" << endl;
			int a = 0;
			int b = 0;
			cin >> a;
			cin >> b;
			G.arcs[a][b] = -1;
			cout << "ɾ�����" << endl;
		}
	}
	updataG(G);
}
void omitbuslinknode(buslinknode& l, int j)
{
		buslinknode p = l;//ͷ���
		int i = 0;
		while (p->next && i< j - 1)
		{//�ҵ�Ҫɾ������ǰһ�����
			p = p->next;
			i++;
		}
		if (!(p->next) || i> j- 1)
		{
			cout << "����" << endl;
		}
		int choice = -1;
		while (choice)
		{
			buslinknode s ;//�½��s
			cout << "��ѡ��������Ķ���" << endl;
			cout << "1.������" << endl;
			cout << "2.��վ" << endl;
			cout << "0.exit" << endl;
			cin >> choice;
			if (choice == 1)
			{
				s = p->next;//sΪҪɾ���Ľ��
				p->next = s->next;//��sǰһ�������s��һ�����������
				delete s;//�ͷ�s
				cout << "ɾ�����" << endl;
			}
			if (choice == 2)
			{
				int flag = 0;//�����־��
				s = p->next;
				char m[20] = {'\0'};
				cout << "��������Ҫɾ���ĳ�վ������" << endl;
				cin >> m;
				for (i = 0; i < s->data.stationnumsave; i++)
				{//������복վ���ڸù�����·��
					if (strcmp(m, s->data.busstation[i].stationname) == 0)
					{//�ѳ�վ����ʼ�����Ա��������ʱ���ᴫ�ĵ���
						memset(s->data.busstation[i].stationname, '\0', sizeof(s->data.busstation[i].stationname));
						//�ҵ�Ҫɾ����վʱ
						flag = 1;
						cout << "ɾ�����" << endl;
						break;
					}
					
				}
				if (flag == 0 && i == s->data.stationnumsave - 1)
				{
					cout << "δ�ҵ���վ" << endl;
				}
				else
				{
					s->data.stationnum--;
				}
			}
			
		}
		updata(l);//��������
}
void changebuslinknode(buslinknode& l, int j)
{
		buslinknode p = l->next;
		int i = 0;
		while (p && i < j-1 )
		{//�ҵ�Ҫ�޸ĵĽڵ�
			p = p->next;
			i++;
		}
		if (!p && i> j - 1)
		{
			cout << "����" << endl;
		}
		int choose = -1;
		char b[20];
		while (choose)
		{
			cout << "*     ��ѡ��Ҫ�޸ĵ�����  *" << endl;
			cout << "*       1.�޸Ĺ�����      *" << endl;
			cout << "*       2.�޸�վ��        *" << endl;
			cout << "*         0.exit          *" << endl;
			int k = 0;
			cin >> choose;
			switch (choose)
			{
			case 1:
				  cout << "�������¹��������" << endl;
				   cin >> p->data.busid;//�޸ĺ�Ĺ��������
				   cout << "�������¹�������վ��" << endl;
				   cin >> p->data.stationnum;//�޸ĺ�ĳ�վ��
				   p->data.stationnumsave = p->data.stationnum;//ͬ����վ������ֵ
				   cout <<" �޸���� "<< endl;
				    break;
			case 2:
				cout << "�������޸ĵڼ���վ��" << endl;
				cin >> k;
				getchar();//��ջس���
				cout << "��������վ������" << endl;
				cin >> p->data.busstation[k - 1].stationname;//�����޸ĺ��վ��
				cout << "�޸����" << endl;
				break;
			default:
				cout << "ѡ�����������ѡ��" << endl;
				break;
			}
		}
		updata(l);//��������
}
void changeGraph(AMGraph&G)
{
	int choose = -1;
	int i = 0;
	int j = 0;
	int m = 0;
	while (choose)
	{
		cout << "��ѡ����Ҫ�����Ķ���" << endl;
		cout << "1.��" << endl;
		cout << "2.��" << endl;
		cout << "0.exit" << endl;
		cin >> choose;
		if (choose == 1)
		{
			cout << "������ѵ����Ŀ�޸�Ϊ" << endl;
			cin >> G.vexnum;
			cout << "��������Ҫ�޸�ͼ�е���±�" << endl;
			cin >> m;
			cout << "�������޸ĺ������" << endl;
			cin >> G.vex_s[m].vexs;
			cout << "�޸����" << endl;
		}
		if (choose == 2)
		{
			cout << "������ѱߵ���Ŀ�޸�Ϊ" << endl;
			cin >> G.arcnum;
			cout << "�������޸ı�����2������±�" << endl;
			int a = 0;
			int b = 0;
			cin >> a;
			cin >> b;
			cout << "�������ӦȨֵ" << endl;
			cin >> G.arcs[a][b];
			cout << "�޸����" << endl;
		}
	}
	updataG(G);
}
void busfind(buslinknode &l,char a[10])
{
	buslinknode p=l->next;
	int i = 0;
	while (p && strcmp(a,p->data.busid)!=0)
	{//�ҵ��ĵ����Ӧ������
		p = p->next;
	}
	if (!p )
	{
		cout << "����" << endl;
	}
	cout << "���������Ϊ:" << p->data.busid << endl;
	cout << "������վ��Ϊ" <<p->data.stationnum<< endl;
	int k = 0;
	while (k<p->data.stationnum-1)
	{//��ӡ��վ��
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
	cout << "������վ�Ĺ��������Ϊ:";
	while (p)
	{//����������վ
		for (i = 0; i < p->data.stationnum; i++)
		{//�ҵ����иó�վ�Ĺ��������
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
		cout << "����" << endl;
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
		cout << "num.txt�ļ���ʧ��" << endl;
	}
	if (!fp2)
	{
		cout << "graphstation.txt�ļ���ʧ��" << endl;
	}
	if (!fp3)
	{
		cout << "adjancentmatrix.txt�ļ���ʧ��" << endl;
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
			int n=0;//��ʼ���ڽӾ��󣬱ߵ�ȨֵΪMaxInt
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
{//��save�����exsit�����ʼ����˳���ȡֵ����
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
		cout << "exsit.txt�ļ���ʧ��" << endl;
	}
	for (i=0;i<5;i++)
		for (j = 0; j < G.vexnum; j++)
		{
			fscanf(fp, "%d", &exsit[i][j]);
		}
}
void printbusid(buslinknode& l, int i)
{
	buslinknode p = l->next;//��Ԫ���
	int m = 0;
	while (m < i)
	{
		m++;
		p = p->next;
	}//�ҵ���Ӧ�������
	cout << p->data.busid << " ";
}
void destory(int arr[][20],int a,int ac[10],int m)
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		arr[i][a] = 0;//���Ѿ���ӡ��exsit���黹ԭ��ʼ��
	}
	ac[m] = 18;//���Ѿ���ӡ��save���鸳ֵ���
}
void busidfind(buslinknode&l,int a[10],int arr[][20],int m)
{
	int i = 0;
	int j = 0;
	int flag = 0;
	for (i = 0; i < 5; i++)
	{
		while (arr[i][a[0]] == 0&&a[0]<18)//û�б���ǲ��ҵ�һ��վ����Բ�ѯ
		{
			i++;
		}
		for (j = 0; j <= m; j++)
		{
			if (a[j] < 18)//û�б����
			{
				if (arr[i][a[j]] == 1)
				{
					destory(arr, a[j], a,j);//�ݻ�����
					printbusid(l, i);//������
					if (arr[i][a[j + 1]] == 1)
					{
						destory(arr, a[j + 1], a,j+1);//�������һ���������һ������ӡ���ݻ�
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
	//���һ��Ԫ��Ҳ����elseѡ��Ʊ����һ�γ�1Ԫ
	cout << "����" << flag-1 << "��" << "Ʊ��Ϊ" << flag << "Ԫ" << endl;
}
void shortpathfloyd(AMGraph G, int v0, int vn,buslinknode&l)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < G.vexnum; i++)//��ʼ��d����Ϊ2���Ȩֵ�ߣ�Paths����������Ϊǰ��ֵ������Ϊ-1
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
				if (d[i][k] + d[k][j] < d[i][j])//�����i��k��j��·�����̸�������
				{
					d[i][j] = d[i][k] + d[k][j];
					Path[i][j] = Path[k][j];
				}
	
	int h = 0;
	int n = 0;
	cout << "������ʼʱ��ʱ" << endl;
	cin >> h;
	cout << "������ʼʱ���" << endl;
	cin >> n;
	n = n + d[v0][vn];//d[v0][vn]Ϊ��̾���
	h = h + n / 60;//����ʱ
	n = n % 60;//�����
	cout << "Ԥ�ƴﵽʱ��Ϊ" <<h <<"ʱ"<<n<<"��"<< endl;
	createxsit(G);//������ά����exsit
	stack* s = NULL;
	s = (stack*)malloc(sizeof(stack));//����ջ���ڴ�
	initstack(s);
	int m = 0;
	save[0] = v0;//���±�v0��������
	i = 1;
	cout << G.vex_s[v0].vexs << "->";
	while (Path[v0][vn] != v0)
	{
		push(s, Path[v0][vn],i,save);//��ջ
		m = Path[v0][vn];
		Path[v0][vn] = Path[v0][m];//����path����
		i++;
	}
	pop(s, G);//��ջ
	cout << G.vex_s[vn].vexs << endl;
	save[i] = vn;//���±�vn��������
	cout << "��Ӧ���������Ϊ" << endl;
	busidfind(l, save, exsit, i);//����ÿ��վ�ı��
}
void menu()
{//��ӡ�˵�
	cout <<"        ��ӭʹ�����ܹ�������ϵͳ          " << endl;
	cout <<"******************************************" << endl;
	cout <<"*           1.���ӹ���������Ϣ           *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*           2.ɾ������������Ϣ           *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*           3.�޸Ĺ���������Ϣ           *"<< endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*           4.��ѯ����������Ϣ           *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*           5.��ѯ��̵���·             *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*       6.��ѯĳվ���й���������Ϣ       *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"*                0.exit                  *" << endl;
	cout <<"*________________________________________*" << endl;
	cout <<"******************************************" << endl;
}
int secureregist()
{//����ԱȨ�޵�¼
	int flag = 0;//��¼�˺�������ȷ�Ĵ���
	int i = 0;
	char a[15] = { '\0' };
	char b[15] = {'\0'};
	char c[15] = { "1003" };
	char d[15] = { "gyd123" };
	cout << "���������Ա�˺�" << endl;
	cin >> a;
	if (strcmp(a, c) == 0)
	{
		flag++;
	}
	cout << "���������Ա���루6��13������ĸ��" << endl;
	while ((b[i] = _getch()) != '\r'&&i<=12)//�ж��Ƿ�Ϊ�س���,����������ַ�
	{

		if (b[i] == '\b')//�ж��Ƿ�Ϊ���˼�
		{
			int j = 0;
			i--;
			system("cls");//�����Ļ
			//��ԭ��Ļ
			cout << "���������Ա�˺�" << endl;
			cout << a << endl;
			cout << "���������Ա���루6��13������ĸ��" << endl;
			//��ԭ*����Ŀ
			for (j=0; j < i; j++)
			{
				putchar('*');
			}
			continue;//��ȥ����������ѭ��
		}
		putchar('*');//��*��������
		i++;//�ַ�ָ���1
	}
	b[i] = { '\0' };//�����һλ�س�����Ϊ��ֵ'\0'
	printf("\n");
	if (i > 12)
	{
		cout << "����λ����������" << endl;
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
	char arr[10];//���������
	char a[20];//��վ
	char b[20];//��վ
	int a_v = 0;
	int b_v = 0;
	while (choice)
	{
		menu();
		cout << "��ѡ��Ҫ���еĲ���" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			break;
		case 1:
			if (secureregist() == 2)
			{
				int b = 0;
				cout << "1.����" << endl;
				cout << "2.ͼ" << endl;
				int a = 0;
				cin >> b;
				if (b == 1)
				{
					cout << "������������ڵڼ��������ĸ����ĳ�վ" << endl;
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
				cout << "�˺Ż��������������" << endl;
			}
			break;
		case 2:
			if (secureregist() == 2)
			{
				int b = 0;
				cout << "1.����" << endl;
				cout << "2.ͼ" << endl;
				int a = 0;
				cin >> b;
				if (b == 1)
				{
					cout << "����������ɾ���ڼ�������������Ϣ" << endl;
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
				cout << "�˺Ż��������������" << endl;
			}
			break;
		case 3:
			if (secureregist() == 2)
			{
				int b = 0;
				cout << "1.����" << endl;
				cout << "2.ͼ" << endl;
				cin >> b;
				int a = 0;
				if (b == 1)
				{
					cout << "�����������޸ĵڼ���������Ϣ" << endl;
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
				cout << "�˺Ż��������������" << endl;
			}
			break;
		case 4:
			cout << "�����빫�������" << endl;
			cin >> arr;
			busfind(l,arr);
			break;
		case 5:
		    cout << "���������վ" << endl;
		    cin >> a;
		    a_v = LocateVex(G, a);
		    while (a_v == -1)
		    {
			cout << "���վ����" << endl;
			cout << "���������վ" << endl;
			cin >> a;
			a_v = LocateVex(G, a);
		     }
		     cout << "�������յ�վ" << endl;
		     cin >> b;
		     b_v = LocateVex(G, b);
			 while (b_v == -1)
			 {
				 cout << "�յ�վ����" << endl;
				 cout << "�������յ�վ" << endl;
				 cin >> b;
				 b_v = LocateVex(G, b);
			 }
			 shortpathfloyd(G, a_v, b_v,l);
		break;
		case 6:
			cout << "������վ��" << endl;
			cin >> arr;
			stationfind(l,arr);
			break;
		default:
			cout << "ѡ�����������ѡ��" << endl;
		}
	}
	return 0;
}