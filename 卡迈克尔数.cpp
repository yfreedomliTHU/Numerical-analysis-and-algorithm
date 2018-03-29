#include <iostream>
#include <cmath>
using namespace std;
int FastM(int a, int p, int m)
{
	if (p == 0) return 1;
	int r = a % m;
	int k = 1;
	while (p > 1)
	{
		if ((p & 1) != 0)
		{
			k = (k * r) % m;
		}
		r = (r * r) % m;
		p >>= 1;
	}
	return (r * k) % m;
}
bool check(int min, int max)
{
	int mo = max % min;
	if (mo == 0)  return min == 1 ? true : false;
	else  return check(mo, min);
}
bool mod(int sum,const int array[],int n)
{
	for (int i = 0; i < sum; i++)
	{
		if (FastM(array[i],n-1,n) != 1)
			return false;
	}
	return true;
}

int main()
{
	int N;
	int count = 0;
	cin >> N;
	int *arr = new int[100];
	for (int i = 3; i <= N; i++)
	{
		int flag = 1;
		int k = sqrt(i);
		for (int j = 2; j <= k; j++)
		{
			if(i%j==0)
			{
				flag = 0;
				break;
			}
		}
		if ((flag==0)&&(i%2!=0))
		{
			if ((i % 3 == 0) || (i % 5 == 0) || (i % 7 == 0) || (i % 11 == 0) || (i % 13 == 0) || (i % 17 == 0) || (i % 41 == 0))
			{
				int *array = new int[i];
				int sum = 0;
				for (int a = 2; a <i; a++)
				{
					if (check(a, i) == true)
					{
						array[sum] = a;
						sum++;
					}
				}
				arr[count] = i;
				count++;
				if (mod(sum, array, i) == true)
				{
					arr[count] = i;
					count++;
				}
				delete[]array;
			}
		}
	}
	
	cout << count << endl;
	for (int i = 0; i < count; i++)
		cout << arr[i] << endl;
	delete [] arr;
	system("pause");
	return 0;
}