#include <iostream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

#define PRINT_IP

void delay(int sec)
{
	time_t start_time, cur_time; // ��������
	time(&start_time);
	do { 
		time(&cur_time);
	} while((cur_time - start_time) < sec );
} 

//һ���ڵ�
template<class T> 
struct TNode 
{
public:
	T data;
	TNode *left;
	TNode *right;
public:
	TNode() { }
	TNode(T t): data(t), left(NULL), right(NULL)
	{ }
};

//�����ӱȸ��ڵ�С���Һ��ӱȸ��ڵ��Ĺ��򴴽���
//�������ڵ�Ķ�����
template<class T> 
class binary_tree
{
public:	
	binary_tree(){};
	//binary_tree(T value);
	binary_tree(const T &value);
	~binary_tree();
	TNode<T> *create_node(const T &data);
	int is_empty();//�ж��Ƿ�Ϊ��
 	TNode<T> *get_root_node();
	int insert_node(const T &data);
#ifdef PRINT_IP	
	int sp_insert(const T &data);
	int sp_insert_node(const T &data, TNode<T> * &node);	//��ӡ������뷽��
	void show(binary_tree<T> * &tree);
	void show_in_print(TNode<T> * tree, int height);
#endif
	int get_height();
	int get_size();
	void pre_order_traverse(binary_tree<T> *proot);
	void in_order_traverse(binary_tree<T> *proot);
	void layer_order_traverse(binary_tree<T> *proot);
private:
	// �����
	TNode<T> *root;
	// ��ǰ���Ľ�����
	int size;
	int height;   //����
	void remove_all(TNode<T> *proot);	//�������ɾ�����н��
	void pre_traverse(TNode<T> *proot);
	void in_traverse(TNode<T> *proot);
	void layer_traverse(TNode<T> *proot, int layer, int count);
};
 

// ��������, ɾ����
template<class T> 
binary_tree<T>::~binary_tree() {
	remove_all(root);
}

/*template<class T> 
binary_tree<T>::binary_tree(T value): size(0), height(0)
{
	root = new TNode<T>(value);
}*/
template<class T> 
binary_tree<T>::binary_tree(const T &value): size(1), height(0)
{
	root = new TNode<T>(value);
}

template<class T> 
int binary_tree<T>::get_height()
{
    return height+1;
}

template<class T> 
TNode<T> * binary_tree<T>::create_node(const T &data)
{
	size++;
	return new TNode<T>(data);
}

template<class T> 
int binary_tree<T>::get_size()
{
    return size;
}

template<class T> 
int binary_tree<T>::is_empty()
{
    return size == 0;
}
// ����1�����, �õݹ���ֱ��
template<class T> 
int binary_tree<T>::insert_node(const T &data)
{
	TNode<T> *temp = root;
	TNode<T> **node_address;
	int count = 0;
	while (NULL != temp) {	
		if (temp->data > data) {
			node_address = &temp->left;
		    temp = temp->left;
		}
		else if (temp->data < data) {
			node_address = &temp->right;
		    temp = temp->right;
		}
		else {
			cout<< "����Ѵ��ڣ�������" <<endl;
			return -1;
		}
		count++;
	}
	if (count > height) {
		height = count;
	}
	*node_address = create_node(data);
	size++;
	return 0;
}

#ifdef PRINT_IP
// �����������(����ʽ��ӡIP��)
template<class T> 
int binary_tree<T>::sp_insert(const T &data)
{
	TNode<T> *temp = root;
	int pos1 = 0;
	int pos2 = data.find(".");
	int ret;
    while(string::npos != pos2)
    {
		//cout << "data 1:" << temp->data <<endl;
		ret = sp_insert_node(data.substr(pos1, pos2-pos1),temp);

		pos1 = pos2 + 1;
		pos2 = data.find(".", pos1);
		if (ret == 1) {
			while (string::npos != pos2) {
				temp->right = create_node(data.substr(pos1, pos2-pos1));
				temp = temp->right;
				pos1 = pos2 + 1;
				pos2 = data.find(".", pos1);
			}
			temp->right = create_node(data.substr(pos1, pos2-pos1));
			return 0;
		}
		temp = temp->right;
     }
	sp_insert_node(data.substr(pos1),temp);
	return 0;
	/*char *pch = strtok((char *)data, ".");  
	while (pch != NULL)  
	{  
		sp_insert_node(data,temp);  
		pch = strtok (NULL, ".");  
	}  	*/
	
}

