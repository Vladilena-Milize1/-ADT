#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "header2.h"
#include <time.h>
#include"header3.h"
#define LARGE_DATA_THRESHOLD 10000
#define SMALL_DATA_THRESHOLD 500
int main() {
    srand((unsigned int)time(NULL));//��ʼ���������

    while (1) {
        printf("\n=== ���˵� ===");
        printf("\n1. ��������ݲ���");
        printf("\n2. ����С���ݲ���");
        printf("\n3. ���ɲ����ļ�");
        printf("\n4. �ļ����ݲ���");
        printf("\n0. �˳�ϵͳ");

        int choice = to_get_input("\n������ѡ�", 0, 4);

        switch (choice) {
        case 1: {  // ֱ��ʵ�ֳ������
            int sizes[] = { 10000, 50000, 200000 };// ��׼����������
            for (int i = 0; i < 3; i++) {// ִ�в���
                int n = sizes[i];// ��ʱ�ͷ��ڴ�
                int* arr = (int*)malloc(n * sizeof(int));
                generate_random_array(arr, n, 100000);// �����������
                run_large_data_test(arr, n);//������������
                free(arr);
            }
            break;
        }
        case 2: {  // �޸�3��ֱ��ʵ�ֳ������
            int* arr = (int*)malloc(100 * sizeof(int));
            generate_small_array(arr, 100);// ����С����
            run_small_data_test(arr, 100);// ��Ƶ����
            free(arr);
            break;
        }
        case 3: // ���ɱ�׼�����ļ�
            main_generate_data();  
            break;
        case 4:// �ļ����ݲ���
            file_test_operation();
            break;
        case 0://�˳�ϵͳ
            
            return 0;
        }
    }
}

