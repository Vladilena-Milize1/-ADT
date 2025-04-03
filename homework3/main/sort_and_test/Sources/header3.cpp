#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#include "header2.h"
#include <time.h>
#include "header3.h"
#define LARGE_DATA_THRESHOLD 10000// 大数据量阈值，超过此值视为大数据测试
#define SMALL_DATA_THRESHOLD 500// 小数据量阈值，低于此值可进行高频测试
struct SortFunction {//定义所有排序函数结构体
    void (*func)(int*, int);//排序函数指针
    const char* name;//排序算法名称
};
// 输入函数
int to_get_input(const char* prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            while (getchar() != '\n'); // 清空缓冲区
            return value;
        }
        printf("输入无效，请输入%d-%d之间的数字\n", min, max);
        while (getchar() != '\n'); // 清空错误输入
    }
}
// 文件测试菜单
void file_test_operation() {
    char filename[256];//存储用户输入的文本路径
    int* arr = NULL;//动态数组指针
    int n = 0;

    while (1) {// 获取文件路径输入
        printf("\n请输入文件路径（或输入q返回）: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL) continue;
        filename[strcspn(filename, "\n")] = 0;

        // 使用Windows兼容的字符串比较,检查退出命令
        if (_stricmp(filename, "q") == 0) { 
            if (arr) free(arr);
            return;
        }
        // 尝试加载文件
        if (!read_data_from_file(filename, &arr, &n)) {
            printf("是否重试？(y/n): ");
            int c = getchar();//吞空格清空缓冲区
            if (tolower(c) != 'y') {
                while (getchar() != '\n');
                return;
            }
            while (getchar() != '\n');
            continue;
        }

        // 成功加载后的测试菜单(文件测试子菜单)
        while (1) {
            printf("\n=== 文件测试菜单 ===");
            printf("\n文件：%s（数据量：%d）", filename, n);
            printf("\n1. 大数据量测试");
            if (n <= SMALL_DATA_THRESHOLD) printf("\n2. 小数据高频测试");// 根据数据量显示可用选项
            else printf("\n2. [不可用] 数据量超过%d", SMALL_DATA_THRESHOLD);
            printf("\n0. 返回上级");

            int choice = to_get_input("\n请选择操作：", 0, 2);

            if (choice == 0) {// 返回上级
                free(arr);
                arr = NULL;
                return;
            }
            // 执行选择的测试
            if (choice == 2 && n > SMALL_DATA_THRESHOLD) {
                printf("当前文件不适合小数据测试！\n");
                continue;
            }

            // 执行测试逻辑
            if (choice == 1) run_large_data_test(arr, n);
            else if (choice == 2) run_small_data_test(arr, n);
        }
    }
}

void run_large_data_test(int* arr, int n) {
    struct SortFunction funcs[] = {
        {insertion_sort, "插入排序"},
        {merge_sort,     "归并排序"},
        {quick_sort,     "快速排序"},
        {counting_sort,  "计数排序"},
        {radix_sort,     "基数排序"}
    };

    printf("\n=== 大数据量测试 ===\n");
    printf("数据量: %d\n", n);
    printf("============================\n");
    // 遍历所有排序算法进行测试
    for (int j = 0; j < sizeof(funcs) / sizeof(funcs[0]); j++) {
        // 使用test_sort函数进行计时测试
        double time = test_sort(funcs[j].func, arr, n);
        printf("%-10s: %.2f 毫秒\n", funcs[j].name, time);
    }
}

void run_small_data_test(int* arr, int n) {
    struct SortFunction funcs[] = {
        {insertion_sort, "插入排序"},
        {merge_sort,     "归并排序"},
        {quick_sort,     "快速排序"},
        {counting_sort,  "计数排序"},
        {radix_sort,     "基数排序"}
    };

    const int iterations = 100000;
    printf("\n=== 小数据高频测试 ===\n");
    printf("单次数据量: %d\n", n);
    printf("测试次数: %d\n", iterations);
    printf("============================\n");

    for (int j = 0; j < sizeof(funcs) / sizeof(funcs[0]); j++) {
        printf("[%s]:\n", funcs[j].name); 
        // 高频测试专用函数
        test_high_frequency_sort(funcs[j].func, arr, n, iterations);
        printf("----------------------------\n");
    }
}

void main_generate_data() {
    printf("\n=== 生成测试文件 ===\n");
    generate_and_save_data("data_10000.txt", 10000, 100000);// 大数据文件（数值范围较大）
    generate_and_save_data("data_50000.txt", 50000, 100000);
    generate_and_save_data("data_200000.txt", 200000, 100000); 
    generate_and_save_data("data_small_100.txt", 100, 1000);// 小数据文件（限制数值范围）
    printf("测试文件生成完成!\n");
}