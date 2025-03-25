
#include "filename.h"

// 链栈实现
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
    return 0;//括号不参与比较,单独处理
 /*return 优先级数值(2最高，0最低)
1.乘除优先级2
2.加减优先级1
3.其他(如括号)返回0
该优先级用于比较运算符处理顺序*/
}

// 使用了调度场算法实现中缀转后缀
void infixToPostfix(char* infix, char* postfix) {//infix是输入的中缀表达式,postfix是转化得到的后缀表达式
    LinkStNode* opStack;//运算符栈
    InitStack(&opStack);//初始化
    int i = 0, j = 0;//i是中缀索引

    while (infix[i] != '\0') {
       // 处理数字(包括多位数)
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];// 连续读取数字字符
            }
            postfix[j++] = ' ';// 数字后加空格分隔
        }
        else if (infix[i] == '(') {// 左括号直接入栈
            Push(&opStack, '(');
            i++;
        }
        else if (infix[i] == ')') {//右括号处理
            ElemType top;
            // 弹出栈顶直到遇到左括号
            while (GetTop(opStack, &top) && top != '(') {
                Pop(&opStack, &top);
                postfix[j++] = top;
                postfix[j++] = ' ';
            }
            Pop(&opStack, &top); // 弹出左括号,不输出
            i++;
        }
        //运算符处理
        else if (strchr("+-*/", infix[i])) {
            ElemType top;
            // 比较当前运算符与栈顶优先级
            while (!StackEmpty(opStack) && GetTop(opStack, &top) &&
                top != '(' && getPriority(infix[i]) <= getPriority(top)) {
                Pop(&opStack, &top);
                postfix[j++] = top;
                postfix[j++] = ' ';
            }
            Push(&opStack, infix[i]);//使当前运算符入栈
            i++;
        }
        //其余情况:遇到空格直接跳过
        else {
            i++;
        }
    }
    //弹出栈中剩余运算符
    ElemType op;
    while (Pop(&opStack, &op)) {
        postfix[j++] = op;
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';//字符串结束
    DestoryStack(&opStack);//销毁
}

// 整数栈的节点定义
typedef struct int_stack_node {
    int data;
    struct int_stack_node* next;
} IntStackNode;

static void PushInt(IntStackNode** s, int e) {
    IntStackNode* p = (IntStackNode*)malloc(sizeof(IntStackNode));
    p->data = e;
    p->next = *s;//原节点指向新栈顶
    *s = p;//更新栈顶指针
}

static bool PopInt(IntStackNode** s, int* e) {
    if (*s == NULL) return false;
    IntStackNode* p = *s;//保存当前栈顶
    *e = p->data;
    *s = p->next;//读取数据,移动指针
    free(p);//释放节点
    return true;
}


/*
 计算后缀表达式 postfix是后缀表达式字符串
 计算结果，出错返回-1
 原理如下：
 1. 读入后缀表达式
 2. 数字转换为整数并入栈
 3. 遇到运算符时弹出两个操作数计算
 4. 将计算结果重新入栈
 5. 最后栈中剩余的一个元素即为结果
 错误处理：
 操作数不足时报告"非法的表达式,操作数不足"
 除零错误报告"发生除零错误"
 未知运算符报告具体错误字符
*/
int evaluatePostfix(char* postfix) {
    IntStackNode* operandStack = NULL; // 操作数栈
    int i = 0;

    while (postfix[i] != '\0') {
        // 跳过空格
        if (postfix[i] == ' ') {
            i++;
            continue;
        }

        // 处理数字(可能为多位数)
        if (isdigit(postfix[i])) {
            int num = 0;
            // 将连续数字字符转换为整数
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            PushInt(&operandStack, num);
        }
        // 处理运算符
        else {
            char op = postfix[i];
            i++; // 移动到下一个字符

            int b, a, result;
            // 弹出右操作数(后进先出)
            if (!PopInt(&operandStack, &b)) {
                fprintf(stderr, "非法的表达式,操作数不足\n");
                while (operandStack) PopInt(&operandStack, &b); // 清空栈
                return -1;
            }
            // 弹出左操作数
            if (!PopInt(&operandStack, &a)) {
                fprintf(stderr, "非法的表达式,操作数不足\n");
                while (operandStack) PopInt(&operandStack, &b);
                return -1;
            }

            // 执行运算
            switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) {
                    fprintf(stderr, "发生除零错误\n");
                    while (operandStack) PopInt(&operandStack, &b);
                    return -1;
                }
                result = a / b;
                break;
            default:
                fprintf(stderr, "未知的运算符: %c\n", op);
                while (operandStack) PopInt(&operandStack, &b);
                return -1;
            }
            // 结果入栈
            PushInt(&operandStack, result);
        }
    }

    // 验证最终结果
    int result;
    if (PopInt(&operandStack, &result) && operandStack == NULL) {
        return result; // 正确情况：栈中只剩结果
    }
    else {
        fprintf(stderr, "非法的表达式: 额外操作数\n");
        while (operandStack) PopInt(&operandStack, &result); // 清空残留
        return -1;
    }
}