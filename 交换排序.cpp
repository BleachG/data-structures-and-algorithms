//#include <iostream>
//using namespace std;
//void bubblesort(int arr[],int n)
//{
//	int i, j= 0;
//	int flag = 1;//������Ǹ��������Ƿ񽻻���û���������
//	int m = n - 1;
//	while ((m>0)&&flag==1)
//	{
//		flag = 0;//����û�н����������
//		for (i = 0; i < n - 1; i++)
//		{
//			if (arr[i + 1] < arr[i])//2 2���ڽ���
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
//	int temp = arr[low];//tempΪ����Ԫ��
//	while (low < high)
//	{
//		while (low < high && arr[high] >= temp)//�����ҵ�������С��Ԫ��
//		{
//			high--;
//		}
//		arr[low] = arr[high];
//		while (low < high && arr[low] <=temp)//�����ұ�������Ԫ��
//		{
//			low++;
//		}
//		arr[high] = arr[low];
//	}
//	arr[low] = temp;//ѭ������low����highΪ����λ��
//	return low;
//}
//void quicksort(int arr[], int low, int high)
//{
//	if (low < high)
//	{
//		int mid = findmind(arr, low, high);//��������
//		quicksort(arr, low, mid - 1);//��������ݹ�����
//		quicksort(arr, mid+1, high);//�������ҵݹ�����
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