/*
        // (递归实现)查找"红黑树"中键值为key的节点
        RBTNode<T>* search(T key);
        // (非递归实现)查找"红黑树"中键值为key的节点
        RBTNode<T>* iterativeSearch(T key);

        // 查找最小结点：返回最小结点的键值。
        T minimum();
        // 查找最大结点：返回最大结点的键值。
        T maximum();

        // 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
        RBTNode<T>* successor(RBTNode<T> *x);
        // 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
        RBTNode<T>* predecessor(RBTNode<T> *x);

        // 将结点(key为节点键值)插入到红黑树中
        void insert(T key);

        // 删除结点(key为节点键值)
        void remove(T key);

        // 销毁红黑树
        void destroy();

        // 打印红黑树
        void print();
    private:
        // 前序遍历"红黑树"
        void preOrder(RBTNode<T>* tree) const;
        // 中序遍历"红黑树"
        void inOrder(RBTNode<T>* tree) const;
        // 后序遍历"红黑树"
        void postOrder(RBTNode<T>* tree) const;

        // (递归实现)查找"红黑树x"中键值为key的节点
        RBTNode<T>* search(RBTNode<T>* x, T key) const;
        // (非递归实现)查找"红黑树x"中键值为key的节点
        RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

        // 查找最小结点：返回tree为根结点的红黑树的最小结点。
        RBTNode<T>* minimum(RBTNode<T>* tree);
        // 查找最大结点：返回tree为根结点的红黑树的最大结点。
        RBTNode<T>* maximum(RBTNode<T>* tree);

        // 左旋
        void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
        // 右旋
        void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
        // 插入函数
        void insert(RBTNode<T>* &root, RBTNode<T>* node);
        // 插入修正函数
        void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
        // 删除函数
        void remove(RBTNode<T>* &root, RBTNode<T> *node);
        // 删除修正函数
        void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

        // 销毁红黑树
        void destroy(RBTNode<T>* &tree);

        // 打印红黑树
        void print(RBTNode<T>* tree, T key, int direction);

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
*/
//按左孩子比父节点小，右孩子比父节点大的规则创建树
#include <iostream>
#include <time.h>
#include <string>
#include <queue>

using namespace std;


void delay(int sec)
{
	time_t start_time, cur_time; // 变量声明
	time(&start_time);
	do { 
		time(&cur_time);
	} while((cur_time - start_time) < sec );
} 
struct RBTdata
{
	int value;
	int color;	//0是黑，1是红
	RBTdata(int v): value(v), color(1)
	{}
};
//一个节点
template<class T> 
struct RBTNode 
{
public:
	T data;
	RBTNode *left;
	RBTNode *right;
	RBTNode *father;
public:
	RBTNode() { }
	RBTNode(T t): data(t), left(NULL), right(NULL), father(NULL)
	{ }
};

//红黑树
template<class T> 
class RBTree
{
public:	
	RBTree(){};
	//RBTree(T value);
	RBTree(const T &value);
	~RBTree();
	RBTNode<T> *create_node(const T &data);
	int is_empty();//判断是否为空
 	RBTNode<T> *get_root_node();
	int get_size();
	void pre_order_traverse(RBTree<T> *proot);
	void in_order_traverse(RBTree<T> *proot);
	void layer_order_traverse(RBTree<T> *proot);
	void Print(RBTree* pRoot);
	bool insert_node_interface(RBTree<T> *proot, const int &data);
	bool find_interface(const int &data);
	void remove_interface(const int &key);
private:
	// 根结点
	RBTNode<T> *root;
	// 当前树的结点个数
	int size;
	void remove_all(RBTNode<T> *proot);	//后序遍历删除所有结点
	void pre_traverse(RBTNode<T> *proot);
	void in_traverse(RBTNode<T> *proot);
	void layer_traverse(RBTNode<T> *proot, int layer, int count);
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);	//左旋转
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);	//右旋转
	bool insert_node(RBTNode<T> *node, const int &data);
	void insertFixUp(RBTNode<T>* node);
	RBTNode<T>* find(RBTNode<T>* node, const int &value);	//根据data查询有无节点，有则返回节点，无则返回NULL
	void remove(RBTNode<T> *node);	
	void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

