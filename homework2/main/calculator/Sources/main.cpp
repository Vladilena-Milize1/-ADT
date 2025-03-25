
#include "filename.h"

int main() {
    char infix[256], postfix[512];//定义表达式长度

    while (1) {
        printf("\n输入表达式 (输入stop以退出计算器): ");
        fgets(infix, sizeof(infix), stdin);
        infix[strcspn(infix, "\n")] = '\0';  // 吸收换行符

        // 检查退出条件
        if (strcmp(infix, "stop") == 0) {
            printf("退出计算器...\n");
            break;
        }

        // 跳过空输入
        if (strlen(infix) == 0) {
            printf("输入为空\n");
            continue;
        }

        // 表达式转换和计算
        infixToPostfix(infix, postfix);
        //printf("后缀表达式: %s", postfix);可选择是否展示后缀表达式

        int result = evaluatePostfix(postfix);
        if (result != -1) {
            printf("结果: %d\n", result);
        }
    }

    return 0;
}
