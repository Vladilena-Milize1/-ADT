#include<stdio.h>
#include<malloc.h>
#include "FileName.h"

void InitStack(LinkStNode*& s)//栈的初始化
{
	s = (LinkStNode*)malloc(sizeof(linknode));//初始化
	s->next = NULL;//表示栈空
}
void DestoryStack(LinkStNode*& s) {//销毁链栈
	LinkStNode* p = s->next;
	while (p != NULL) {
		free(s);
		s = p;//使得s指向尾节点,释放其内存
		p = p->next;
	}
	free(s);//free(p)
	s = NULL;
}
bool/*布尔类型*/ StackEmpty(LinkStNode* s) {//判断链栈是否为空
	return(s->next == NULL);
}
void Push(LinkStNode*& s, ElemType e) {//进栈,插入p节点
	LinkStNode* p;
	p = (LinkStNode*)malloc(sizeof(LinkStNode));
	p->data = e;//插入节点数据为e
	p->next = s->next/*将插入的p节点作为头节点top*/; s->next = p;
}
bool Pop(LinkStNode*& s, ElemType& e) {//出栈
	LinkStNode* p;
	if (s->next == NULL) {//判断是否为空栈
		return false;
	}
	p = s->next; e = p->data;//让p连上头节点
	s->next = p->next;//删除p节点
	free(p);
	return true;

}
bool GetTop(LinkStNode* s, ElemType& e) {//取得栈顶元素
	if (s->next == NULL){//判断是否为空栈
		return false;
	}
	e = s->next->data;//获取栈顶元素
	return true;
}
void show(LinkStNode* s) {//输出栈顶元素
	ElemType e;
	if (GetTop(s, e)) {  
		printf("栈顶元素为：%c\n", e);
	}
	else {
		printf("栈为空\n");
	}
}