#include <iostream>
using namespace std;
void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
			cout << arr[i] << " ";
	}
}
void mergesort(int arr[],int a_rr[],int low,int high)
{
	if (low >= high)//归并完成退出
	{
		return;
	}
	int mid = (low + high) / 2;//找到中间值
	mergesort(arr, a_rr, low, mid);//分别对2个区间递归排序
	mergesort(arr, a_rr, mid + 1, high);
	int i = low;
	int m = 0;
	int j = mid + 1;
	while (i<= mid && j <= high)//找到其中最小值将其并入临时存储空间
	{
		if (arr[i] < arr[j])
		{
			a_rr[m] = arr[i];
			i++;
			m++;
		}
		else
		{
			a_rr[m] = arr[j];
			j++;
			m++;
		}
	}
	//把剩下没有遍历的并入临时空间
	while (i <= mid)
	{
		a_rr[m] = arr[i];
		i++;
		m++;
	}
	while (j <= high)
	{
		a_rr[m] = arr[j];
		j++;
		m++;
	}
	//把临时空间值拷贝到原数组
	for (int k = 0; k < m; k++)
	{
		arr[low + k] = a_rr[k];
	}
}
int main()
{
	int arr[8] = { 49,38,65,97,76,13,27,50 }; 
	int brr[8] = { 0 };
	mergesort(arr, brr, 0, 7);
	print(arr, 8);
	return 0;
}