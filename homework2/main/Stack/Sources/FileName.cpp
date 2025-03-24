#include<stdio.h>
#include<malloc.h>
#include "FileName.h"

void InitStack(LinkStNode*& s)//ջ�ĳ�ʼ��
{
	s = (LinkStNode*)malloc(sizeof(linknode));//��ʼ��
	s->next = NULL;//��ʾջ��
}
void DestoryStack(LinkStNode*& s) {//������ջ
	LinkStNode* p = s->next;
	while (p != NULL) {
		free(s);
		s = p;//ʹ��sָ��β�ڵ�,�ͷ����ڴ�
		p = p->next;
	}
	free(s);//free(p)
	s = NULL;
}
bool/*��������*/ StackEmpty(LinkStNode* s) {//�ж���ջ�Ƿ�Ϊ��
	return(s->next == NULL);
}
void Push(LinkStNode*& s, ElemType e) {//��ջ,����p�ڵ�
	LinkStNode* p;
	p = (LinkStNode*)malloc(sizeof(LinkStNode));
	p->data = e;//����ڵ�����Ϊe
	p->next = s->next/*�������p�ڵ���Ϊͷ�ڵ�top*/; s->next = p;
}
bool Pop(LinkStNode*& s, ElemType& e) {//��ջ
	LinkStNode* p;
	if (s->next == NULL) {//�ж��Ƿ�Ϊ��ջ
		return false;
	}
	p = s->next; e = p->data;//��p����ͷ�ڵ�
	s->next = p->next;//ɾ��p�ڵ�
	free(p);
	return true;

}
bool GetTop(LinkStNode* s, ElemType& e) {//ȡ��ջ��Ԫ��
	if (s->next == NULL){//�ж��Ƿ�Ϊ��ջ
		return false;
	}
	e = s->next->data;//��ȡջ��Ԫ��
	return true;
}
void show(LinkStNode* s) {//���ջ��Ԫ��
	ElemType e;
	if (GetTop(s, e)) {  
		printf("ջ��Ԫ��Ϊ��%c\n", e);
	}
	else {
		printf("ջΪ��\n");
	}
}