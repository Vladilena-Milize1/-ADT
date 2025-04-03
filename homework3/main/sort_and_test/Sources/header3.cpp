#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "header2.h"
#include <time.h>
#include "header3.h"
#define LARGE_DATA_THRESHOLD 10000// ����������ֵ��������ֵ��Ϊ�����ݲ���
#define SMALL_DATA_THRESHOLD 500// С��������ֵ�����ڴ�ֵ�ɽ��и�Ƶ����
struct SortFunction {//���������������ṹ��
    void (*func)(int*, int);//������ָ��
    const char* name;//�����㷨����
};
// ���뺯��
int to_get_input(const char* prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            while (getchar() != '\n'); // ��ջ�����
            return value;
        }
        printf("������Ч��������%d-%d֮�������\n", min, max);
        while (getchar() != '\n'); // ��մ�������
    }
}
// �ļ����Բ˵�
void file_test_operation() {
    char filename[256];//�洢�û�������ı�·��
    int* arr = NULL;//��̬����ָ��
    int n = 0;

    while (1) {// ��ȡ�ļ�·������
        printf("\n�������ļ�·����������q���أ�: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL) continue;
        filename[strcspn(filename, "\n")] = 0;

        // ʹ��Windows���ݵ��ַ����Ƚ�,����˳�����
        if (_stricmp(filename, "q") == 0) { 
            if (arr) free(arr);
            return;
        }
        // ���Լ����ļ�
        if (!read_data_from_file(filename, &arr, &n)) {
            printf("�Ƿ����ԣ�(y/n): ");
            int c = getchar();//�̿ո���ջ�����
            if (tolower(c) != 'y') {
                while (getchar() != '\n');
                return;
            }
            while (getchar() != '\n');
            continue;
        }

        // �ɹ����غ�Ĳ��Բ˵�(�ļ������Ӳ˵�)
        while (1) {
            printf("\n=== �ļ����Բ˵� ===");
            printf("\n�ļ���%s����������%d��", filename, n);
            printf("\n1. ������������");
            if (n <= SMALL_DATA_THRESHOLD) printf("\n2. С���ݸ�Ƶ����");// ������������ʾ����ѡ��
            else printf("\n2. [������] ����������%d", SMALL_DATA_THRESHOLD);
            printf("\n0. �����ϼ�");

            int choice = to_get_input("\n��ѡ�������", 0, 2);

            if (choice == 0) {// �����ϼ�
                free(arr);
                arr = NULL;
                return;
            }
            // ִ��ѡ��Ĳ���
            if (choice == 2 && n > SMALL_DATA_THRESHOLD) {
                printf("��ǰ�ļ����ʺ�С���ݲ��ԣ�\n");
                continue;
            }

            // ִ�в����߼�
            if (choice == 1) run_large_data_test(arr, n);
            else if (choice == 2) run_small_data_test(arr, n);
        }
    }
}

void run_large_data_test(int* arr, int n) {
    struct SortFunction funcs[] = {
        {insertion_sort, "��������"},
        {merge_sort,     "�鲢����"},
        {quick_sort,     "��������"},
        {counting_sort,  "��������"},
        {radix_sort,     "��������"}
    };

    printf("\n=== ������������ ===\n");
    printf("������: %d\n", n);
    printf("============================\n");
    // �������������㷨���в���
    for (int j = 0; j < sizeof(funcs) / sizeof(funcs[0]); j++) {
        // ʹ��test_sort�������м�ʱ����
        double time = test_sort(funcs[j].func, arr, n);
        printf("%-10s: %.2f ����\n", funcs[j].name, time);
    }
}

void run_small_data_test(int* arr, int n) {
    struct SortFunction funcs[] = {
        {insertion_sort, "��������"},
        {merge_sort,     "�鲢����"},
        {quick_sort,     "��������"},
        {counting_sort,  "��������"},
        {radix_sort,     "��������"}
    };

    const int iterations = 100000;
    printf("\n=== С���ݸ�Ƶ���� ===\n");
    printf("����������: %d\n", n);
    printf("���Դ���: %d\n", iterations);
    printf("============================\n");

    for (int j = 0; j < sizeof(funcs) / sizeof(funcs[0]); j++) {
        printf("[%s]:\n", funcs[j].name); 
        // ��Ƶ����ר�ú���
        test_high_frequency_sort(funcs[j].func, arr, n, iterations);
        printf("----------------------------\n");
    }
}

void main_generate_data() {
    printf("\n=== ���ɲ����ļ� ===\n");
    generate_and_save_data("data_10000.txt", 10000, 100000);// �������ļ�����ֵ��Χ�ϴ�
    generate_and_save_data("data_50000.txt", 50000, 100000);
    generate_and_save_data("data_200000.txt", 200000, 100000); 
    generate_and_save_data("data_small_100.txt", 100, 1000);// С�����ļ���������ֵ��Χ��
    printf("�����ļ��������!\n");
}