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
	cout << "��������Ҫ�жϵ���������";
	int a, b;
	cin >> a >> b;
	if (check(a, b) == 0)
		cout << a << "��" << b << "������" << endl;
	else
		cout << a << "��" << b << "����" << endl;
	system("pause");
	return 0;
}