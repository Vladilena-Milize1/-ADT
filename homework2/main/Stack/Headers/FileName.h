#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdio.h>
#include<malloc.h>
#include "FileName.h"
#define mian main

typedef char ElemType;
typedef struct linknode {
	ElemType data;//������
	struct linknode* next;//ָ����

}LinkStNode;//��ջ���Ͷ���

void InitStack(LinkStNode*& s);

void DestoryStack(LinkStNode*& s);

bool StackEmpty(LinkStNode* s);

void Push(LinkStNode*& s, ElemType e);

bool Pop(LinkStNode*& s, ElemType& e);

bool GetTop(LinkStNode* s, ElemType& e);

void show(LinkStNode* s);