#define rb_is_red(r)   ((r)->data.color == 1)
#define rb_is_black(r)  ((r)->data.color == 0)
#define rb_set_black(r)  do { (r)->data.color = 0; } while (0)
#define rb_set_red(r)  do { (r)->data.color = 1; } while (0)
};
 

// 析构函数, 删除树
template<class T> 
RBTree<T>::~RBTree() {
	remove_all(root);
}

/*template<class T> 
RBTree<T>::RBTree(T value): size(0), height(0)
{
	root = new RBTNode<T>(value);
}*/
template<class T> 
RBTree<T>::RBTree(const T &value): size(1)
{
	root = new RBTNode<T>(value);
	root->data.color = 0;
}

template<class T> 
RBTNode<T> * RBTree<T>::create_node(const T &data)
{
	size++;
	return new RBTNode<T>(data);
}

template<class T> 
int RBTree<T>::get_size()
{
    return size;
}

template<class T> 
int RBTree<T>::is_empty()
{
    return size == 0;
}

template <>
void RBTree<RBTdata>::leftRotate(RBTNode<RBTdata>* &root, RBTNode<RBTdata>* x)
{
    RBTNode<RBTdata> *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->father = x;
    }
    y->father = x->father;

    if (x->father == NULL)
    {
        root = y;           
    }
    else
    {
        if (x->father->left == x)
            x->father->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
        else
            x->father->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
    }
    y->left = x;
    x->father = y;
}

template <>
void RBTree<RBTdata>::rightRotate(RBTNode<RBTdata>* &root, RBTNode<RBTdata>* y)
{
    RBTNode<RBTdata> *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->father = y;
    }
    x->father = y->father;

    if (y->father == NULL) 
    {
        root = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
    }
    else
    {
        if (y == y->father->right)
            y->father->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
        else
            y->father->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
    }
    x->right = y;
    y->father = x;
}

//修正二叉树
template <>
void RBTree<RBTdata>::insertFixUp(RBTNode<RBTdata>* node)
{
	//cout << "FN: " << node->data.value <<endl;
    RBTNode<RBTdata> *gparent;
	RBTNode<RBTdata> *parent;
	root = get_root_node();
    // 父节点黑色时不用调整数
    while ((parent = node->father) && parent->data.color)
    {
		cout << "start adjust" << node->data.value <<endl;
        gparent = parent->father;

        //若“父节点”是“祖父节点的左孩子”
        if (parent == gparent->left)
        {
            // Case 1条件：叔叔节点是红色
            RBTNode<RBTdata> *uncle = gparent->right;
            if (uncle && uncle->data.color)
            {
                uncle->data.color = 0;
                parent->data.color = 0;	//设置父节点和叔叔节点为黑
				gparent->data.color = 1;
                node = gparent;
                continue;	//有节点变成红色，继续修正。
            }
            // Case 2条件：叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                RBTNode<RBTdata> *tmp;	
                leftRotate(root, parent);	//调整二叉树，左旋后节点成为左孩子
                tmp = parent;	//左旋后当前节点成为父节点
                parent = node;	//当前节点的左孩子是原来的父节点
                node = tmp;
            }	
            // Case 3条件：叔叔是黑色，且当前节点是左孩子。
            parent->data.color = 0;
            gparent->data.color = 1;
            rightRotate(root, gparent);
			//设置父节点为黑色，祖父节点为红色，然后右旋。
        } 
        else	//若父节点是祖父节点的右孩子，则旋转方向相反
        {
            RBTNode<RBTdata> *uncle = gparent->left;
            if (uncle && uncle->data.color)
            {
                uncle->data.color = 0;
                parent->data.color = 0;	//设置父节点和叔叔节点为黑
				gparent->data.color = 1;
                node = gparent;
                continue;	//有节点变成红色，继续修正
            }
            if (parent->left == node)
            {
                RBTNode<RBTdata> *tmp;	
                rightRotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            parent->data.color = 0;
            gparent->data.color = 1;
            leftRotate(root, gparent);
        }
    }
	root->data.color = 0;
}