template<class T> 
int binary_tree<T>::sp_insert_node(const T &data, TNode<T> * &node)
{
	while (node->data != data) {
		if (node->left) {
			node = node->left;
		} 
		else {
			node->left = create_node(data);
			node = node->left;
			return 1;
		}
	}
	if (!node->right) {
		return 1;	
	}
	return 0;	
}

template<class T> 
void binary_tree<T>::show(binary_tree<T> * &tree)
{
	TNode<T> *temp = tree->get_root_node();
	show_in_print(temp, 0);
}

template<class T> 
void binary_tree<T>::show_in_print(TNode<T> * tree, int height)
{
	int count = height;
	while (count) {
		cout<<"---";
		count--;
	}
	cout<< tree->data <<endl;
	count = height;
	if (tree->right) {
		show_in_print(tree->right, ++height);
	}
	if (tree->left) {
		show_in_print(tree->left, count);
	}
}
#endif

// �������(ǰ�����)
template <class T>
void binary_tree<T>::pre_order_traverse(binary_tree<T> *proot)
{
	cout << "ǰ����� :" <<endl; 
	pre_traverse(proot->get_root_node());
}
// �������(ǰ�����)
template <class T>
void binary_tree<T>::pre_traverse(TNode<T> *proot)
{
    if (NULL != proot)
    {
        cout << proot->data << ",   "; 
        pre_traverse(proot->left);
        pre_traverse(proot->right);
    }
}

//�������ɾ�����н��
template <class T>
void binary_tree<T>::remove_all(TNode<T> *proot)
{
    if (NULL != proot)
    {
        remove_all(proot->left);
        remove_all(proot->right);
        cout << "delete : " << proot->data <<endl; 
        //delay(2);
        delete proot;
    }
}

// ���ظ��ڵ�
template <class T>
TNode<T>* binary_tree<T>::get_root_node()
{
    return root;
}


// �������
template <class T>
void binary_tree<T>::in_order_traverse(binary_tree<T> *proot)
{
	cout << "������� :" <<endl; 
	in_traverse(proot->get_root_node());
}
template <class T>
void binary_tree<T>::in_traverse(TNode<T> *proot)
{
    if (NULL != proot)
    {
        in_traverse(proot->left);
        cout << proot->data << ",   "; 
        in_traverse(proot->right);
    }
}

#if 1
// ��α���
template <class T>
void binary_tree<T>::layer_order_traverse(binary_tree<T> *proot)
{
	cout << "��α��� :" <<endl;
	for(int i = 1; i <= height+1; i++) {
		layer_traverse(proot->get_root_node(), i, 1);
	}

}
template <class T>
void binary_tree<T>::layer_traverse(TNode<T> *proot, int layer, int count)
{
	if (NULL != proot) {
	    if (layer == count)
	    {	
			cout << proot->data << ",   ";
			return;
	    }
		if (count < layer)
	    {
			count++;
	        layer_traverse(proot->left, layer, count);
	        layer_traverse(proot->right, layer, count);
	    }
	}
}
#else
//�ö��е�������ʽ����: ��root���������Ȼ��ʼѭ����ȡ������ͷ�������ݺ��
//�ڵ�����Һ������������ֱ��������
#endif




int main()
{
	string s[] = {
		"192.168.19.43",
		"192.168.19.88",
		"192.125.19.88",
		"192.125.22.77",
		"172.168.19.88",
		"172.105.22.7",
	};
	string sss = "192";
	binary_tree<string> *ptree = new binary_tree<string>(sss);
	//int arr[9] = {10, 20, 40, 30, 77, 5, 7, 6, 8};//����һ������
	cout << "\n��ʼ����\n" << endl;
	// ����˫������
 	for (int i=0; i<6; i++) {
		ptree->sp_insert(s[i]);   
 	}
	int sz = ptree->get_size();
	//int h = ptree->get_height();
	cout << "sz: " << sz <<endl;	//<< "   height: " << h 
	ptree->show(ptree);
	delete ptree;
}

