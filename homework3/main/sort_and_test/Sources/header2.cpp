
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "header2.h"





void generate_random_array(int* arr, int n, int max_val) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (max_val + 1);
    }
}

int* copy_array(const int* src, int n) {
    int* dest = (int*)malloc(n * sizeof(int));
    if (dest == NULL) {
        fprintf(stderr, "�ڴ����ʧ��!\n");
        exit(EXIT_FAILURE);
    }
    memcpy(dest, src, n * sizeof(int));
    return dest;
}

double test_sort(void (*sort_func)(int*, int), int* arr, int n) {
    int* data = copy_array(arr, n);
    clock_t start = clock();
    sort_func(data, n);
    clock_t end = clock();
    free(data);
    return (double)(end - start) * 1000 / CLOCKS_PER_SEC;
}

void generate_small_array(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

void test_high_frequency_sort(void (*sort_func)(int*, int), int base_array[], int n, int iterations) {
    int* working_array = (int*)malloc(n * sizeof(int));
    clock_t total_time = 0;

    for (int i = 0; i < iterations; i++) {
        memcpy(working_array, base_array, n * sizeof(int));
        clock_t start = clock();
        sort_func(working_array, n);
        clock_t end = clock();
        total_time += (end - start);
    }

    free(working_array);
    double total_ms = (double)total_time * 1000 / CLOCKS_PER_SEC;
    double avg_us = total_ms * 1000 / iterations;
    printf("�ܺ�ʱ: %.2f ms | ƽ������: %.2f ��s\n", total_ms, avg_us);
}

void test_sort_with_data(void (*sort_func)(int*, int), int* arr, int n, int iterations) {
    int* data = (int*)malloc(n * sizeof(int));
    memcpy(data, arr, n * sizeof(int));

    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        if (i > 0) memcpy(data, arr, n * sizeof(int));
        sort_func(data, n);
    }
    clock_t end = clock();

    free(data);
    double time_ms = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    if (iterations > 1) {
        printf("�ܺ�ʱ: %.2f ms | ƽ������: %.2f ��s\n", time_ms, time_ms * 1000 / iterations);
    }
    else {
        printf("��ʱ: %.2f ms\n", time_ms);
    }
}
// �ļ�����
bool generate_and_save_data(const char* filename, int n, int max_val) {
    
    char full_path[_MAX_PATH];
//#ifdef _WIN32��ƽ̨ʵ��
    if (!_fullpath(full_path, filename, _MAX_PATH)) {
        fprintf(stderr, "·������ʧ��\n");
        return false;
    }
//#else 
    //if (realpath(filename, full_path) == NULL) {
    //    fprintf(stderr, "·������ʧ��\n");
    //    return false;
   // }
//#endif

    printf("���������ļ�����%s\n", full_path); // ·����ʾ
    // �����ļ���д������
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "�����޷������ļ� %s\n", filename);
        return false;
    }

    // д���ļ�ͷ����������
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) { // �����������
        fprintf(file, "%d\n", rand() % (max_val + 1));
    }
    fclose(file);
    printf("�ɹ������ļ���%s����������%d��\n", filename, n);
    return true;
}


// ��ǿ���ļ���ȡ������״̬+������
bool read_data_from_file(const char* filename, int** arr, int* n) {// ��ȡ���ɵĲ����ļ�����·��
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "�����޷����ļ� %s\n", filename);
        return false;
    }

    if (fscanf(file, "%d", n) != 1) {// ��ȡ������
        fclose(file);
        fprintf(stderr, "�����ļ�ͷ��ʽ��Ч\n");
        return false;
    }

    *arr = (int*)malloc(*n * sizeof(int));//�ڴ����
    if (!*arr) {
        fclose(file);
        fprintf(stderr, "�����ڴ����ʧ�ܣ������С��%d��\n", *n);
        return false;
    }

    for (int i = 0; i < *n; i++) { // ��ȡ����
        if (fscanf(file, "%d", &(*arr)[i]) != 1) {
            free(*arr);
            *arr = NULL;
            fclose(file);
            fprintf(stderr, "���󣺵�%d�����ݶ�ȡʧ��\n", i + 2);
            return false;
        }
    }
    fclose(file);
    return true;
}