template<> 
bool RBTree<RBTdata>::insert_node(RBTNode<RBTdata> *node, const int &data)
{
	if (node->data.value > data) {
		if (node->left) {
			insert_node(node->left, data);
		}
		else {
			node->left = create_node(data);
			node->left->father = node;
			insertFixUp(node->left);
			size++;
		}
	}
	else if (node->data.value < data) {
		if (node->right) {
			insert_node(node->right, data);
		}
		else {
			node->right = create_node(data);
			node->right->father = node;
			insertFixUp(node->right);
			size++;
		}
	}
	else {
		cout<< "结点已存在，不插入" <<endl;
		return false;
	}
	return true;
}

template <>
RBTNode<RBTdata>* RBTree<RBTdata>::find(RBTNode<RBTdata> *node, const int &value)
{
	if (value < node->data.value) {
		if (node->left) {
			return find(node->left, value);
		}
		else {
			return NULL;
		}
	}
	else if (value > node->data.value) {
		if (node->right) {
			return find(node->right, value);
		}
		else {
			return NULL;
		}
	}
	else {
		return node;
	}
}
template <>
bool RBTree<RBTdata>::find_interface(const int &data)
{
	if (find(get_root_node(),data)) {
		return true;
	}
	else {
		return false;
	}
}

// 插入1个结点, 用递归会更直观
template<> 
bool RBTree<RBTdata>::insert_node_interface(RBTree<RBTdata> *proot, const int &data)
{
	if (insert_node(proot->get_root_node(), data)) {
		return true;
	}
	return false;
}

template<class T> 
bool RBTree<T>::insert_node_interface(RBTree<T> *proot, const int &data)
{
	cout << "yes!" <<endl;
	return true;
}

// 先序遍历(前序遍历)
template <class T>
void RBTree<T>::pre_order_traverse(RBTree<T> *proot)
{
	cout << "前序遍历 :" <<endl; 
	pre_traverse(proot->get_root_node());
}
// 先序遍历(前序遍历)
template <class T>
void RBTree<T>::pre_traverse(RBTNode<T> *proot)
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
void RBTree<T>::remove_all(RBTNode<T> *proot)
{
    if (NULL != proot)
    {
        remove_all(proot->left);
        remove_all(proot->right);
        //cout << "delete : " << proot->data <<endl; 
        //delay(2);
        delete proot;
    }
}

// 返回根节点
template <class T>
RBTNode<T>* RBTree<T>::get_root_node()
{
    return root;
}


// 中序遍历
template <class T>
void RBTree<T>::in_order_traverse(RBTree<T> *proot)
{
	cout << "中序遍历 :" <<endl; 
	in_traverse(proot->get_root_node());
}
template <class T>
void RBTree<T>::in_traverse(RBTNode<T> *proot)
{
    if (NULL != proot)
    {
        in_traverse(proot->left);
        cout << proot->data << ",   "; 
        in_traverse(proot->right);
    }
}

//用队列单向链表方式更快: 将root塞进队列里，然后开始循环：取出队列头，读数据后把
//节点的左右孩子塞进队列里，直至结束。
template <>
void RBTree<RBTdata>::Print(RBTree* pRoot) 
{
	RBTNode<RBTdata> *node = pRoot->get_root_node();
    if (node == NULL)
        return;
	int n = 0;
	int layer_n = 1;
    queue<RBTNode<RBTdata> *> q;
    q.push(node);

    while(!q.empty())
    {
        while(layer_n)
        {
            node = q.front();
			q.pop();
			if (node) {
				if (node->data.color) {
					cout <<" \033[31m"<< node->data.value <<"\033[0m ";
				}
				else {
					cout << " " << node->data.value << " ";
				}
	            if(node->left)
	            {
	                q.push(node->left);
	            }
				else {
					q.push(NULL);
				}
	            if(node->right)
	            {
	                q.push(node->right);
	            }
				else {
					q.push(NULL);
				}
				n += 2;
			}
			else {
				cout << " N ";
			}
			layer_n--;
        }
		cout<<endl;
		layer_n = n;
		n = 0;
    }
}

