
#ifndef FILENAME_H
#define FILENAME_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef char ElemType;//��ջ����
typedef struct linknode {
    ElemType data;
    struct linknode* next;
} LinkStNode;

// ��ջ����
void InitStack(LinkStNode** s);//��ʼ��
void DestoryStack(LinkStNode** s);//����
bool StackEmpty(LinkStNode* s);//�ж��Ƿ�Ϊ��
void Push(LinkStNode** s, ElemType e);//Ԫ����ջ
bool Pop(LinkStNode** s, ElemType* e);//��ջ
bool GetTop(LinkStNode* s, ElemType* e);//��ȡջ��Ԫ��
static int getPriority(char op);//������������ȡ��������ȼ�,opָ������ַ�,���Ų�����Ƚ�,��������



// ���ʽ����
void infixToPostfix(char* infix, char* postfix);//��׺ת��׺


int evaluatePostfix(char* postfix);

#endif