#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int maxnum = 400;
const int maxint = 999999;
int re[maxnum] = { 0 };
int c[maxnum][maxnum];
int n, line;

typedef struct {
	int dist[maxnum];
	int c[maxnum][maxnum];
}Strt;

typedef struct {
	int index;
	int value;
}CoupleInt;

void swapCI(CoupleInt t[], int i, int j) {
	CoupleInt temp = t[i];
	t[i] = t[j];
	t[j] = temp;
}

void Dijkstra(int n, int v, int *dist, vector<int> *prev, int c[maxnum][maxnum])
{
	bool s[maxnum];
	for (int i = 0; i < n; ++i)
	{
		dist[i] = c[v][i];
		s[i] = 0;
		if (dist[i] < maxint)
			prev[i].push_back(v);
	}
	dist[v] = 0;
	s[v] = 1;

	for (int i = 1; i < n; ++i)
	{
		int tmp = maxint;
		int u = v;

		for (int j = 0; j < n; ++j)
			if ((!s[j]) && dist[j] < tmp)
			{
				u = j;
				tmp = dist[j];
			}
		s[u] = 1;

		for (int j = 0; j < n; ++j)
			if ((!s[j]) && c[u][j] < maxint)
			{
				int newdist = dist[u] + c[u][j];
				if (newdist <= dist[j])
				{
					if (newdist < dist[j]) {
						prev[j].clear();
						dist[j] = newdist;
					}
					prev[j].push_back(u);
				}
			}
	}
}

void searchPath(vector<int> *prev, int v, int u, int sta[], int len, int t) {
	if (u == v) {
		return;
	}
	sta[len] = u;
	for (int i = 0; i < prev[u].size(); ++i) {
		if (i > 0) {
			for (int j = len - 1; j >= 0; --j) {
				if (sta[j] != t) {
					re[sta[j]]++;
				}
			}
		}
		searchPath(prev, v, prev[u][i], sta, len + 1, t);
		if (u != t) {
			re[u]++;
		}
	}
}

int main() {

	cin >> n;

	cin >> line;
	int p, q, len;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			c[i][j] = maxint;

	for (int i = 0; i < line; ++i)
	{
		cin >> p >> q >> len;
		if (len < c[p][q])
		{
			c[p][q] = len;
			c[q][p] = len;
		}
	}

	for (int i = 0; i < n; i++) {
		int dist[maxnum];
		for (int i = 0; i < n; ++i)
			dist[i] = maxint;
		vector<int> prev[maxnum];
		Dijkstra(n, i, dist, prev, c);
		for (int j = i + 1; j < n; j++) {
			int sta[maxnum];
			searchPath(prev, i, j, sta, 0, j);
		}
	}

	CoupleInt ci[maxnum];
	for (int i = 0; i < n; i++) {
		CoupleInt temp;
		temp.index = i;
		temp.value = re[i];
		ci[i] = temp;
	}

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (ci[i].value < ci[j].value)
				swapCI(ci, i, j);
			else if (ci[i].value == ci[j].value && ci[i].index > ci[j].index)
				swapCI(ci, i, j);
		}
	}

	for (int i = 0; i < n; i++)
		cout << ci[i].index << " " << ci[i].value << endl;
	//system("pause");
	return 0;
}