/*
 * 红黑树删除修正函数
 *
 * 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 待修正的节点
 */
template <>
void RBTree<RBTdata>::removeFixUp(RBTNode<RBTdata>* &root, RBTNode<RBTdata> *node, RBTNode<RBTdata> *parent)
{
    RBTNode<RBTdata> *other;

    while ((!node || rb_is_black(node)) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的  
                rb_set_black(other);
                rb_set_red(parent);
                leftRotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                rb_set_red(other);
                node = parent;
                parent = node->father;
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rightRotate(root, other);
                    other = parent->right;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                other->data.color = parent->data.color;
                rb_set_black(parent);
                rb_set_black(other->right);
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的  
                rb_set_black(other);
                rb_set_red(parent);
                rightRotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                rb_set_red(other);
                node = parent;
                parent = node->father;
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    rb_set_black(other->right);
                    rb_set_red(other);
                    leftRotate(root, other);
                    other = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
				other->data.color = parent->data.color;
                rb_set_black(parent);
                rb_set_black(other->left);
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}

/* 
 * 删除结点(node)，并返回被删除的结点
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 删除的结点
 */
template <>
void RBTree<RBTdata>::remove(RBTNode<RBTdata> *node)
{
    RBTNode<RBTdata> *child, *parent;
    int color;

    // 被删除节点的"左右孩子都不为空"的情况。
    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
        // 被删节点的后继节点。(称为"取代节点")
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        RBTNode<RBTdata> *replace = node;
        // 获取后继节点
        replace = replace->right;
        while (replace->left != NULL) {
            replace = replace->left;
        }
        // "node节点"不是根节点(只有根节点不存在父节点)
        if (node->father)
        {
            if (node->father->left == node)
                node->father->left = replace;
            else
                node->father->right = replace;
        } 
        else {
            // "node节点"是根节点，更新根节点。
            root = replace;
        }
        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->right;
        parent = replace->father;
        // 保存"取代节点"的颜色
        color = replace->data.color;

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {
            // child不为空
            if (child) {
                child->father = parent;
            }
            parent->left = child;

            replace->right = node->right;
            node->right->father = replace;
        }

        replace->father = node->father;
        replace->data.color = node->data.color;
        replace->left = node->left;
        node->left->father = replace;

        if (color == 0)
            removeFixUp(root, child, parent);

        delete node;
        return ;
    }

    if (node->left != NULL)
        child = node->left;
    else 
        child = node->right;

    parent = node->father;
    // 保存"取代节点"的颜色
    color = node->data.color;

    if (child)
        child->father = parent;

    // "node节点"不是根节点
    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root = child;

    if (color == 0)
        removeFixUp(root, child, parent);
    delete node;
}

/* 
 * 删除红黑树中键值为key的节点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 */
template <>
void RBTree<RBTdata>::remove_interface(const int &key)
{
    RBTNode<RBTdata> *node; 
    // 查找key对应的节点(node)，找到的话就删除该节点
    if ((node = find(root, key)) != NULL)
        remove(node);
}



int main()
{
	int a[20] = {10, 111, 178, 298, 77, 57, 17, 27, 71, 61,
				 66, 67, 11, 99, 28, 13, 38, 21, 88, 84};
	RBTdata Tdata = RBTdata(1000);
	RBTree<RBTdata> *ptree = new RBTree<RBTdata>(Tdata);
	for (int n = 0; n < 20; n++) {
		ptree->insert_node_interface(ptree, a[n]);
	}
	ptree->remove_interface(28);
	ptree->remove_interface(38);
	ptree->remove_interface(61);
	ptree->Print(ptree);
	delete ptree;
}


