#include <iostream>
#include <algorithm>
using namespace std;

struct node
{
	int sum;
	int begin;
	int end;
};
node *get_max(int *arr,int begin, int end, node *max)
{
	node *max_temp = new node;
	max->sum = arr[begin];
	max->begin = begin;
	max->end = begin;
	max_temp->begin = max->begin;
	max_temp->end = max->end;
	max_temp->sum = max->sum;
	for (int i = begin+1; i <= end; i++)
	{
		if (max_temp->sum <= 0)
		{
			if (arr[i]>0)
			{
				max_temp->end = i;
				max_temp->begin = i;
				max_temp->sum = arr[i];
				
			}
		}
		else
		{
			max_temp->sum += arr[i];
			max_temp->end = i;
		}
		if (max_temp->sum>max->sum || (max_temp->sum == max->sum && (max_temp->end - max_temp->begin) < (max->end - max->begin)))
		{
			max->end = max_temp->end;
			max->begin = max_temp->begin;
			max->sum = max_temp->sum;
		}
	}
	return max;
}
node *get_min(int*arr, int begin, int end, node *min)
{
	node *min_temp = new node;
	min->sum = arr[begin];
	min->begin = begin;
	min->end = begin;
	min_temp->begin = min->begin;
	min_temp->end = min->end;
	min_temp->sum = min->sum;
	for (int i = begin + 1; i <= end; i++)
	{
		if (min_temp->sum > 0)
		{
			if (arr[i]<0)
			{
				min_temp->end = i;
				min_temp->begin = i;
				min_temp->sum = arr[i];

			}
		}
		else
		{
			min_temp->sum += arr[i];
			min_temp->end = i;
		}
		if (min_temp->sum<min->sum || (min_temp->sum == min->sum && (min_temp->end - min_temp->begin) > (min->end - min->begin)))
		{
			min->end = min_temp->end;
			min->begin = min_temp->begin;
			min->sum = min_temp->sum;
		}
	}
	return min;
}

int main()
{
	int a, b, c, d;
	int i, length, max, Max;
	cin >> length;
	int *arr = new int[length];
	int sum1 = 0;
	for (i = 0; i < length; i++)
	{
		cin >> arr[i];
		sum1 = sum1 + arr[i];
	}
	node *max1 = new node;
	max1 = get_max(arr, 0, length - 1,max1);
	node *min1 = new node;
	min1 = get_min(arr,0,length-1,min1);
	int max2= sum1 - min1->sum;
	if (max1->sum > max2)
	{
		max = max1->sum;
		a = max1->begin;
		b = max1->end;
	}
	else if (max1->sum == max2)
	{
		if ((max1->end - max1->begin + 1) < (length - min1->end + min1->begin - 1))
		{
			max = max1->sum;
			a = max1->begin;
			b = max1->end;
		}
		else
		{
			max = max2;
			a = min1->begin - 1;
			b = min1->end + 1;
		}
	}
	else
	{
		max = max2;
		a = min1->begin - 1;
		b = min1->end + 1;
	}
	node *Max1 = new node;
	if (a==min1->begin-1)
	{
		Max1 = get_max(arr, a + 1, b - 1, Max1);
		c = Max1->begin;
		d = Max1->end;
		Max = Max1->sum;
	}
	else if(a==max1->begin)
	{
		int temp = length - (b - a + 1);
		int *arr1 = new int[temp];
		for (i = 0; i < length - b; i++)
			arr1[i] = arr[b + i];
		for (i = length - b; i < temp; i++)
			arr1[i] = arr[i - length + b];
		Max1 = get_max(arr1, 0, temp - 1, Max1);
		if (Max1->begin < length - b)
			Max1->begin = Max1->begin + b;
		else
			Max1->begin = Max1->begin - length + b;
		if (Max1->end < length - b)
			Max1->end = Max1->end + b;
		else
			Max1->end = Max1->end - length + b;
		c = Max1->begin;
		d = Max1->end;
		Max = Max1->sum;
	}
	node *max_min = new node;
	if (a==min1->begin-1)
	{
		int temp1 = length - b + a + 1;
		int *arr2 = new int[temp1];
		for (i = 0; i < length - b; i++)
			arr2[i] = arr[b + i];
		for (i = length - b; i < temp1; i++)
			arr2[i] = arr[i - length + b];
		max_min = get_min(arr2, 0, temp1 - 1, max_min);
		if (max_min->begin < length - b)
			max_min->begin = max_min->begin + b;
		else
			max_min->begin = max_min->begin - length + b;
		if (max_min->end < length - b)
			max_min->end = max_min->end + b;
		else
			max_min->end = max_min->end - length + b;
	}
	else if(a==max1->begin)
	{
		max_min = get_min(arr, max1->begin, max1->end, max_min);
	}
	if ((max - max_min->sum) >= (max + Max))
	{
		cout << max - max_min->sum << endl;
		c = max_min->begin - 1;
		d = max_min->end + 1;
	}
	else
		cout << max + Max << endl;
	int point[4] = { a,b,c,d };
	sort(point, point + 4);
	for (int i = 0; i < 4; i++)
		cout << point[i] << " ";
	delete []arr;
	//system("pause");
	return 0;
}