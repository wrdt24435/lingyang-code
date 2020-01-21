/*
        // (�ݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ�
        RBTNode<T>* search(T key);
        // (�ǵݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ�
        RBTNode<T>* iterativeSearch(T key);

        // ������С��㣺������С���ļ�ֵ��
        T minimum();
        // ��������㣺���������ļ�ֵ��
        T maximum();

        // �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
        RBTNode<T>* successor(RBTNode<T> *x);
        // �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
        RBTNode<T>* predecessor(RBTNode<T> *x);

        // �����(keyΪ�ڵ��ֵ)���뵽�������
        void insert(T key);

        // ɾ�����(keyΪ�ڵ��ֵ)
        void remove(T key);

        // ���ٺ����
        void destroy();

        // ��ӡ�����
        void print();
    private:
        // ǰ�����"�����"
        void preOrder(RBTNode<T>* tree) const;
        // �������"�����"
        void inOrder(RBTNode<T>* tree) const;
        // �������"�����"
        void postOrder(RBTNode<T>* tree) const;

        // (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
        RBTNode<T>* search(RBTNode<T>* x, T key) const;
        // (�ǵݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
        RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

        // ������С��㣺����treeΪ�����ĺ��������С��㡣
        RBTNode<T>* minimum(RBTNode<T>* tree);
        // ��������㣺����treeΪ�����ĺ����������㡣
        RBTNode<T>* maximum(RBTNode<T>* tree);

        // ����
        void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
        // ����
        void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
        // ���뺯��
        void insert(RBTNode<T>* &root, RBTNode<T>* node);
        // ������������
        void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
        // ɾ������
        void remove(RBTNode<T>* &root, RBTNode<T> *node);
        // ɾ����������
        void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

        // ���ٺ����
        void destroy(RBTNode<T>* &tree);

        // ��ӡ�����
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
//�����ӱȸ��ڵ�С���Һ��ӱȸ��ڵ��Ĺ��򴴽���
#include <iostream>
#include <time.h>
#include <string>
#include <queue>

using namespace std;


void delay(int sec)
{
	time_t start_time, cur_time; // ��������
	time(&start_time);
	do { 
		time(&cur_time);
	} while((cur_time - start_time) < sec );
} 
struct RBTdata
{
	int value;
	int color;	//0�Ǻڣ�1�Ǻ�
	RBTdata(int v): value(v), color(1)
	{}
};
//һ���ڵ�
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

//�����
template<class T> 
class RBTree
{
public:	
	RBTree(){};
	//RBTree(T value);
	RBTree(const T &value);
	~RBTree();
	RBTNode<T> *create_node(const T &data);
	int is_empty();//�ж��Ƿ�Ϊ��
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
	// �����
	RBTNode<T> *root;
	// ��ǰ���Ľ�����
	int size;
	void remove_all(RBTNode<T> *proot);	//�������ɾ�����н��
	void pre_traverse(RBTNode<T> *proot);
	void in_traverse(RBTNode<T> *proot);
	void layer_traverse(RBTNode<T> *proot, int layer, int count);
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);	//����ת
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);	//����ת
	bool insert_node(RBTNode<T> *node, const int &data);
	void insertFixUp(RBTNode<T>* node);
	RBTNode<T>* find(RBTNode<T>* node, const int &value);	//����data��ѯ���޽ڵ㣬���򷵻ؽڵ㣬���򷵻�NULL
	void remove(RBTNode<T> *node);	
	void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

#define rb_is_red(r)   ((r)->data.color == 1)
#define rb_is_black(r)  ((r)->data.color == 0)
#define rb_set_black(r)  do { (r)->data.color = 0; } while (0)
#define rb_set_red(r)  do { (r)->data.color = 1; } while (0)
};
 

// ��������, ɾ����
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
            x->father->left = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
        else
            x->father->right = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
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
        root = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
    }
    else
    {
        if (y == y->father->right)
            y->father->right = x;    // ��� y�������ڵ���Һ��ӣ���x��Ϊ��y�ĸ��ڵ���Һ��ӡ�
        else
            y->father->left = x;    // (y�������ڵ������) ��x��Ϊ��x�ĸ��ڵ�����ӡ�
    }
    x->right = y;
    y->father = x;
}

//����������
template <>
void RBTree<RBTdata>::insertFixUp(RBTNode<RBTdata>* node)
{
	//cout << "FN: " << node->data.value <<endl;
    RBTNode<RBTdata> *gparent;
	RBTNode<RBTdata> *parent;
	root = get_root_node();
    // ���ڵ��ɫʱ���õ�����
    while ((parent = node->father) && parent->data.color)
    {
		cout << "start adjust" << node->data.value <<endl;
        gparent = parent->father;

        //�������ڵ㡱�ǡ��游�ڵ�����ӡ�
        if (parent == gparent->left)
        {
            // Case 1����������ڵ��Ǻ�ɫ
            RBTNode<RBTdata> *uncle = gparent->right;
            if (uncle && uncle->data.color)
            {
                uncle->data.color = 0;
                parent->data.color = 0;	//���ø��ڵ������ڵ�Ϊ��
				gparent->data.color = 1;
                node = gparent;
                continue;	//�нڵ��ɺ�ɫ������������
            }
            // Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
            if (parent->right == node)
            {
                RBTNode<RBTdata> *tmp;	
                leftRotate(root, parent);	//������������������ڵ��Ϊ����
                tmp = parent;	//������ǰ�ڵ��Ϊ���ڵ�
                parent = node;	//��ǰ�ڵ��������ԭ���ĸ��ڵ�
                node = tmp;
            }	
            // Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
            parent->data.color = 0;
            gparent->data.color = 1;
            rightRotate(root, gparent);
			//���ø��ڵ�Ϊ��ɫ���游�ڵ�Ϊ��ɫ��Ȼ��������
        } 
        else	//�����ڵ����游�ڵ���Һ��ӣ�����ת�����෴
        {
            RBTNode<RBTdata> *uncle = gparent->left;
            if (uncle && uncle->data.color)
            {
                uncle->data.color = 0;
                parent->data.color = 0;	//���ø��ڵ������ڵ�Ϊ��
				gparent->data.color = 1;
                node = gparent;
                continue;	//�нڵ��ɺ�ɫ����������
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
		cout<< "����Ѵ��ڣ�������" <<endl;
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

// ����1�����, �õݹ���ֱ��
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

// �������(ǰ�����)
template <class T>
void RBTree<T>::pre_order_traverse(RBTree<T> *proot)
{
	cout << "ǰ����� :" <<endl; 
	pre_traverse(proot->get_root_node());
}
// �������(ǰ�����)
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

//�������ɾ�����н��
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

// ���ظ��ڵ�
template <class T>
RBTNode<T>* RBTree<T>::get_root_node()
{
    return root;
}


// �������
template <class T>
void RBTree<T>::in_order_traverse(RBTree<T> *proot)
{
	cout << "������� :" <<endl; 
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

//�ö��е�������ʽ����: ��root���������Ȼ��ʼѭ����ȡ������ͷ�������ݺ��
//�ڵ�����Һ������������ֱ��������
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
 * �����ɾ����������
 *
 * �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node �������Ľڵ�
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
                // Case 1: x���ֵ�w�Ǻ�ɫ��  
                rb_set_black(other);
                rb_set_red(parent);
                leftRotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
                rb_set_red(other);
                node = parent;
                parent = node->father;
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rightRotate(root, other);
                    other = parent->right;
                }
                // Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
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
                // Case 1: x���ֵ�w�Ǻ�ɫ��  
                rb_set_black(other);
                rb_set_red(parent);
                rightRotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
                rb_set_red(other);
                node = parent;
                parent = node->father;
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    // Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
                    rb_set_black(other->right);
                    rb_set_red(other);
                    leftRotate(root, other);
                    other = parent->left;
                }
                // Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
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
 * ɾ�����(node)�������ر�ɾ���Ľ��
 *
 * ����˵����
 *     root ������ĸ����
 *     node ɾ���Ľ��
 */
