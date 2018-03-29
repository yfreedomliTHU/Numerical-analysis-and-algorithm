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
	int len;//�����н�����  
	Node<Type>* Head; //ָ��ͷ���  
public:
	Circlist();//Ĭ�Ϲ��캯��  
	~Circlist();
	void createBackward(const int m);//β�巨  
	void initList();//����ͷ��㣬β������ΪNULL  
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
Circlist<Type>::Circlist() //��ʼ��ʱ��ֻ��һ��ͷ��㣬��headָ��  
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
void Circlist<Type>::createBackward(const int m)//β�巨  
{
	Node<Type>* current = Head;//currentָ��ͷ���  
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
void Circlist<Type>::initList() //ֻʣ��ͷ��㣬��ָ������  
{
	destoryList();//���н�㶼���٣����ؽ�ͷ���  
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
void Circlist<Type>::destoryList()//���ٰ���ͷ���  
{
	Node<Type>* current;
	Node<Type>* temp;
	if (Head != NULL)//��������ҲҪ��������������Ҫ�ж�ͷ�ǲ���Ϊ�գ�Ϊ�ձ�ʾ�Ѿ��ͷ�  
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
		cout << "����λ�ò���ȷ!" << endl;
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
	Node<Type>* current = Head->next;//currentָ���һ��λ�ã���i��ϣ�ָ���i�����  
	if (pos<1 || pos>len)
	{
		cout << "����λ�ò���ȷ!" << endl;
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
		cout << "ɾ��λ�ò���ȷ!" << endl;
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
	cout << "Running time is: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1000 << "ms" << endl;//�������ʱ��
	system("pause");
	return 0;
}
