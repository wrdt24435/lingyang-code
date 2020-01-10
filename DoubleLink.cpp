#include <iostream>
#include "DoubleLink.h"
using namespace std;
//一个节点
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
//双向链表基本操作
template<class T> 
class DoubleLink 
{
public:
	DoubleLink();
	~DoubleLink();
 
	int size();//大小
	int is_empty();//判断是否为空
 
	T get_value(int index);//获取节点
	T get_first();//获取首节点
	T get_last();//获取尾节点
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
DoubleLink<T>::DoubleLink() : count(0)	// 设置链表计数为0
{
	phead = new DNode<T>();
	phead->prev = phead->next = NULL;
}
 
// 析构函数
template<class T>
DoubleLink<T>::~DoubleLink() 
{
	cout<< "析构函数 in" <<endl;
	// 删除所有的节点
	DNode<T>* ptmp;
	DNode<T>* pnode = phead->prev;
	while (pnode != NULL)
	{
		ptmp = pnode;
		pnode=pnode->next;
		cout<< "delete value: " << ptmp->value <<endl;
		delete ptmp;
	}
 
	// 删除"表头"
	delete phead;
	phead = NULL;
}
// 将节点插入到第index位置之后
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
 // 返回节点数目
template<class T>
int DoubleLink<T>::size() 
{
	return count;
}
// 将节点插入第一个节点处。
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
 
// 将节点追加到链表的末尾
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
//给链表加入第一个节点
template<class T>
int DoubleLink<T>::first(T t) 
{
	DNode<T>* pnode = new DNode<T>(t, NULL, NULL);
	phead->next = pnode;
	phead->prev = pnode;
	count++;
	return 0;
}
// 获取第index位置的节点的值
template<class T>
T DoubleLink<T>::get_value(int index) 
{
		// 判断参数有效性
	if (index<0 || index>=count)
	{
		cout << "get node failed! the index in out of bound!" << endl;
		return (T)-1;	//临时return
	}
 	int i=0;
	// 正向查找
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
// 获取第index位置的节点
template<class T>
DNode<T>* DoubleLink<T>::get_node(int index) 
{
		// 判断参数有效性
	if (index<0 || index > count)
	{
		cout << "get node failed! the index in out of bound!" << endl;
		return (T)0;
	}
 	int i=0;
	// 正向查找
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
  
// 获取第1个节点的值
template<class T>
T DoubleLink<T>::get_first() 
{
	return phead->prev;
}
 
// 获取最后一个节点的值
template<class T>
T DoubleLink<T>::get_last() 
{
	return phead->next;
}

 
// 返回链表是否为空
template<class T>
int DoubleLink<T>::is_empty() 
{
	return count==0;
}
 
// 删除index位置的节点
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
 
// 删除第一个节点
template<class T>
int DoubleLink<T>::delete_first() 
{
	DNode<T>* temp = phead->prev;
	phead->prev = phead->prev->next;
	delete temp;
	count--;
	return 0;
}
 
// 删除最后一个节点
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
	int iarr1[4] = {10, 20, 30, 40};//定义一个数组
 	int iarr2[4] = {5, 6, 7, 8};//定义一个数组
	cout << "\n开始测试 int数据" << endl;
	// 创建双向链表
	DoubleLink<int> *pdlink = new DoubleLink<int>();
 	for (int i=0; i<4; i++) {
	//pdlink->insert(0, 20);        // 将 20 插入到第一个位置
		pdlink->append_last(iarr1[i]);   
 	}
	for (int i=0; i<4; i++) {
		pdlink->insert_first(iarr2[i]);  
 	}
 	pdlink->insert(6, 777);
	/*// 双向链表是否为空
	cout << "is_empty()=" << pdlink->is_empty() <<endl;
	// 双向链表的大小
	cout << "size()=" << pdlink->size() <<endl;*/
 
	// 打印双向链表中的全部数据
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
	int_test();        // 演示向双向链表操作“int数据”。
	return 0;
}