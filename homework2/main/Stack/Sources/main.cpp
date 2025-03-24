#define _CRT_SECURE_NO_WARNINGS
//链栈是一个利用链表来利用存储结构实现的栈,为了便于操作,此处采用带头节点的单链表实现
//由于链栈的增删节点操作只在头节点进行,链表的头指针作为栈顶的指针 top
#include <stdio.h>
#include <malloc.h>
#include "FileName.h"

int mian()
{
    LinkStNode* s;
    InitStack(s);  // 初始化带头节点的链栈
    int choice;
    ElemType e;
    //互动菜单
    while (1) {
        printf("\n======== 链栈操作菜单 ========");
        printf("\n1. 入栈");
        printf("\n2. 出栈");
        printf("\n3. 查看栈顶");
        printf("\n4. 检查栈空");
        printf("\n5. 显示栈顶元素");
        printf("\n6. 销毁栈并退出");
        printf("\n输入你想进行的操作：");
        int result = scanf("%d", &choice);
        if (result != 1) { // 注意输入非数字时的处理
            printf("错误的输入,请输入数字\n");
            while (getchar() != '\n'); // 清空缓冲
            continue;
        }

        switch (choice) {
        case 1:  // 入栈
            printf("请输入要入栈的字符：");
            scanf(" %c", &e);  // 空格用于吸收换行符
            Push(s, e);
            printf("[成功] '%c' 已入栈\n", e);
            break;

        case 2:  // 出栈
            if (Pop(s, e)) {
                printf("[成功] 出栈元素：%c\n", e);
            }
            else {
                printf("[失败] 栈已空\n");
            }
            break;

        case 3:  // 获取栈顶元素
            if (GetTop(s, e)) {
                printf("栈顶元素：%c\n", e);
            }
            else {
                printf("栈为空\n");
            }
            break;

        case 4:  // 检查栈空
            printf(StackEmpty(s) ? "栈为空\n" : "栈非空\n");
            break;

        case 5:  // 显示栈顶
            show(s);
            break;

        case 6:  // 销毁退出
            DestoryStack(s);
            printf("栈销毁，程序退出\n");
            return 0;

        default:
            printf("未知输入,请重新输入\n");
        }

        // 清空输入缓冲
        while (getchar() != '\n');
    }
}