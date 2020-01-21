#include <iostream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

#define PRINT_IP

void delay(int sec)
{
	time_t start_time, cur_time; // 变量声明
	time(&start_time);
	do { 
		time(&cur_time);
	} while((cur_time - start_time) < sec );
} 

//一个节点
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

//按左孩子比父节点小，右孩子比父节点大的规则创建树
//不带父节点的二叉树
template<class T> 
class binary_tree
{
public:	
	binary_tree(){};
	//binary_tree(T value);
	binary_tree(const T &value);
	~binary_tree();
	TNode<T> *create_node(const T &data);
	int is_empty();//判断是否为空
 	TNode<T> *get_root_node();
	int insert_node(const T &data);
#ifdef PRINT_IP	
	int sp_insert(const T &data);
	int sp_insert_node(const T &data, TNode<T> * &node);	//打印问题插入方法
	void show(binary_tree<T> * &tree);
	void show_in_print(TNode<T> * tree, int height);
#endif
	int get_height();
	int get_size();
	void pre_order_traverse(binary_tree<T> *proot);
	void in_order_traverse(binary_tree<T> *proot);
	void layer_order_traverse(binary_tree<T> *proot);
private:
	// 根结点
	TNode<T> *root;
	// 当前树的结点个数
	int size;
	int height;   //树高
	void remove_all(TNode<T> *proot);	//后序遍历删除所有结点
	void pre_traverse(TNode<T> *proot);
	void in_traverse(TNode<T> *proot);
	void layer_traverse(TNode<T> *proot, int layer, int count);
};
 

// 析构函数, 删除树
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
// 插入1个结点, 用递归会更直观
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
			cout<< "结点已存在，不插入" <<endl;
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
// 特殊情况插入(按格式打印IP号)
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

// 先序遍历(前序遍历)
template <class T>
void binary_tree<T>::pre_order_traverse(binary_tree<T> *proot)
{
	cout << "前序遍历 :" <<endl; 
	pre_traverse(proot->get_root_node());
}
// 先序遍历(前序遍历)
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

//后序遍历删除所有结点
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

// 返回根节点
template <class T>
TNode<T>* binary_tree<T>::get_root_node()
{
    return root;
}


// 中序遍历
template <class T>
void binary_tree<T>::in_order_traverse(binary_tree<T> *proot)
{
	cout << "中序遍历 :" <<endl; 
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
// 层次遍历
template <class T>
void binary_tree<T>::layer_order_traverse(binary_tree<T> *proot)
{
	cout << "层次遍历 :" <<endl;
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
//用队列单向链表方式更快: 将root塞进队列里，然后开始循环：取出队列头，读数据后把
//节点的左右孩子塞进队列里，直至结束。
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
	//int arr[9] = {10, 20, 40, 30, 77, 5, 7, 6, 8};//定义一个数组
	cout << "\n开始测试\n" << endl;
	// 创建双向链表
 	for (int i=0; i<6; i++) {
		ptree->sp_insert(s[i]);   
 	}
	int sz = ptree->get_size();
	//int h = ptree->get_height();
	cout << "sz: " << sz <<endl;	//<< "   height: " << h 
	ptree->show(ptree);
	delete ptree;
}

