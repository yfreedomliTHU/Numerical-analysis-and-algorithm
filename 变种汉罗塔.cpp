#include <iostream>
#include <vector>
using namespace std;
int main()
{
	long long int N, M;
	cin >> N >> M;
	//vector<long>a;
	//vector<long>f;
	//vector<long>b;
	long long *a = new long long[N+1];
	long long *b = new long long[N + 1];
	long long *f = new long long[N + 1];
	for (int i = 1; i <= N; i++)
		cin >> a[i];
	for (int i = 1; i <= N; i++)
	{
		if (i == 1)
		{
			b[i] = a[i]%M;
			f[i] = (2 * a[i] - 1)%M;
		}
		else
		{
			b[i] = (2 * b[i - 1] + a[i]%M)%M;
			if (a[i] == 1)
			{
				f[i] = b[i];
			}
			else
			{
				f[i] = (2 * b[i - 1] + f[i - 1] + 2 * a[i]%M)%M;
			}
		}
	}
	cout << f[N] % M << endl;
	delete []a;
	delete []b;
	delete []f;
	//system("pause");
	return 0;
}