#include <iostream>
#include "DoubleLink.h"
using namespace std;
//һ���ڵ�
template<class T> 
struct DNode 
{
public:
	T value;
	DNode *prev;
	DNode *next;
public:
	DNode() { }
	DNode(T t, DNode *prev, DNode *next) {
		this->value = t;
		this->prev  = prev;
		this->next  = next;
	}
};
//˫�������������
template<class T> 
class DoubleLink 
{
public:
	DoubleLink();
	~DoubleLink();
 
	int size();//��С
	int is_empty();//�ж��Ƿ�Ϊ��
 
	T get_value(int index);//��ȡ�ڵ�
	T get_first();//��ȡ�׽ڵ�
	T get_last();//��ȡβ�ڵ�
	int insert(int index, T t);
	int insert_first(T t);
	int append_last(T t);
 	int first(T t);
	int del(int index);
	int delete_first();
	int delete_last();
 
private:
	int count;
	DNode<T> *phead;
private:
	DNode<T> *get_node(int index);
};
 
template<class T>
DoubleLink<T>::DoubleLink() : count(0)	// �����������Ϊ0
{
	phead = new DNode<T>();
	phead->prev = phead->next = NULL;
}
 
// ��������
template<class T>
DoubleLink<T>::~DoubleLink() 
{
	cout<< "�������� in" <<endl;
	// ɾ�����еĽڵ�
	DNode<T>* ptmp;
	DNode<T>* pnode = phead->prev;
	while (pnode != NULL)
	{
		ptmp = pnode;
		pnode=pnode->next;
		cout<< "delete value: " << ptmp->value <<endl;
		delete ptmp;
	}
 
	// ɾ��"��ͷ"
	delete phead;
	phead = NULL;
}
// ���ڵ���뵽��indexλ��֮��
template<class T>
int DoubleLink<T>::insert(int index, T t) 
{
	if (index == 0)
		return insert_first(t);
	if (index > count)
		return append_last(t);
	DNode<T>* pindex = get_node(index);
	DNode<T>* pnode  = new DNode<T>(t, pindex, pindex->next);
	pindex->next->prev= pnode;
	pindex->next = pnode;
	count++;
	return 0;
}
 // ���ؽڵ���Ŀ
template<class T>
int DoubleLink<T>::size() 
{
	return count;
}
// ���ڵ�����һ���ڵ㴦��
template<class T>
int DoubleLink<T>::insert_first(T t) 
{
	if (!count) {
		first(t);
		return 0;
	}
	DNode<T>* pnode  = new DNode<T>(t, NULL, phead->prev);
	phead->prev->prev = pnode;
	phead->prev = pnode;
	count++;
	return 0;
}
 
// ���ڵ�׷�ӵ������ĩβ
template<class T>
int DoubleLink<T>::append_last(T t) 
{
	if (!count) {
		first(t);
		return 0;
	}
	DNode<T>* pnode = new DNode<T>(t, phead->next, NULL);
	phead->next->next = pnode;
	phead->next = pnode;
	count++;
	return 0;
}
//����������һ���ڵ�
template<class T>
int DoubleLink<T>::first(T t) 
{
	DNode<T>* pnode = new DNode<T>(t, NULL, NULL);
	phead->next = pnode;
	phead->prev = pnode;
	count++;
	return 0;
}
// ��ȡ��indexλ�õĽڵ��ֵ
template<class T>
T DoubleLink<T>::get_value(int index) 
{
		// �жϲ�����Ч��
	if (index<0 || index>=count)
	{
		cout << "get node failed! the index in out of bound!" << endl;
		return (T)-1;	//��ʱreturn
	}
 	int i=0;
	// �������
	if (index <= count/2)
	{	
		DNode<T>* pindex = phead->prev;
		while (i++ < index) {
			pindex = pindex->next;
		}
		return pindex->value;
	} else {
		int rindex = count - index -1;
		DNode<T>* prindex = phead->next;
		while (i++ < rindex) {
			prindex = prindex->prev;
		}
		return prindex->value;
	}
}
// ��ȡ��indexλ�õĽڵ�
template<class T>
DNode<T>* DoubleLink<T>::get_node(int index) 
{
		// �жϲ�����Ч��
	if (index<0 || index > count)
	{
		cout << "get node failed! the index in out of bound!" << endl;
		return (T)0;
	}
 	int i=0;
	// �������
	if (index <= count/2)
	{	
		DNode<T>* pindex = phead->prev;
		while (i++ < index) {
			pindex = pindex->next;
		}
		return pindex;
	} else {
		int rindex = count - index -1;
		DNode<T>* prindex = phead->next;
		while (i++ < rindex) {
			prindex = prindex->prev;
		}
		return prindex;
	}
}
  
// ��ȡ��1���ڵ��ֵ
template<class T>
T DoubleLink<T>::get_first() 
{
	return phead->prev;
}
 
// ��ȡ���һ���ڵ��ֵ
template<class T>
T DoubleLink<T>::get_last() 
{
	return phead->next;
}

 
// ���������Ƿ�Ϊ��
template<class T>
int DoubleLink<T>::is_empty() 
{
	return count==0;
}
 
// ɾ��indexλ�õĽڵ�
template<class T>
int DoubleLink<T>::del(int index) 
{
	if (index <= 0) {
		delete_first();
	} 
	else if (index >= (count - 1)) {
		delete_last();
	}
	else {
		DNode<T>* pindex = get_node(index);
		pindex->next->prev = pindex->prev;
		pindex->prev->next = pindex->next;
		delete pindex;
		count--;
	}
	return 0;
}
 
// ɾ����һ���ڵ�
template<class T>
int DoubleLink<T>::delete_first() 
{
	DNode<T>* temp = phead->prev;
	phead->prev = phead->prev->next;
	delete temp;
	count--;
	return 0;
}
 
// ɾ�����һ���ڵ�
template<class T>
int DoubleLink<T>::delete_last() 
{
	DNode<T>* temp = phead->next;
	phead->next = phead->next->prev;
	delete temp;
	count--;
	return 0;
}
 
 
 
 
 
 
 
 

void int_test()
{
	int iarr1[4] = {10, 20, 30, 40};//����һ������
 	int iarr2[4] = {5, 6, 7, 8};//����һ������
	cout << "\n��ʼ���� int����" << endl;
	// ����˫������
	DoubleLink<int> *pdlink = new DoubleLink<int>();
 	for (int i=0; i<4; i++) {
	//pdlink->insert(0, 20);        // �� 20 ���뵽��һ��λ��
		pdlink->append_last(iarr1[i]);   
 	}
	for (int i=0; i<4; i++) {
		pdlink->insert_first(iarr2[i]);  
 	}
 	pdlink->insert(6, 777);
	/*// ˫�������Ƿ�Ϊ��
	cout << "is_empty()=" << pdlink->is_empty() <<endl;
	// ˫������Ĵ�С
	cout << "size()=" << pdlink->size() <<endl;*/
 
	// ��ӡ˫�������е�ȫ������
	int sz = pdlink->size();
	cout << "sz: " << sz <<endl;
	for (int i=0; i<sz; i++) {
		cout << "pdlink(" << i << ")=" << pdlink->get_value(i) <<endl;
	}
	pdlink->del(6);
	pdlink->delete_last();
	pdlink->delete_first();
	sz = pdlink->size();
	cout << "after delete sz: " << sz <<endl;
	for (int i=0; i<sz; i++) {
		cout << "pdlink(" << i << ")=" << pdlink->get_value(i) <<endl;
	}	
	delete pdlink;
}

int main()
{
	int_test();        // ��ʾ��˫�����������int���ݡ���
	return 0;
}