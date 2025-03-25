
#include "filename.h"

int main() {
    char infix[256], postfix[512];

    while (1) {
        printf("\n������ʽ (����stop���˳�������): ");
        fgets(infix, sizeof(infix), stdin);
        infix[strcspn(infix, "\n")] = '\0';  // ���ջ��з�

        // ����˳�����
        if (strcmp(infix, "stop") == 0) {
            printf("�˳�������...\n");
            break;
        }

        // ����������
        if (strlen(infix) == 0) {
            printf("����Ϊ��\n");
            continue;
        }

        // ���ʽת���ͼ���
        infixToPostfix(infix, postfix);
        //printf("��׺���ʽ: %s", postfix);��ѡ���Ƿ�չʾ��׺���ʽ

        int result = evaluatePostfix(postfix);
        if (result != -1) {
            printf("���: %d\n", result);
        }
    }

    return 0;
}