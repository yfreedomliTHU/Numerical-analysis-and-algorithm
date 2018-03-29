#include<iostream>
#include<cmath>
using namespace std;

int main(int argc, char* argv[])
{
	double **A;
	int i, j, count = 0;
	int m, n, k;
	cin >> m >> n >> k;
	A = new double*[m];
	for (i = 0; i<m; i++)
		A[i] = new double[n];
	for (i = 0; i<m; i++)
	{
		for (j = 0; j<n; j++)
			A[i][j] = 0;
	}
	int p, q;
	double v;
	while (count != k)
	{
		cin >> p >> q >> v;
		count++;
		A[p-1][q-1] = v;
	}
	double **ATA;//ATA
	ATA = new double*[n];
	for (i = 0; i<n; i++)
		ATA[i] = new double[n];
	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
		{
			ATA[i][j] = 0;
			for (int r = 0; r<m; r++)
				ATA[i][j] += A[r][i] * A[r][j];
		}
	double *b;
	b = new double[m];
	i = 0;
	while (i<m)
	{
		cin >> v;
		b[i] = v;
		i++;
	}

	double *ATb;//ATb
	ATb = new double[n];
	for (i = 0; i<n; i++)
	{
		ATb[i] = 0;
		for (j = 0; j<m; j++)
			ATb[i] += A[j][i] * b[j];
	}

	//高斯消元
	double s;
	for (int i = 0; i < n - 1; i++)
	{
		for (int k = i + 1; k < n; k++)
		{
			s = -ATA[k][i] / ATA[i][i];
			for (int j = i + 1; j < n; j++)
			{
				ATA[k][j] += s*ATA[i][j];
			}
			ATA[k][i] = 0;
			ATb[k] += s*ATb[i];
		}
	}

	//回代
	double *x = new double[n];
	for (int i = n - 1; i >= 0; i--)
	{
		s = ATb[i];
		for (int k = i + 1; k<n; k++)
		{
			s -= ATA[i][k] * x[k];
		}
		x[i] = s / ATA[i][i];
	}
	for (i = 0; i < n; i++)//输出结果
		cout << x[i] << endl;
	double X = 0;
	double *Ax=new double[m];
	for (i = 0; i <m; i++)
	{
		Ax[i] = 0;
		for (j = 0; j < n; j++)
		{
			Ax[i] += A[i][j] * x[j];
		}
		X += (b[i] - Ax[i])*(b[i] - Ax[i]);
	}
	cout << X << endl;
	delete[]Ax;
	delete[]x;
	delete[]b;
	for (i = 0; i<m; i++)
		delete[]A[i];
	delete[]ATb;
	for (i = 0; i<n; i++)
		delete[]ATA[i];
	system("pause");
	return 0;
}
