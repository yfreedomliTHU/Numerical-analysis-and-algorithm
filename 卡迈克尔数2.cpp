#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
bool isprime(int n)
{
	for (int i = 2; i <= sqrt(n); i++)
		if (n%i == 0) return false;
	return true;
}
bool judge(int sum,const long pri[], long n)
{
	if (sum < 3)
		return false;
	else
	{
		for (int i = 0; (i < sum)&&(pri[i]<n); i++)
		{
			if ((n - 1) % (pri[i] - 1) != 0)
				return false;
		}
		return true;
	}
}
int main()
{
	long N;
	cin >> N;
	int count = 0;
	int flag = 0;
	long primelist[1000];
	long pri[50];
	long arr[300];
	vector<long>array(N);
	for (int i = 3; i < 1000; i++)
	{
		if (isprime(i))
		{
			primelist[flag] = i;
			flag++;
		}
	}
	for (long i = 3; i < N; i++)
	{
		if ((isprime(i)==false)&&(i%2!=0))
		{
			int sum = 0;
			for (int j = 0; (j < flag)&&(primelist[j]<i); j++)
			{
				if (i%primelist[j] == 0)
				{
					if (i % (primelist[j] * primelist[j]) == 0)
						break;
					pri[sum] = primelist[j];
					sum++;
				}
			}
			if (judge(sum, pri, i) == true)
			{
				arr[count] = i;
				count++;
			}
		}
	}
	cout << count << endl;
	for (int i = 0; i < count; i++)
		cout << arr[i] << endl;
	system("pause");
	return 0;
}