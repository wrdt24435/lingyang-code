#ifndef LIST_H
#define LIST_H

typedef struct _single_node{
	void *content;
	struct _single_node *next;
}single_node;

typedef struct _head_single_list{
	int length;
}test_head;

single_node *single_node_creat(void *content);
int insert_list(single_node *head,void *content);
void display_list(single_node *head);
single_node insert_list_recursive(single_node,int);
single_node search_list(single_node,int);
int list_length(single_node);

#endif