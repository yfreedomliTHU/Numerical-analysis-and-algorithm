#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

int main()
{
	int M;
	cin >> M;
	for (int i = 0; i < M; i++)
	{
		int N;
		cin >> N;
		double sumA = 0.0, correction = 0.0, corrected_next_term, new_sum;;
		double Anmax1 = 0.0;
		double Anmin1 = 0.0;
		double Anmax2 = 0.0;
		double Anmin2 = 0.0;
		double An;
		double s;
		double n2;
		if (N <= 150000)
		{
			for (int n = 1; n <= N; n++)
			{
				if (n <= 10000)
				{
					n2 = n*n;
					s = (sqrt(n2 + 1.0) + sqrt(n2 - 1.0)) / 2.0;//s>=1/s
					Anmax1 += s;
					Anmin1 += 1.0 / s;
				}
				else if ((n >= 10000) && (n<100000))
				{
					Anmax1 += n;
					Anmin1 += 1.0 / n;
				}
				else
				{
					n2 = n*n;
					s = (sqrt(n2 + 1.0) + sqrt(n2 - 1.0)) / 2.0;
					Anmax2 += s;
					Anmin2 += 1.0 / s;
				}
			}
			sumA += Anmax1 + Anmin1 + Anmax2 + Anmin2;
		}
		else
		{
			sumA = 6.7767683758104091e-01 + 100000.0*double(100000.0 + 1.0) / 2.0 + log(double(N));
		}
		printf("%.12e\n", sumA);
	}
	return 0;
}