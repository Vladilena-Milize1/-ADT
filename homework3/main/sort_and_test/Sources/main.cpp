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
    srand((unsigned int)time(NULL));//初始化随机种子

    while (1) {
        printf("\n=== 主菜单 ===");
        printf("\n1. 常规大数据测试");
        printf("\n2. 常规小数据测试");
        printf("\n3. 生成测试文件");
        printf("\n4. 文件数据测试");
        printf("\n0. 退出系统");

        int choice = to_get_input("\n请输入选项：", 0, 4);

        switch (choice) {
        case 1: {  // 直接实现常规测试
            int sizes[] = { 10000, 50000, 200000 };// 标准测试数据量
            for (int i = 0; i < 3; i++) {// 执行测试
                int n = sizes[i];// 及时释放内存
                int* arr = (int*)malloc(n * sizeof(int));
                generate_random_array(arr, n, 100000);// 生成随机数据
                run_large_data_test(arr, n);//大数据量测试
                free(arr);
            }
            break;
        }
        case 2: {  // 修复3：直接实现常规测试
            int* arr = (int*)malloc(100 * sizeof(int));
            generate_small_array(arr, 100);// 生成小数据
            run_small_data_test(arr, 100);// 高频测试
            free(arr);
            break;
        }
        case 3: // 生成标准测试文件
            main_generate_data();  
            break;
        case 4:// 文件数据测试
            file_test_operation();
            break;
        case 0://退出系统
            
            return 0;
        }
    }
}

