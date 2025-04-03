
#include "header.h"
//插入排序
/*插入排序是一种稳定的排序方法,最优时间复杂度为 O(n)，在数列几乎有序时效率很高。
    插入排序的最坏时间复杂度和平均时间复杂度都为 O(n^2)。*/
void insertion_sort(int arr[], int n) {
    int i, j, key;
    //从第二个元素开始遍历（i=1），因为第一个元素默认为有序区 已排序
    for (i = 1; i < n; i++) {
        key = arr[i];// 当前待插入元素
        j = i - 1;// 从已排序部分的末尾开始比较
        while (j >= 0 && arr[j] > key) {// 将比key大的元素向右移动，为key腾出插入位置
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;// 插入key到正确位置
    }
}
//归并排序
/*归并排序基于分治思想将数组分段排序后合并，时间复杂度在最优、最坏与平均情况下均为 O(nlogn)，
    空间复杂度为O(n)。归并排序可以只使用 O (1) 的辅助空间，但为便捷通常使用与原数组等长的辅助数组。*/
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;//左子数组长度与右子数组长度
    int n2 = r - m;
    int* L = (int*)malloc(n1 * sizeof(int));//动态分配临时数组存储左右数组
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];//将数据存储到临时数组中
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;//合并临时数组到原数组 其中 i是左数组指针j是右数组指针k是原数组指针
    while (i < n1 && j < n2) {  // 选择较小的元素放入原数组
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) arr[k++] = L[i++];//处理剩余元素
    while (j < n2) arr[k++] = R[j++];

    free(L);//删除临时数组
    free(R);
}

void merge_sort_helper(int arr[], int l, int r) {//辅助函数(归并)
    if (l < r) {// 递归终止条件：子数组长度 > 1
        int m = l + (r - l) / 2;
        merge_sort_helper(arr, l, m);//递归排序左半部分和右半部分,并合并已排序的子数组
        merge_sort_helper(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge_sort(int arr[], int n) {//入口函数
    merge_sort_helper(arr, 0, n - 1);
}
//快速排序递归版
/*快速排序的工作原理是通过 分治 的方式来将一个数组排序。快速排序分为三个过程：
    1.将数列划分为两部分（要求保证相对大小关系）；
    2.递归到两个子序列中分别进行快速排序；
    3.不用合并，因为此时数列已经完全有序。*/
void swap(int* a, int* b) {//此函数用于交换整数ab的值
    int temp = *a;
    *a = *b;
    *b = temp;
}

int area_cut(int arr[], int low, int high) {//分区函数：选择最后一个元素为基准，将数组分为小于基准和大于基准的两部分
    int pivot = arr[high];// 选择最后一个元素作为基准
    int i = low - 1;// i标记小于基准的子数组末尾
    for (int j = low; j < high; j++) {// 判断当前元素小于等于基准 则将当前函数交换到i的位置
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);// 将基准放到正确位置（i+1）并返回基准索引
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort_helper(int arr[], int low, int high) {//辅助函数(快排递归)
    if (low < high) {// 递归终止条件：子数组长度 > 1
        int pi = area_cut(arr, low, high);// 获取基准位置
        quick_sort_helper(arr, low, pi - 1);// 递归排序左半部分与右半部分
        quick_sort_helper(arr, pi + 1, high);
    }
}

void quick_sort(int arr[], int n) {//入口函数
    quick_sort_helper(arr, 0, n - 1);
}
//计数排序
/*计数排序的工作原理是使用一个额外的数组 C，其中第 i 个元素是待排序数组 A 中值等于 i 的元素的个数，然后根据数组 C 来将 A 中的元素排到正确的位置
它的工作过程分为三个步骤：
1.计算每个数出现了几次；
2.求出每个数出现次数的 前缀和；
3.利用出现次数的前缀和，从右至左计算每个数的排名。*/
void counting_sort(int arr[], int n) {
    if (n <= 0) return;
    // 处理空数组或无效长度,直接结束
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }

    int* count = (int*)calloc(max + 1, sizeof(int));// 创建计数数组并初始化为0
    for (int i = 0; i < n; i++) count[arr[i]]++;// 统计每个元素的出现次数
    for (int i = 1; i <= max; i++) count[i] += count[i - 1];// 累加计数数组，生成元素最终位置索引

    int* output = (int*)malloc(n * sizeof(int));//反向填充输出数组
    for (int i = n - 1; i >= 0; i--) {//将排序结果复制回原数组
        output[--count[arr[i]]] = arr[i];
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(count);
    free(output);//删除
}
//基数排序
//基数排序是一种非比较型的排序算法，它通过按位排序（通常是按个位、十位、百位等）来处理整数排序。基数排序通常使用计数排序作为其子过程。
int get_max(int arr[], int n) {//获取数组中最大值
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

void count_sort_for_radix(int arr[], int n, int exp) {//辅助函数(计数排序)
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = { 0 };

    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;//统计当前位数上的数字出现次数
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];// 累加计数数组生成位置索引
    for (int i = n - 1; i >= 0; i--) {//反向填充输出数组（保证稳定性）
        output[--count[(arr[i] / exp) % 10]] = arr[i];
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];// 将排序结果保存回原数组
    free(output);
}

void radix_sort(int arr[], int n) {//获取最大值以确定最大位数
    int max = get_max(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10) {//计数排序,从个位开始依次进行排序
        count_sort_for_radix(arr, n, exp);
    }
}