#define _CRT_SECURE_NO_WARNINGS
//��ջ��һ���������������ô洢�ṹʵ�ֵ�ջ,Ϊ�˱��ڲ���,�˴����ô�ͷ�ڵ�ĵ�����ʵ��
//������ջ����ɾ�ڵ����ֻ��ͷ�ڵ����,�����ͷָ����Ϊջ����ָ�� top
#include <stdio.h>
#include <malloc.h>
#include "FileName.h"

int mian()
{
    LinkStNode* s;
    InitStack(s);  // ��ʼ����ͷ�ڵ����ջ
    int choice;
    ElemType e;
    //�����˵�
    while (1) {
        printf("\n======== ��ջ�����˵� ========");
        printf("\n1. ��ջ");
        printf("\n2. ��ջ");
        printf("\n3. �鿴ջ��");
        printf("\n4. ���ջ��");
        printf("\n5. ��ʾջ��Ԫ��");
        printf("\n6. ����ջ���˳�");
        printf("\n����������еĲ�����");
        int result = scanf("%d", &choice);
        if (result != 1) { // ע�����������ʱ�Ĵ���
            printf("���������,����������\n");
            while (getchar() != '\n'); // ��ջ���
            continue;
        }

        switch (choice) {
        case 1:  // ��ջ
            printf("������Ҫ��ջ���ַ���");
            scanf(" %c", &e);  // �ո��������ջ��з�
            Push(s, e);
            printf("[�ɹ�] '%c' ����ջ\n", e);
            break;

        case 2:  // ��ջ
            if (Pop(s, e)) {
                printf("[�ɹ�] ��ջԪ�أ�%c\n", e);
            }
            else {
                printf("[ʧ��] ջ�ѿ�\n");
            }
            break;

        case 3:  // ��ȡջ��Ԫ��
            if (GetTop(s, e)) {
                printf("ջ��Ԫ�أ�%c\n", e);
            }
            else {
                printf("ջΪ��\n");
            }
            break;

        case 4:  // ���ջ��
            printf(StackEmpty(s) ? "ջΪ��\n" : "ջ�ǿ�\n");
            break;

        case 5:  // ��ʾջ��
            show(s);
            break;

        case 6:  // �����˳�
            DestoryStack(s);
            printf("ջ���٣������˳�\n");
            return 0;

        default:
            printf("δ֪����,����������\n");
        }

        // ������뻺��
        while (getchar() != '\n');
    }
}