template <>
void RBTree<RBTdata>::remove(RBTNode<RBTdata> *node)
{
    RBTNode<RBTdata> *child, *parent;
    int color;

    // ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
        // ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
        // ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
        RBTNode<RBTdata> *replace = node;
        // ��ȡ��̽ڵ�
        replace = replace->right;
        while (replace->left != NULL) {
            replace = replace->left;
        }
        // "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
        if (node->father)
        {
            if (node->father->left == node)
                node->father->left = replace;
            else
                node->father->right = replace;
        } 
        else {
            // "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
            root = replace;
        }
        // child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
        // "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
        child = replace->right;
        parent = replace->father;
        // ����"ȡ���ڵ�"����ɫ
        color = replace->data.color;

        // "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {
            // child��Ϊ��
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
    // ����"ȡ���ڵ�"����ɫ
    color = node->data.color;

    if (child)
        child->father = parent;

    // "node�ڵ�"���Ǹ��ڵ�
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
 * ɾ��������м�ֵΪkey�Ľڵ�
 *
 * ����˵����
 *     tree ������ĸ����
 */
template <>
void RBTree<RBTdata>::remove_interface(const int &key)
{
    RBTNode<RBTdata> *node; 
    // ����key��Ӧ�Ľڵ�(node)���ҵ��Ļ���ɾ���ýڵ�
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


