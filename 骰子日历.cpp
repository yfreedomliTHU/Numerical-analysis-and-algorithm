#include<iostream>
//using namespace std;
int dice[84][6] = { { 0,1,2,3,4,5 },{ 0,1,2,3,4,6 },{ 0,1,2,3,4,7 },{ 0,1,2,3,4,8 },{ 0,1,2,3,5,6 },{ 0,1,2,3,5,7 },{ 0,1,2,3,5,8 },{ 0,1,2,3,6,7 },{ 0,1,2,3,6,8 },{ 0,1,2,3,7,8 },{ 0,1,2,4,5,6 },{ 0,1,2,4,5,7 },{ 0,1,2,4,5,8 },{ 0,1,2,4,6,7 },{ 0,1,2,4,6,8 },{ 0,1,2,4,7,8 },{ 0,1,2,5,6,7 },{ 0,1,2,5,6,8 },{ 0,1,2,5,7,8 },{ 0,1,2,6,7,8 },{ 0,1,3,4,5,6 },{ 0,1,3,4,5,7 },{ 0,1,3,4,5,8 },{ 0,1,3,4,6,7 },{ 0,1,3,4,6,8 },{ 0,1,3,4,7,8 },{ 0,1,3,5,6,7 },{ 0,1,3,5,6,8 },{ 0,1,3,5,7,8 },{ 0,1,3,6,7,8 },{ 0,1,4,5,6,7 },{ 0,1,4,5,6,8 },{ 0,1,4,5,7,8 },{ 0,1,4,6,7,8 },{ 0,1,5,6,7,8 },{ 0,2,3,4,5,6 },{ 0,2,3,4,5,7 },{ 0,2,3,4,5,8 },{ 0,2,3,4,6,7 },{ 0,2,3,4,6,8 },{ 0,2,3,4,7,8 },{ 0,2,3,5,6,7 },{ 0,2,3,5,6,8 },{ 0,2,3,5,7,8 },{ 0,2,3,6,7,8 },{ 0,2,4,5,6,7 },{ 0,2,4,5,6,8 },{ 0,2,4,5,7,8 },{ 0,2,4,6,7,8 },{ 0,2,5,6,7,8 },{ 0,3,4,5,6,7 },{ 0,3,4,5,6,8 },{ 0,3,4,5,7,8 },{ 0,3,4,6,7,8 },{ 0,3,5,6,7,8 },{ 0,4,5,6,7,8 },{ 1,2,3,4,5,6 },{ 1,2,3,4,5,7 },{ 1,2,3,4,5,8 },{ 1,2,3,4,6,7 },{ 1,2,3,4,6,8 },{ 1,2,3,4,7,8 },{ 1,2,3,5,6,7 },{ 1,2,3,5,6,8 },{ 1,2,3,5,7,8 },{ 1,2,3,6,7,8 },{ 1,2,4,5,6,7 },{ 1,2,4,5,6,8 },{ 1,2,4,5,7,8 },{ 1,2,4,6,7,8 },{ 1,2,5,6,7,8 },{ 1,3,4,5,6,7 },{ 1,3,4,5,6,8 },{ 1,3,4,5,7,8 },{ 1,3,4,6,7,8 },{ 1,3,5,6,7,8 },{ 1,4,5,6,7,8 },{ 2,3,4,5,6,7 },{ 2,3,4,5,6,8 },{ 2,3,4,5,7,8 },{ 2,3,4,6,7,8 },{ 2,3,5,6,7,8 },{ 2,4,5,6,7,8 },{ 3,4,5,6,7,8 } };
int **number;     
int *dice_reverse;     
void form_Graph(int  M, int  N)
{
	dice_reverse = new int[N];
	number = new int *[M];
	for (int i = 0; i < M; i++) number[i] = new int[N];
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cin >> number[i][j];
			if (number[i][j] == 9) number[i][j] = 6;
		}
	}
}
bool find_count(int **state, int n)
{
	bool flag = 0;
	for (int a = 0; a < n + 1 && flag == 0; a++)
	{
		for (int b = 0; b < n + 2 && flag == 0; b++)
		{
			for (int c = 0; c < n + 2 && flag == 0; c++)
			{
				for (int d = 0; d < n + 2 && flag == 0; d++)
				{
					for (int e = 0; e < n + 2 && flag == 0; e++)
					{
						for (int f = 0; f < n + 2 && flag == 0; f++)
						{
							int dd[6] = { 0 };
							if (state[0][a] != -1)	dd[state[0][a]]++;
							if (state[1][b] != -1)	dd[state[1][b]]++;
							if (state[2][c] != -1)	dd[state[2][c]]++;
							if (state[3][d] != -1)	dd[state[3][d]]++;
							if (state[4][e] != -1)	dd[state[4][e]]++;
							if (state[5][f] != -1)	dd[state[5][f]]++;
							int count = 0;
							bool flag1 = 1;
							for (int i = 0; i < 6 ; i++)
							{
								count += dd[i];
								if (dd[i] > 1)
								{
									flag1 = 0;
									break;
								}
							}
							if (count == n + 1 && flag1 == 1) return 1;
						}
					}
				}
			}
		}
	}
	return flag;
}

bool Check(int n,int M,int N) //检查 
{
	bool flag = 1;
	for (int i = 0; i < M ; i++) 
	{
		int **state;
		state = new int *[6];//记录状态
		for (int i = 0; i < 6; i++)
		{
			state[i] = new int[6];
			for (int j = 0; j < 6; j++)
			{
				state[i][j] = -1;//表示未被使用
			}
		}
		for (int a = 0; a < n + 1; a++)   
		{
			for (int j = 0; j < N; j++)   
			{
				bool flag = 0;
				for (int k = 0; k < 6 && flag == 0; k++) 
				{
					if (dice[dice_reverse[a]][k] == number[i][j])
					{
						bool flag1 = 0;
						for (int l = 0; l < n + 1 ; l++)
						{
							if (state[j][l] == -1)
							{
								state[j][l] = a; 
								flag1 = 1;
								break;
							}
						}
					}
				}
			}
		}
		flag = find_count(state, n);
		for (int i = 0; i < 6; i++)   delete[]state[i];
		delete[]state;
		if (flag == 0) break;
	}
	return flag;
}

bool PrintRes(int n, int num,int M,int N)
{
	bool flag = 0;
	for (int i = num; i < 84 && flag == 0; i++)
	{
		dice_reverse[n] = i;
		if (Check(n,M,N)) 
		{
			if (n == N - 1) return 1;
			else flag = PrintRes(n + 1, i,M,N);
		}
	}
	return flag;
}
void print(bool flag,int N)
{
	using namespace std;
	if (flag == 0) cout << "NO" << endl;
	else {
		for (int i = 0; i <= N - 1; i++) cout << dice_reverse[i] << " ";
		cout << endl;
	}
}

int main()
{
	int M, N;
	std::cin >> N >> M;
	form_Graph(M, N);
	using namespace std;
	bool flag = PrintRes(0, 0, M, N);
	print(flag, N);
	system("pause");
	return 0;
}