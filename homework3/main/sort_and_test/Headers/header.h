#pragma once

#include <stdio.h>
#include <malloc.h>
//此文件用于实现排序算法
void insertion_sort(int arr[], int n);
void merge(int arr[], int l, int m, int r);
void merge_sort_helper(int arr[], int l, int r);
void merge_sort(int arr[], int n);
void swap(int* a, int* b);
int area_cut(int arr[], int low, int high);
void quick_sort_helper(int arr[], int low, int high);
void quick_sort(int arr[], int n);
void counting_sort(int arr[], int n);
int get_max(int arr[], int n);
void count_sort_for_radix(int arr[], int n, int exp);
void radix_sort(int arr[], int n);