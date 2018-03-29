#include <iostream> 
#include <time.h>
using namespace std;
template<class Type>
struct Node
{
	Type data;
	Node<Type> *next;
};
template<class Type>
class Circlist
{
protected:
	int len;//链表中结点个数  
	Node<Type>* Head; //指向头结点  
public:
	Circlist();//默认构造函数  
	~Circlist();
	void createBackward(const int m);//尾插法  
	void initList();//生成头结点，尾部设置为NULL  
	bool isEmptyList();
	int  length();
	void destoryList();
	void insertBefore(const int pos, const Type newItem);
	void insertAfter(const int pos, const Type newItem);
	void deleteNode(const int pos);
	int getelem(const int pos);
	int judge(int M);
};

template<class Type>
Circlist<Type>::Circlist() //初始化时，只有一个头结点，由head指向  
{
	Head = new Node<Type>;
	Head->next = Head;
	len = 0;
}

template<class Type>
Circlist<Type>::~Circlist()
{
	destoryList();
}

template<class Type>
void Circlist<Type>::createBackward(const int m)//尾插法  
{
	Node<Type>* current = Head;//current指向头结点  
	Node<Type>* newNode;
	len = m;
	for (int i = 0; i<len; i++)
	{
		newNode = new Node<Type>;
		newNode->data = i + 1;
		newNode->next = current->next;
		current->next = newNode;
		current = current->next;
	}
}

template<class Type>
void Circlist<Type>::initList() //只剩下头结点，和指针设置  
{
	destoryList();//所有结点都销毁，在重建头结点  
	Head = new Node<Type>;
	Head->next = Head;
	len = 0;
}

template<class Type>
bool Circlist<Type>::isEmptyList()
{
	if (Head->next == Head)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class Type>
int Circlist<Type>::length()
{
	return len;
}

template<class Type>
void Circlist<Type>::destoryList()//销毁包括头结点  
{
	Node<Type>* current;
	Node<Type>* temp;
	if (Head != NULL)//析构函数也要调这个函数，因此要判断头是不是为空，为空表示已经释放  
	{
		temp = Head;
		current = Head->next;
		while (current != Head)
		{
			delete temp;
			temp = current;
			current = current->next;
		}
		delete temp;
		len = 0;
	}
}

template<class Type>
void Circlist<Type>::insertBefore(const int pos, const Type newItem)
{
	int i = 1;
	Node<Type>* current = Head->next;
	if (pos<1 || pos>len)
	{
		cout << "插入位置不正确!" << endl;
		return;
	}
	Node<Type>* newNode = new Node<Type>;
	newNode->data = newItem;
	if (pos == 1)
	{
		newNode->next = Head->next;
		Head->next = newNode;
	}
	else
	{
		while (i<pos - 1)
		{
			current = current->next;
			i++;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
	len++;
}

template<class Type>
void Circlist<Type>::insertAfter(const int pos, const Type newItem)
{
	int i = 1;
	Node<Type>* current = Head->next;//current指向第一个位置，和i配合，指向第i个结点  
	if (pos<1 || pos>len)
	{
		cout << "插入位置不正确!" << endl;
		return;
	}
	Node<Type>* newNode = new Node<Type>;
	newNode->data = newItem;
	if (pos == len)
	{
		newNode->next = Head->next;
		Head->next = newNode;
	}
	else
	{
		while (i<pos)
		{
			current = current->next;
			i++;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
	len++;
}

template<class Type>
void Circlist<Type>::deleteNode(const int pos)
{
	int i = 1;
	Node<Type>* current = Head;
	Node<Type>* temp;
	if (pos<1 || pos>len)
	{
		cout << "删除位置不正确!" << endl;
		return;
	}
	while (i<pos)
	{
		current = current->next;
		i++;
	}
	temp = current->next;
	current->next = temp->next;
	delete temp;
	temp = NULL;
	len--;
}

template<class Type>
int  Circlist<Type>::getelem(const int pos)
{
	int i = 1;
	Node<Type>* current = Head;
	while (i <= pos)
	{
		current = current->next;
		i++;
	}
	return current->data;
}
template<class Type>
int Circlist<Type>::judge(int M)
{
	Node<Type>* current = Head;
	int i = 1;
	int flag = 0;
	while (i <= len)
	{
		if (current->data <= M)
			flag++;
		current = current->next;
		i++;
	}
	return flag;
}
int main()
{
	Circlist<long> list;
	int N, M, k, tem, tmp;
	cin >> N >> M >> k;
	clock_t start_time = clock();
	{
		list.createBackward(M);
		int count = 0;
		int L = list.length();
		while (L < N)
		{
			if ((count + k) % L == 0)
				tem = L;
			else
				tem = (count + k) % L;
			int num = list.getelem(tem);
			if (num % 2 == 0)
			{
				list.insertAfter(tem, L + 1);
				count = tem;
			}
			else
			{
				list.insertBefore(tem, L + 1);
				count = tem + 1;
			}
			L++;
		}
		int len = list.length();
		while (len > M)
		{
			if ((count + k) % len == 0)
				tmp = len;
			else
				tmp = (count + k) % len;
			list.deleteNode(tmp);
			count = count + k - 1;
			len--;
		}
		cout << list.judge(M) << endl;
	}
	clock_t end_time = clock();
	cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;//输出运行时间
	system("pause");
	return 0;
}
