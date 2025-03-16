#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"linklist.h"
/*int main() {
	Node* list = createList();
	

	return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

void menu() {
    printf("\n链表操作菜单:\n");
    printf("1. 初始化链表\n");
    printf("2. 头插法插入元素\n");
    printf("3. 尾插法插入元素\n");
    printf("4. 按位置插入元素\n");
    printf("5. 查找元素\n");
    printf("6. 删除头节点\n");
    printf("7. 删除尾节点\n");
    printf("8. 删除指定元素(一次)\n");
    printf("9. 遍历链表\n");
    printf("0. 退出\n");
    printf("请选择操作: ");
}

int main() {
    Node* list = NULL;
    int choice, value, pos;

    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            list = createList();
            printf("链表已初始化\n");
            break;
        case 2:
            printf("输入要插入的值: ");
            scanf("%d", &value);
            push_front(list, value);
            break;
        case 3:
            printf("输入要插入的值: ");
            scanf("%d", &value);
            push_back(list, value);
            break;
        case 4:
            printf("输入插入位置和值: ");
            scanf("%d %d", &pos, &value);
            insert_pos(list, pos, value);
            break;
        case 5:
            printf("输入要查找的值: ");
            scanf("%d", &value);
            if (find(list, value))
                printf("元素 %d 存在于链表中\n", value);
            else
                printf("元素 %d 不存在\n", value);
            break;
        case 6:
            pop_front(list);
            printf("头节点已删除\n");
            break;
        case 7:
            pop_back(list);
            printf("尾节点已删除\n");
            break;
        case 8:
            printf("输入要删除的值: ");
            scanf("%d", &value);
            removeOne(list, value);
            break;
        case 9:
            printf("当前链表: ");
            show_list(list);
            break;
        case 0:
            printf("程序退出\n");
            return 0;
        default:
            printf("无效输入，请重新选择\n");
        }
    }
}
