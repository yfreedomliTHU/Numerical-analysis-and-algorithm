#include <iostream>
using namespace std;
bool check2(int max, int min);
bool check(int m, int n)
{
	return check2(m > n ? m : n, m <= n ? m : n);
}
bool check2(int max, int min)
{
	int mo = max % min;
	if (mo == 0)  return min == 1 ? true : false;
	else  return check2(min, mo);
}
int main()
{
	cout << "请输入需要判断的两个数：";
	int a, b;
	cin >> a >> b;
	if (check(a, b) == 0)
		cout << a << "与" << b << "不互质" << endl;
	else
		cout << a << "与" << b << "互质" << endl;
	system("pause");
	return 0;
}