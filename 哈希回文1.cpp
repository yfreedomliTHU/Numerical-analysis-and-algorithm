#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
//bool if a string is huiwen
bool is_huiwen(char *p)
{
	int j = strlen(p);
	for (int i = 0, q = j - 1; i<q; i++, q--)
	{
		if (p[i] != p[q])
			return false;
	}
	return  true;
}
//store the numbers of the datas(store*next is not neccessary)
class store
{
public:
	int a;
	int b;
	int c;
	store *next;
	store() { a = b = c = 0; next = NULL; }
	store(int x, int y, int z) { a = x; b = y; c = z; next = NULL; }
};
//create a linklist to store the order of datas
//can use vector to store it, too
class link
{
public:
	store *head;
	store *pre;
	int size;
	link() { head = NULL; size = 0; }
	void adddata(int x, int y, int z);
};
void link::adddata(int x, int y, int z)
{
	if (!head)
	{
		head = new store(x, y, z);
		pre = head;
		size++;
	}
	else
	{
		store *p = new store(x, y, z);
		pre->next = p;
		pre = p;
		size++;
	}
}
//store the disorder of the string
char* disorder(char *b)
{
	char *c;
	int n = strlen(b);
	c = new char[n + 3];
	for (int i = 0; i<n; i++)
	{
		c[i] = b[n - 1 - i];
	}
	c[n] = '\0';
	return c;
}
//store datas
class hash_data
{
public:
	int number;
	char* order;
	char* dis;
	int feature;
	//feature = 211*(ascii)dis[0]+199*dis[1]+229*dis[3];
	bool is_two;
	//if the string has only two char, mark it
	hash_data() { number = -1; is_two = false; }
	hash_data(int n) { number = n; is_two = false; }
	void inputstring(char* a, int n) { order = a; dis = new char[n]; dis = disorder(order); }
	void culfeature();
};
void hash_data::culfeature()
{
	int n = strlen(dis);
	if (n == 2)
	{
		feature = 211 * int(dis[0]) + 199 * int(dis[1]);
		is_two = true;
	}
	else
	{
		feature = 211 * int(dis[0]) + 199 * int(dis[1]) + 229 * dis[2];
	}
}
//the following is the hash_storage, use prt to store the adress of datas.
class hash_store
{
public:
	hash_data *p;
	hash_store() { p = NULL; }
};
//compare function used in sort
bool cmp(store &a, store &b)
{
	if (a.a<b.a)
		return true;
	else if (a.a == b.a && a.b<b.b)
		return true;
	else if (a.a == b.a && a.b == b.b &&a.c<b.c)
		return true;
	else
		return false;
}

int main()
{
	//cout<<"please input:";
	int M, N;
	cin >> M >> N;
	//max can be larger
	int max = 5 * M;
	hash_data *data = new hash_data[M];
	hash_store *sto = new hash_store[max];
	link result;
	//create datas;
	for (int i = 0; i<M; i++)
	{
		char *p = new char[N + 1];
		cin >> p;
		data[i].inputstring(p, N + 1);
		data[i].culfeature();
		data[i].number = i;
	}
	//create hash table
	for (int j = 0; j<M; j++)
	{
		int l = data[j].feature%max;
		while (1)
		{
			if (!sto[l].p)
			{
				sto[l].p = &data[j];
				break;
			}
			l = (l + 1) % max;
		}
	}
	char *a = new char[2 * N + 2];
	char *b = new char[3 * N + 2];
	for (int i = 0; i<M; i++)
	{
		for (int j = 0; j<M; j++)
		{
			if (i != j)
			{

				a[0] = '\0';
				strcat(a, data[i].order);
				strcat(a, data[j].order);
				int FEA = (int(a[0]) * 211 + int(a[1]) * 199 + int(a[2]) * 229) % (max);
				int copy = FEA;
				//find the suit datas.
				while (1)
				{
					if (!sto[copy].p)
						break;
					if (sto[copy].p->feature % (max) == FEA && sto[copy].p->number != i && sto[copy].p->number != j && !sto[copy].p->is_two)
					{
						b[0] = '\0';
						strcat(b, a);
						strcat(b, sto[copy].p->order);
						if (is_huiwen(b))
							result.adddata(i, j, sto[copy].p->number);
					}
					copy = (copy + 1) % max;
				}
				int len;
				len = strlen(a);
				a[len] = a[1];
				a[len + 1] = a[0];
				a[len + 2] = '\0';
				if (is_huiwen(a))
				{
					FEA = (211 * int(a[0]) + 199 * int(a[1])) % (max);
					int copy = FEA;
					while (1)
					{
						if (!sto[copy].p)
							break;
						if (sto[copy].p->is_two &&sto[copy].p->dis[0] == a[0] && sto[copy].p->dis[1] == a[1] && sto[copy].p->number != i &&sto[copy].p->number != j)
						{
							result.adddata(i, j, sto[copy].p->number);
							break;
						}
						copy = (copy + 1) % max;
					}
				}
			}
		}
	}
	int number = result.size;
	cout << number << endl;
	store *xxx = new store[number];
	result.pre = result.head;
	for (int j = 0; j<number; j++)
	{
		xxx[j].a = result.pre->a;
		xxx[j].b = result.pre->b;
		xxx[j].c = result.pre->c;
		result.pre = result.pre->next;
	}
	sort(xxx, xxx + number, cmp);
	for (int k = 0; k<number; k++)
	{
		cout << xxx[k].a << " " << xxx[k].b << " " << xxx[k].c << endl;
	}
	return 0;
}
