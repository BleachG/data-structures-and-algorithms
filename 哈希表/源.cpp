#include <iostream>
using namespace std;
#define max 16;
typedef struct hash
{
	int key;
}hashtable[16];//�����ϣ��ṹ��
void creat(hashtable &ht,int arr[])
{
	float sum = 0;
	int i = 0;
	int m = 0;
	int n = 0;
	int j = 0;
	cout << "�������ϣ��Ԫ�ظ���" << endl;
	cin >> m;
	for (i = 0; i < m; i++)
	{
		cout << "�������ϣ���Ԫ��" << endl;
		cin >> arr[i];
	}//�ѹ�ϣ��Ԫ�ش�������
	for (i = 0; i < 16; i++)
	{
		ht[i].key = 0;
	}
	for (i = 0; i < m; i++)
	{
		n = arr[i] % 13;//δ������ͻʱ��ϣ��Ĵ���
		if (ht[n].key == 0)
		{
			ht[n].key = arr[i];
			sum++;
		}
		else//������ͻʱʹ������̽�ⷨ�����ͻ
		{
			for (j = n ; j < 15; j++)
			{
				sum++;
				if (ht[j].key == 0)
				{
					ht[j].key = arr[i];
					break;
				}
			}
		}
	}
	sum = sum / m;
	cout << "ƽ�����ҳ���Ϊ" << sum << endl;
}
void print(hashtable ht)
{
	int i = 0;
	for (i = 0; i < 16; i++)
	{
		if (ht[i].key != 0)
		{
			cout << ht[i].key << endl;
		}
	}
}
int find(hashtable ht, int key)
{
	int flag= 0;
	int i = 0;
	for (i = 0; i < 16; i++)
	{
		if (ht[i].key == key)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		return i;
	}
	else
	{
		return -1;
	}
}
int main()
{
	hashtable ht;
	int arr[20] = { 0 };
	creat(ht, arr);
	int m = 0;
	cout << "���е�" << endl;
	cout << "211050100305" << endl;
	return 0;
}