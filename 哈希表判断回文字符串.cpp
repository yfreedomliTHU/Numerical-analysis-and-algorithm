#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
using namespace tr1;
bool isPalin(string& str,int begin,int end)
{
	while (begin < end)
	{
		if (str[begin] != str[end])
			return false;
		begin++;
		end--;
	}
	return true;
}

int main() 
{
	unordered_map<string, int> word_hash;
	vector<vector<int> > ffshit;
	int m, n;
	cin >> m >> n;
	vector<string> words(m + 1);
	for (int i = 0; i<m; i++)
	{
		string temp_result;
		cin >> temp_result;
		word_hash[temp_result] = i;
		words[i] = temp_result;
	}
	for (int i = 0; i<m; i++) 
	{
		for (int j = 0; j<m; j++) 
		{
			if (i != j) 
			{
				string base_string = words[i] + words[j];
				for (int k = 0; k<base_string.size(); k++) 
				{
					int str_len = base_string.size();
					if (isPalin(base_string, k, str_len - 1))
					{
						string left_string = base_string.substr(0, k);
						reverse(left_string.begin(), left_string.end());
						if (word_hash.count(left_string))
						{
							int index = word_hash[left_string];
							if (index != i&&index != j)
							{
								vector<int> p_temp;
								p_temp.push_back(i);
								p_temp.push_back(j);
								p_temp.push_back(word_hash[left_string]);
								ffshit.push_back(p_temp);
							}
						}
					}
					if (isPalin(base_string, 0, k - 1))
					{
						string right_string = base_string.substr(k);
						reverse(right_string.begin(), right_string.end());
						if (word_hash.count(right_string))
						{
							int index = word_hash[right_string];
							if (index != i&&index != j)
							{
								vector<int> p_temp;
								p_temp.push_back(word_hash[right_string]);
								p_temp.push_back(i);
								p_temp.push_back(j);
								ffshit.push_back(p_temp);
							}
						}
					}
				}
			}
		}
	}
	sort(ffshit.begin(), ffshit.end());
	//sort(vec.begin(), vec.end());
	vector<vector<int> >::iterator iter = unique(ffshit.begin(), ffshit.end());
	ffshit.erase(iter, ffshit.end());
	cout << ffshit.size() << endl;
	for (int i = 0; i<ffshit.size(); i++) 
	{
		for (int j = 0; j<3; j++) 
		{
			cout << ffshit[i][j] << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}