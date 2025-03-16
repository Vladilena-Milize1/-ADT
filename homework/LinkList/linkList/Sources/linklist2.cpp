#include "linklist.h"
//创建节点
Node* createNode(Data val) {//创建节点值
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (!newNode) {
		printf("newNode malloc failed");//判断
		return NULL;
	}
	newNode->data = val;
	newNode->next = NULL;

	return newNode;
}
//创建链表

//声明
Node* createList()
{
	Node* head = (Node*)malloc(sizeof(Node));//head头节点 
	if (!head)//判断申请是否失败
	{
		printf("head malloc failed");
		return NULL;

	}
	//初始化为NULL
	//head->data = 0;//初始化
	//head->next = NULL;
	memset(head, 0, sizeof(Node));  //初始化
	return head;
}
void push_front(Node* list, Data val)
{//先让第二个节点(首元节点)接上新节点,再让新节点接上头节点
	Node* newNode = createNode(val);
	newNode->next = list->next;
	list->next = newNode;
}
void push_back(Node* list, Data val)
{//遍历找到最后一个节点,让尾节点与新节点连接,最后让新节点的next指向null
	Node* curNode = list;
	while (curNode->next){
		curNode = curNode->next;
	}
	Node* newNode = createNode(val);
	newNode->next = NULL;


}
void insert_pos(Node* list, int pos, Data val)
{//遍历,先找到pos位置前一个元素,原因是必须先知道前一元素的next
	Node* curNode = list;
	for (int i = 0; i < pos&&curNode->next; i++) {//排除特殊情况,如pos>>i;同时排除curNode为空的特殊情况

		curNode = curNode->next;
	}
	//先让新节点连上后一个节点
	Node* newNode = createNode(val);
	newNode->next = curNode->next;
	//让前一个节点连上新节点
	curNode->next = newNode;
	
}
void insert_item(Node* list, Node* item, Data val)
{
	Node* newNode = createNode(val);
	//新节点连上后面的节点
	newNode->next = item->next;
	//item(已知指定的节点)连上新节点
	item->next = newNode;
}

void show_list(Node* list)
{
	Node* curNode = list->next;
	while (curNode){
		printf("%d ", curNode->data);
		curNode = curNode->next;
	}
	putchar('\n');
}

Node* find(Node* list, Data val)
{
	Node* curNode = list->next;
	while (curNode) {
		if (curNode->data == val) {
			return curNode;
		}
		curNode = curNode->next;
	}
	return NULL;
}

void pop_front(Node* list)
{
	Node* delNode = list->next;//将要被删除的节点是头节点
	list->next = delNode->next;
	free(delNode);//释放,删除节点
}

void pop_back(Node* list)
{
	//若链表为空直接退出
	if (list->next == NULL)
		return;
	Node* curNode = list;
	while (/*curNode->next && */curNode->next->next)//注意排除链表为空的情况
	{
		//判断curNode是否为倒数第二个节点,即要删除节点的前一个节点
		curNode = curNode->next;//移动目前节点
	}
	free(curNode->next);//释放最后一个节点,删除
	curNode->next = NULL;
	
}

void removeOne(Node* list, Data val)
{
	//若链表为空直接退出
	if (list->next == NULL)
		return;
	Node* prevNode = list;//前一位节点
	Node* curNode = list->next;
	while(curNode)
	{
		if (curNode->data == val)
		{
			break;
		}
		curNode = curNode->next;
	}
	if (curNode) {


		prevNode->next = curNode->next;
		free(curNode);
	}//删除
}

void removeAll(Node* list, Data val)
{//若链表为空直接退出
	if (list->next == NULL)
		return;
	Node* prevNode = list;
	Node* curNode = list->next;
	Node* delNode = NULL;
	while (curNode) {
		if (curNode->data == val) {
			prevNode->next = curNode->next;//让要删除的节点的前一个节点指向要删除节点的后一个节点
			delNode = curNode;
		}
		else {//不是要删除的元素,就移动pre
			prevNode = curNode;
		}
		prevNode = curNode;
		curNode = curNode->next;
		//根据情况释放
		if (delNode) {
			free(delNode);
			delNode = NULL;
		}
	}
}
