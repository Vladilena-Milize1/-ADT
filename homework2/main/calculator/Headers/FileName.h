
#ifndef FILENAME_H
#define FILENAME_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef char ElemType;//链栈定义
typedef struct linknode {
    ElemType data;
    struct linknode* next;
} LinkStNode;

// 链栈操作
void InitStack(LinkStNode** s);//初始化
void DestoryStack(LinkStNode** s);//销毁
bool StackEmpty(LinkStNode* s);//判断是否为空
void Push(LinkStNode** s, ElemType e);//元素入栈
bool Pop(LinkStNode** s, ElemType* e);//出栈
bool GetTop(LinkStNode* s, ElemType* e);//获取栈顶元素
static int getPriority(char op);//辅助函数：获取运算符优先级,op指运算符字符,括号不参与比较,单独处理



// 表达式处理
void infixToPostfix(char* infix, char* postfix);//中缀转后缀


int evaluatePostfix(char* postfix);

#endif