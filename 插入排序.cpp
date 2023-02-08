#include <iostream>
using namespace std;
void directinset(int arr[],int n)
{
	int i = 0;
	int j = 0;
	int temp = 0;
	for (i = 1; i < n; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			temp = arr[i];
			arr[i] = arr[i - 1];
			for (j = i - 2; temp < arr[j]&&j>=0; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[j+1] = temp;
		}
	}
 }
void twodividesort(int arr[], int n)
{
	int i = 0;
	int j = 0;
	int temp = 0;
	for (i = 1; i <n; i++)
	{
		temp = arr[i];//待插入节点
		int low = 0;//待插入节点前区间的low
		int high = i - 1;//待插入节点前区间的high
		while (low <= high)
		{//找到待插入节点的插入位置
			int mid = (low + high) / 2;
			if (temp < arr[mid])
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		for (j = i - 1; j >= high + 1; j--)//区间范围数组后移
		{
			arr[j + 1] = arr[j];
		}
		arr[high + 1] = temp;//把待插入节点赋值
	}
}
void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
}
void shellsort(int arr[],int m,int n)
{
	int i = 0;
	int temp = 0;
	int j = 0;
	for (i = m; i< n; i++)
	{
		if (arr[i] < arr[i - m])
		{
			temp = arr[i];
			for (j = i - m; j >=0 && temp<arr[j] ; j -= m)
			{
				arr[j + m] = arr[j];
			}
			arr[j + m] = temp;
		}
	}
}
void shelldt(int dt[],int arr[],int n,int t)
{
	int i = 0;
	for (i = 0; i < t; i++)
	{
		shellsort(arr, dt[i], n);
	}
}
int main()
{
	int arr[8] = { 49,38,65,97,76,13,27,50 };
	int dt[3] = { 5,3,1 };
	shelldt(dt, arr, 8, 3);
	print(arr, 8);
	return 0;
}