
#include "filename.h"

// ��ջʵ��
void InitStack(LinkStNode** s) {
    *s = (LinkStNode*)malloc(sizeof(LinkStNode));
    (*s)->next = NULL;
}

void DestoryStack(LinkStNode** s) {
    LinkStNode* current = *s;
    while (current != NULL) {
        LinkStNode* temp = current;
        current = current->next;
        free(temp);
    }
    *s = NULL;
}

bool StackEmpty(LinkStNode* s) {
    return (s->next == NULL);
}

void Push(LinkStNode** s, ElemType e) {
    LinkStNode* p = (LinkStNode*)malloc(sizeof(LinkStNode));
    p->data = e;
    p->next = (*s)->next;
    (*s)->next = p;
}

bool Pop(LinkStNode** s, ElemType* e) {
    if ((*s)->next == NULL) return false;
    LinkStNode* p = (*s)->next;
    *e = p->data;
    (*s)->next = p->next;
    free(p);
    return true;
}

bool GetTop(LinkStNode* s, ElemType* e) {
    if (s->next == NULL) return false;
    *e = s->next->data;
    return true;
}


static int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;//���Ų�����Ƚ�,��������
 /*return ���ȼ���ֵ(2��ߣ�0���)
1.�˳����ȼ�2
2.�Ӽ����ȼ�1
3.����(������)����0
�����ȼ����ڱȽ����������˳��*/
}

// ʹ���˵��ȳ��㷨ʵ����׺ת��׺
void infixToPostfix(char* infix, char* postfix) {//infix���������׺���ʽ,postfix��ת���õ��ĺ�׺���ʽ
    LinkStNode* opStack;//�����ջ
    InitStack(&opStack);//��ʼ��
    int i = 0, j = 0;//i����׺����

    while (infix[i] != '\0') {
       // ��������(������λ��)
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];// ������ȡ�����ַ�
            }
            postfix[j++] = ' ';// ���ֺ�ӿո�ָ�
        }
        else if (infix[i] == '(') {// ������ֱ����ջ
            Push(&opStack, '(');
            i++;
        }
        else if (infix[i] == ')') {//�����Ŵ���
            ElemType top;
            // ����ջ��ֱ������������
            while (GetTop(opStack, &top) && top != '(') {
                Pop(&opStack, &top);
                postfix[j++] = top;
                postfix[j++] = ' ';
            }
            Pop(&opStack, &top); // ����������,�����
            i++;
        }
        //���������
        else if (strchr("+-*/", infix[i])) {
            ElemType top;
            // �Ƚϵ�ǰ�������ջ�����ȼ�
            while (!StackEmpty(opStack) && GetTop(opStack, &top) &&
                top != '(' && getPriority(infix[i]) <= getPriority(top)) {
                Pop(&opStack, &top);
                postfix[j++] = top;
                postfix[j++] = ' ';
            }
            Push(&opStack, infix[i]);//ʹ��ǰ�������ջ
            i++;
        }
        //�������:�����ո�ֱ������
        else {
            i++;
        }
    }
    //����ջ��ʣ�������
    ElemType op;
    while (Pop(&opStack, &op)) {
        postfix[j++] = op;
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';//�ַ�������
    DestoryStack(&opStack);//����
}

// ����ջ�Ľڵ㶨��
typedef struct int_stack_node {
    int data;
    struct int_stack_node* next;
} IntStackNode;

static void PushInt(IntStackNode** s, int e) {
    IntStackNode* p = (IntStackNode*)malloc(sizeof(IntStackNode));
    p->data = e;
    p->next = *s;//ԭ�ڵ�ָ����ջ��
    *s = p;//����ջ��ָ��
}

static bool PopInt(IntStackNode** s, int* e) {
    if (*s == NULL) return false;
    IntStackNode* p = *s;//���浱ǰջ��
    *e = p->data;
    *s = p->next;//��ȡ����,�ƶ�ָ��
    free(p);//�ͷŽڵ�
    return true;
}


/*
 �����׺���ʽ postfix�Ǻ�׺���ʽ�ַ���
 ��������������-1
 ԭ�����£�
 1. �����׺���ʽ
 2. ����ת��Ϊ��������ջ
 3. ���������ʱ������������������
 4. ��������������ջ
 5. ���ջ��ʣ���һ��Ԫ�ؼ�Ϊ���
 ������
 ����������ʱ����"�Ƿ��ı��ʽ,����������"
 ������󱨸�"�����������"
 δ֪����������������ַ�
*/
int evaluatePostfix(char* postfix) {
    IntStackNode* operandStack = NULL; // ������ջ
    int i = 0;

    while (postfix[i] != '\0') {
        // �����ո�
        if (postfix[i] == ' ') {
            i++;
            continue;
        }

        // ��������(����Ϊ��λ��)
        if (isdigit(postfix[i])) {
            int num = 0;
            // �����������ַ�ת��Ϊ����
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            PushInt(&operandStack, num);
        }
        // ���������
        else {
            char op = postfix[i];
            i++; // �ƶ�����һ���ַ�

            int b, a, result;
            // �����Ҳ�����(����ȳ�)
            if (!PopInt(&operandStack, &b)) {
                fprintf(stderr, "�Ƿ��ı��ʽ,����������\n");
                while (operandStack) PopInt(&operandStack, &b); // ���ջ
                return -1;
            }
            // �����������
            if (!PopInt(&operandStack, &a)) {
                fprintf(stderr, "�Ƿ��ı��ʽ,����������\n");
                while (operandStack) PopInt(&operandStack, &b);
                return -1;
            }

            // ִ������
            switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) {
                    fprintf(stderr, "�����������\n");
                    while (operandStack) PopInt(&operandStack, &b);
                    return -1;
                }
                result = a / b;
                break;
            default:
                fprintf(stderr, "δ֪�������: %c\n", op);
                while (operandStack) PopInt(&operandStack, &b);
                return -1;
            }
            // �����ջ
            PushInt(&operandStack, result);
        }
    }

    // ��֤���ս��
    int result;
    if (PopInt(&operandStack, &result) && operandStack == NULL) {
        return result; // ��ȷ�����ջ��ֻʣ���
    }
    else {
        fprintf(stderr, "�Ƿ��ı��ʽ: ���������\n");
        while (operandStack) PopInt(&operandStack, &result); // ��ղ���
        return -1;
    }
}