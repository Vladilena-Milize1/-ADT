#pragma once
#include<stdio.h>
#include<malloc.h>
#include<string.h>
//ADT抽象数据类型
typedef int Data;
//定义节点结构
typedef struct Node {
	Data data;//数据域 存储数据
	//struct Node* next;//指针域 存储下一个节点的地址
	Node* next;
}Node;
// 创建链表的函数声明
Node* createList();
//从头插入(插在头节点后)
void push_front(Node* list, Data val);//value
//从尾插入
void push_back(Node* list, Data val);
//指定位置的后面插入(下标)
void insert_pos(Node* list, int pos, Data val);
//指定位置插入(指定元素之后插入)
void insert_item(Node* list, Node* item, Data val);
//遍历 并输出
void show_list(Node* list);
//查找元素
Node* find(Node* list, Data val);
//头节点删
void pop_front(Node* list);
//尾节点删
void pop_back(Node* list);
//删除指定元素
void removeOne(Node* list, Data val);//删除一次 
void removeAll(Node* list, Data val);//删除全部指定相同数据
