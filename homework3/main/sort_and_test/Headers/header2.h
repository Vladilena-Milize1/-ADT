#pragma once
#include <stdio.h>
#include <stdbool.h>
//此文件用于生成随机数据

bool generate_and_save_data(const char* filename, int n, int max_val);
bool read_data_from_file(const char* filename, int** arr, int* n);


void generate_random_array(int* arr, int n, int max_val);
int* copy_array(const int* src, int n);
double test_sort(void(*sort_func)(int*, int), int* arr, int n);
void generate_small_array(int* arr, int n);
void test_high_frequency_sort(void(*sort_func)(int*, int), int base_array[], int n, int iterations);
void test_sort_with_data(void(*sort_func)(int*, int), int* arr, int n, int iterations);
