#include <stdio.h>
#include <iostream>
using namespace std;

class MyData
{
public:
	MyData()
	{
		key1 = key2 = 0;
	}

	int key1;
	int key2;
};

class MySearchTree
{
public:
	struct TreeNode
	{
		MyData element;
		TreeNode *left;
		TreeNode *right;
		int cur_layer;

		TreeNode() :cur_layer(0), left(NULL), right(NULL) {}
		TreeNode(const MyData &theElement, int tree_cur_layer, TreeNode *It, TreeNode *rt)
			:cur_layer(tree_cur_layer), element(theElement), left(It), right(rt) {}
	};

	MySearchTree();
	//MySearchTree(const MySearchTree & rhs);
	~MySearchTree();

	int getNodeNum(int low1, int high1, int low2, int high2) const;

	void Clear();
	void insert(const MyData & x);

private:
	TreeNode *root;

	void insert(const MyData & x, TreeNode * & t, int cur_layer) const;
	int getNodeNum(TreeNode *t, int low1, int high1, int low2, int high2) const;
	int dataCompare(const MyData &data1, const MyData &data2, int cur_layer) const;
	void deleteNode(TreeNode * &t);
};

MySearchTree::MySearchTree() {
	root = NULL;
}

MySearchTree::~MySearchTree()
{
	Clear();
}

void MySearchTree::Clear()
{
	deleteNode(root);
}


int MySearchTree::getNodeNum(int low1, int high1, int low2, int high2) const
{
	return getNodeNum(root, low1, high1, low2, high2);
}

int MySearchTree::getNodeNum(MySearchTree::TreeNode * t,
	int low1, int high1, int low2, int high2) const
{
	if (t == NULL)
		return 0;
	else
	{
		MyData low, high;
		low.key1 = low1;
		low.key2 = low2;
		high.key1 = high1;
		high.key2 = high2;

		if (dataCompare(t->element, low, t->cur_layer) < 0)
		{
			return getNodeNum(t->right, low1, high1, low2, high2);
		}
		else if (dataCompare(high, t->element, t->cur_layer) < 0)
		{
			return getNodeNum(t->left, low1, high1, low2, high2);
		}
		else
		{
			int cur = 0;
			if (dataCompare(t->element, low, t->cur_layer + 1) >= 0 && dataCompare(t->element, high, t->cur_layer + 1) <= 0)
				cur = 1;

			return cur + getNodeNum(t->left, low1, high1, low2, high2) + getNodeNum(t->right, low1, high1, low2, high2);
		}
	}
}

void MySearchTree::insert(const MyData & x)
{
	insert(x, root, 0);
}

void MySearchTree::insert(const MyData &x, TreeNode *&t, int cur_layer) const
{
	if (t == NULL)
		t = new TreeNode(x, cur_layer, NULL, NULL);
	else if (dataCompare(x, t->element, cur_layer) < 0)
		insert(x, t->left, cur_layer + 1);
	else
		insert(x, t->right, cur_layer + 1);
}

void MySearchTree::deleteNode(TreeNode * &t)
{
	if (t != NULL)
	{
		deleteNode(t->left);
		deleteNode(t->left);
		delete t;
	}

	t = NULL;
}

int MySearchTree::dataCompare(const MyData &data1, const MyData &data2, int cur_layer) const
{
	if (cur_layer % 2 == 0)
	{
		if (data1.key1 < data2.key1)
			return -1;
		else if (data1.key1 > data2.key1)
			return 1;
		else
			return 0;
	}
	else
	{
		if (data1.key2 < data2.key2)
			return -1;
		else if (data1.key2 > data2.key2)
			return 1;
		else
			return 0;
	}
}

int main()
{
	int m, n,type;
	cin >> m >> n;
	int read_num = 0;
	int search_num = 0;
	int count = 0;
	int *result = new int[m];
	int low1, high1, low2, high2;

	MySearchTree MyTree;
	MyData data;
	do
	{
		cin >> type;
		if (type == 0)
		{
			cin >> data.key1 >> data.key2;
			MyTree.insert(data);
		}
		else if(type ==1)
		{
			cin >> low1 >> high1 >> low2 >> high2;
			search_num = MyTree.getNodeNum(low1, high1, low2, high2);
			//cout << search_num << endl;
			result[count] = search_num;
			count++;
		}
	read_num++;
	} while (read_num != n + m);
	for (int i = 0; i < count; i++)
		cout << result[i]<<endl;
	delete[]result;
	//system("pause");
	return 0;

}