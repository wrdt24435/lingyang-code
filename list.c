/*	暂时忽略malloc可靠性
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void *my_malloc(size_t size)
{
	void *p = malloc(size);
	memset(p, 0, size);
	return p;
}
//初始化链表
single_node *single_list_init(size_t size)
{
	single_node *node = my_malloc(sizeof(single_node));
	void *head_content = my_malloc(size);
	node->content = head_content;
	return node;
}
//插入一个链表到尾部
int insert_list(single_node *head, void *content){
	if(!head) {
		return -1;
	}
	single_node *new_element = my_malloc(sizeof(single_node));
	new_element->content = content;
	while(head->next){
		head = head->next;
	}
	head->next = new_element;
	return 0;
}
//插入一个链表到头部
int insert_list1(single_node *head, void *content){
	if(!head) {
		return -1;
	}
	single_node *new_element = my_malloc(sizeof(single_node));
	new_element->content = content;
	new_element->next = head->next;
	head->next = new_element;
	return 0;
	//printf("head->content %d\n",(int)head->content);
}

void display_list(single_node *head){
	single_node *temp = head;
	int i = 0;
	if (!head) {
		printf("display error1\n");
		return;
	}
	head = head->next;
	while(head){
		printf("%d ",(int)head->content);
		head=head->next;
		if (i++ > 10) {
			printf("display error\n");
			return;
		}
	}
	printf("\n length : %d\n",((test_head *)temp->content)->length);
}

//删除一个链表的尾，但是不释放内容的内存
int delete_list(single_node *head)
{
    if (!head || !head->next) {
	    printf("cannot delete");
	    return -1;
    }
    single_node *temp = head;
    single_node *my_head = head;
    head = head->next;
	while(head->next){
		temp = head;
		head = head->next;
	}
	temp->next = NULL;
    free(head);

    ((test_head *)my_head->content)->length--;
    return 0;
}
//根据内容参数删除指定节点, 不释放内容的内存
int delete_list2(single_node *head, void *content)
{
    if (!head || !head->next) {
	    printf("error delete2");
	    return -1;
    }
    single_node *temp = head;
    single_node *my_head = head;
    head = head->next;
	while(content != head->content){
		temp = head;
		head = head->next;
		if (!head->next) {
			printf("error delete3\n");
			return -2;
		}
	}
	temp->next = head->next;
    free(head);

    ((test_head *)my_head->content)->length--;
    return 0;
}

void destory_List(single_node *head)
{
    single_node *p = NULL;

    while(head)
    {
    	//printf("Destory head->content : %d\n", (int)head->content);
        p = head->next;
        free(head);
        head = p;
    }
}

// 反转链表(循环)
single_node *reverse_list(single_node *head)
{
	int i = 1;
	if (!head || !head->next) {
		//error
	}
	single_node *list = head;
	single_node *tmp;
	single_node *tmp_next;
	head = head->next;
	tmp = head;
	head = head->next;
	tmp_next = head;
	tmp->next = NULL;
	while (head) {
		/*if (i++ > 10) {
			break;
		}
		printf("reverse_list %d\n",(int)head->content);*/
		tmp_next = head->next;
		head->next = tmp;
		tmp = head;
		head = tmp_next;
	}
	list->next = tmp;
	return list;
}

int main(int argc, char const *argv[])
{
	int i;
	single_node *my_head = single_list_init(sizeof(test_head));
	int data[]={1,2,3,4,5};
	//printf("sizeof %d\n",sizeof(data)/sizeof(data[0]));
	for(i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
		if (insert_list1(my_head,(void *)data[i]) == 0) {
			//printf("coming %d\n",((test_head *)my_head->content)->length);
			((test_head *)my_head->content)->length++;
		}
	}
	display_list(my_head);
	my_head = reverse_list(my_head);
	display_list(my_head);
	return 0;
}






