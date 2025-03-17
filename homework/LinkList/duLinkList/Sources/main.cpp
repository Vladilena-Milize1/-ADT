#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "duLinkedList.h"  // 包含链表操作的头文件



// 访问函数，用于打印链表中的数据
void printElem(int e) {
    printf("%d ", e);  // 打印每个节点的数据
}

int main() {
    DuLinkedList L = NULL;  // 定义链表头指针
    int choice, value;
    int deletedData;
    DuLNode* newNode;

    // 显示菜单，直到用户选择退出
    while (1) {
        printf("\n===========================\n");
        printf("双向链表操作菜单：\n");
        printf("1. 初始化链表\n");
        printf("2. 插入节点（尾部）\n");
        printf("3. 删除节点\n");
        printf("4. 遍历链表并显示\n");
        printf("5. 销毁链表\n");
        printf("6. 退出程序\n");
        printf("请输入你的选择 (1-6): ");
        scanf("%d", &choice);

        DuLNode* tempNode = NULL;  // 确保在此处初始化 tempNode

        switch (choice) {
        case 1:
            // 初始化链表
            if (InitList_DuL(&L) == SUCCESS) {
                printf("链表初始化成功\n");
            }
            else {
                printf("链表初始化失败\n");
            }
            break;

        case 2:
            // 插入节点到链表尾部
            if (L == NULL) {
                printf("链表未初始化，请先初始化链表\n");
                break;
            }
            newNode = (DuLNode*)malloc(sizeof(DuLNode));
            if (newNode == NULL) {
                printf("内存分配失败\n");
                break;
            }
            printf("请输入要插入的数据：");
            scanf("%d", &value);
            newNode->data = value;
            newNode->next = NULL;

            if (L->next == NULL) {
                L->next = newNode;  // 如果链表为空，直接插入
                newNode->prior = L;
            }
            else {
                // 否则插入到链表尾部
                DuLNode* tail = L;
                while (tail->next != NULL) {
                    tail = tail->next;
                }
                InsertAfterList_DuL(tail, newNode);
            }
            printf("数据 %d 插入成功\n", value);
            break;

        case 3:
            // 删除链表中的节点
            if (L == NULL || L->next == NULL) {
                printf("链表为空，无法删除节点\n");
                break;
            }
            printf("请输入要删除节点的数据：");
            scanf("%d", &value);

            // 在删除操作之前初始化 tempNode
            tempNode = L->next;
            while (tempNode != NULL && tempNode->data != value) {
                tempNode = tempNode->next;
            }

            if (tempNode == NULL) {
                printf("未找到数据 %d 的节点！\n", value);
            }
            else {
                if (DeleteList_DuL(tempNode, &deletedData) == SUCCESS) {
                    printf("数据 %d 被删除成功！\n", deletedData);
                }
                else {
                    printf("删除失败\n");
                }
            }
            break;

        case 4:
            // 遍历链表并显示
            if (L == NULL || L->next == NULL) {
                printf("链表为空\n");
            }
            else {
                printf("链表内容：");
                TraverseList_DuL(L, printElem);
                printf("\n");
            }
            break;

        case 5:
            // 销毁链表
            if (L == NULL) {
                printf("链表未初始化，无法进行销毁操作\n");
            }
            else {
                DestroyList_DuL(&L);
                printf("链表销毁成功\n");
            }
            break;

        case 6:
            // 退出程序
            DestroyList_DuL(&L);
            printf("程序退出，链表已销毁\n");
            return 0;

        default:
            // 输入无效时的提示
            printf("无效选择，请重新输入\n");
        }
    }

    return 0;
}
