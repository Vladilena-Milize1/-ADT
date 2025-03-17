#include "duLinkedList.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//定义数据类型
typedef int data;

//定义链表的节点结构
/*typedef struct DuLNode {
    data data;            // 节点数据域
    struct DuLNode* prior;    // 前驱指针
    struct DuLNode* next;     // 后继指针
} DuLNode, * DuLinkedList;*/

Status InitList_DuL(DuLinkedList* L)
{
    *L = (DuLinkedList)malloc(sizeof(DuLNode));//为头节点分配内存
    if (*L==NULL) {//判断头节点指针值是否为空
        return ERROR; // 若内存分配失败，返回 ERROR
    }
    //初始化头节点的prior和next指针
    (*L)->prior= NULL;
    (*L)->next = NULL;
    //初始化头节点数据为0
    (*L)->data = 0;
    return SUCCESS;
}

void DestroyList_DuL(DuLinkedList* L)//销毁链表并释放所有节点的内存(删除)
{
    DuLNode* curNode = *L;
    DuLNode* temp;

    //正序遍历链表，逐一释放每个节点
    while (curNode != NULL) {
        temp = curNode;
        curNode = curNode->next;
        free(temp);
    }
    *L = NULL;  // 最后将头指针置为NULL
}

Status InsertBeforeList_DuL(DuLNode* p, DuLNode* q)//在给定节点p前插入新节点q
{
    if (p == NULL || q == NULL) return ERROR;
    
    {
        q->next = p;
        q->prior = p->prior;
    }

    if (p->prior != NULL) {
        p->prior->next = q; //将前驱节点的next指针修改与q连接
    }
    p->prior = q;  // 修改p节点的prior指针

    return SUCCESS;
}

Status InsertAfterList_DuL(DuLNode* p, DuLNode* q)//在给定节点p后插入新节点q
{
    if (p == NULL || q == NULL) return ERROR;
    {
        q->prior = p;
        q->next = p->next;
    }
    if (p->next != NULL) {
        p->next->prior = q;  //修改后继节点的prior指针
    }
    p->next = q;  //修改p节点的next指针

    return SUCCESS;
}

Status DeleteList_DuL(DuLNode* p, data* e)//删除节点p
{
    if (!p) 
        return ERROR;
    if (p->prior != NULL) {
        p->prior->next = p->next;  //修改前驱节点的next指针
    }
    if (p->next != NULL) {
        p->next->prior = p->prior;  //修改后继节点的prior指针
    }
    free(p);  // 删除
    return SUCCESS;
}

void TraverseList_DuL(DuLinkedList L, void(*visit)(data e))//遍历链表并输出
{
    if (L == NULL || L->next == NULL) {
        printf("链表为空\n");
        return;  //如果链表为空，则直接结束遍历
    }
    DuLNode* curNode = L->next;  //从头节点的后继节点开始遍历
    while (curNode != NULL) {
        visit(curNode->data);  //执行visit将数据打印输出
        curNode = curNode->next;
    } // 移动至下一个节点
}

