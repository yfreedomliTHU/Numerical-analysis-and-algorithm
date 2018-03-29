#include <iostream>  
using namespace std;
typedef int datatype;//方便换数据类型
struct node 
{
	datatype data;
	node *pre;
	node *next;//前驱和后继指针  
};
class DCLink
{
public:
	DCLink(); 
	DCLink(datatype data);  
	void add(datatype data);//添加data到链表中去  
	~DCLink() {}
	int getLength()const;
	int Joseph(datatype n, datatype m, datatype k);
private:
	node *head;//头指针  
	node *cur;//当前指针 
	int size;
};
DCLink::DCLink() 
{
	head = cur = NULL;//默认为空  
	size = 0;
}
DCLink::DCLink(datatype data) 
{ 
	head = new node[1]; 
	cur = head;  
	head->data = data;
	head->next = head->pre = head; 
	size = 1;
}
void DCLink::add(datatype data) 
{ 
	node *dcl = new node[1];
	dcl->data = data;
	if (NULL != head) 
	{
		node *temp = cur->next;
		cur->next = dcl;
		dcl->pre = cur;
		dcl->next = temp;  
		temp->pre = dcl;  
	}
	else 
	{
		head = dcl; 
		head->data = data;
		head->next = head->pre = head;
	}
	cur = dcl;
	size++; 
}

int DCLink::getLength()const {
	return size;
}  
  
int DCLink::Joseph(datatype n, datatype m, datatype k)
{
	node *p = head->pre;
	for (int i = m + 1; i <= n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			p = p->next;
		}
		if ((p->data) % 2 == 0)
		{
			node *dcl = new node[1];
			dcl->data = i;
			node *temp = p->next;
			p->next = dcl;  
			dcl->pre = p;  
			dcl->next = temp;
			temp->pre = dcl;
		}
		else
		{
			p = p->pre;
			node *dcl = new node[1];
			dcl->data = i;
			node *temp = p->next; 
			p->next = dcl; 
			dcl->pre = p;  
			dcl->next = temp; 
			temp->pre = dcl; 
			p = p->next->next;
		}
		size++;
	}
	while (size > m)
	{
		for (int j = 1; j <= k; j++)
		{
			p = p->next;
		}
		node*s = p;
		p = p->pre;
		s->pre->next = s->next;
		s->next->pre = s->pre; 
		delete s;
		s = NULL;
		size--;
	}
		int x = 1;
		int flag = 0;
		while (x <= size)
		{
			if (p->data <= m)
				flag++;
			p = p->next;
			x++;
		}
		return flag;
}
int main() 
{
	DCLink dcl;
	int N, M, k;
	cin >> N >> M >> k;
	for (int i = 1; i <= M; i++)
		dcl.add(i);
	cout << dcl.Joseph(N, M, k) << endl;
	return 0;
}

