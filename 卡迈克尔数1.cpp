#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
bool judge(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
		if (n%i == 0) return false;
	return true;
}
int main()
{
	int k, N;
	cin >> N;
	int sum=0;
	int count = 0;
	/*int *array = new int[N];
	int *arr = new int[N];*/
	vector <int> array(N);
	vector <int> arr(N);
	for (int i = 3; i < N; i++)
	{
		if (judge(i))
		{
			array[sum] = i;
			sum++;
		}
	}
	for (int i = 0; i < sum-2; i++)
	{
		for (int j=i+1;j<sum-1; j++)
		{
			for (int k = j+1; array[i] * array[j] * array[k] <=N && k<sum; k++)
			{
				int temp = array[i] * array[j] * array[k];
				if (((temp - 1) % (array[i] - 1) == 0 )&& ((temp - 1) % (array[j] - 1) == 0) && ((temp - 1) % (array[k] - 1) == 0))
				{
					arr[count] = temp;
					count++;
				}
			}
		}
	}
	cout << count << endl;
	for (int i = 0; i < count; i++)
		cout << arr[i] << endl;
	/*delete[]arr;
	delete[]array;*/
	system("pause");
	return 0;
}