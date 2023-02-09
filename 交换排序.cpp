//#include <iostream>
//using namespace std;
//void bubblesort(int arr[],int n)
//{
//	int i, j= 0;
//	int flag = 1;//用来标记该躺排序是否交换，没有排序结束
//	int m = n - 1;
//	while ((m>0)&&flag==1)
//	{
//		flag = 0;//本堂没有交换排序结束
//		for (i = 0; i < n - 1; i++)
//		{
//			if (arr[i + 1] < arr[i])//2 2相邻交换
//			{
//				flag = 1;
//				int temp = arr[i];
//				arr[i] = arr[i + 1];
//				arr[i + 1] = temp;
//			}
//		}
//		m--;
//	}
//}
//int findmind(int arr[], int low, int high)
//{
//	int temp = arr[low];//temp为枢轴元素
//	while (low < high)
//	{
//		while (low < high && arr[high] >= temp)//从右找到比枢轴小的元素
//		{
//			high--;
//		}
//		arr[low] = arr[high];
//		while (low < high && arr[low] <=temp)//从左找比枢轴大的元素
//		{
//			low++;
//		}
//		arr[high] = arr[low];
//	}
//	arr[low] = temp;//循环结束low或者high为枢轴位置
//	return low;
//}
//void quicksort(int arr[], int low, int high)
//{
//	if (low < high)
//	{
//		int mid = findmind(arr, low, high);//返回枢轴
//		quicksort(arr, low, mid - 1);//对枢轴左递归排序
//		quicksort(arr, mid+1, high);//对枢轴右递归排序
//	}
//}
//void print(int arr[], int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		cout << arr[i] << " ";
//	}
//}
//int main()
//{
//	int arr[8] = { 49,38,65,97,76,13,27,50 };
//	quicksort(arr, 0, 7);
//	print(arr, 8);
//	return 0;
//}