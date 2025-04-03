
#include "header.h"
//��������
/*����������һ���ȶ������򷽷�,����ʱ�临�Ӷ�Ϊ O(n)�������м�������ʱЧ�ʺܸߡ�
    ����������ʱ�临�ӶȺ�ƽ��ʱ�临�Ӷȶ�Ϊ O(n^2)��*/
void insertion_sort(int arr[], int n) {
    int i, j, key;
    //�ӵڶ���Ԫ�ؿ�ʼ������i=1������Ϊ��һ��Ԫ��Ĭ��Ϊ������ ������
    for (i = 1; i < n; i++) {
        key = arr[i];// ��ǰ������Ԫ��
        j = i - 1;// �������򲿷ֵ�ĩβ��ʼ�Ƚ�
        while (j >= 0 && arr[j] > key) {// ����key���Ԫ�������ƶ���Ϊkey�ڳ�����λ��
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;// ����key����ȷλ��
    }
}
//�鲢����
/*�鲢������ڷ���˼�뽫����ֶ������ϲ���ʱ�临�Ӷ������š����ƽ������¾�Ϊ O(nlogn)��
    �ռ临�Ӷ�ΪO(n)���鲢�������ֻʹ�� O (1) �ĸ����ռ䣬��Ϊ���ͨ��ʹ����ԭ����ȳ��ĸ������顣*/
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;//�������鳤�����������鳤��
    int n2 = r - m;
    int* L = (int*)malloc(n1 * sizeof(int));//��̬������ʱ����洢��������
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];//�����ݴ洢����ʱ������
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;//�ϲ���ʱ���鵽ԭ���� ���� i��������ָ��j��������ָ��k��ԭ����ָ��
    while (i < n1 && j < n2) {  // ѡ���С��Ԫ�ط���ԭ����
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) arr[k++] = L[i++];//����ʣ��Ԫ��
    while (j < n2) arr[k++] = R[j++];

    free(L);//ɾ����ʱ����
    free(R);
}

void merge_sort_helper(int arr[], int l, int r) {//��������(�鲢)
    if (l < r) {// �ݹ���ֹ�����������鳤�� > 1
        int m = l + (r - l) / 2;
        merge_sort_helper(arr, l, m);//�ݹ�������벿�ֺ��Ұ벿��,���ϲ��������������
        merge_sort_helper(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge_sort(int arr[], int n) {//��ں���
    merge_sort_helper(arr, 0, n - 1);
}
//��������ݹ��
/*��������Ĺ���ԭ����ͨ�� ���� �ķ�ʽ����һ���������򡣿��������Ϊ�������̣�
    1.�����л���Ϊ�����֣�Ҫ��֤��Դ�С��ϵ����
    2.�ݹ鵽�����������зֱ���п�������
    3.���úϲ�����Ϊ��ʱ�����Ѿ���ȫ����*/
void swap(int* a, int* b) {//�˺������ڽ�������ab��ֵ
    int temp = *a;
    *a = *b;
    *b = temp;
}

int area_cut(int arr[], int low, int high) {//����������ѡ�����һ��Ԫ��Ϊ��׼���������ΪС�ڻ�׼�ʹ��ڻ�׼��������
    int pivot = arr[high];// ѡ�����һ��Ԫ����Ϊ��׼
    int i = low - 1;// i���С�ڻ�׼��������ĩβ
    for (int j = low; j < high; j++) {// �жϵ�ǰԪ��С�ڵ��ڻ�׼ �򽫵�ǰ����������i��λ��
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);// ����׼�ŵ���ȷλ�ã�i+1�������ػ�׼����
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort_helper(int arr[], int low, int high) {//��������(���ŵݹ�)
    if (low < high) {// �ݹ���ֹ�����������鳤�� > 1
        int pi = area_cut(arr, low, high);// ��ȡ��׼λ��
        quick_sort_helper(arr, low, pi - 1);// �ݹ�������벿�����Ұ벿��
        quick_sort_helper(arr, pi + 1, high);
    }
}

void quick_sort(int arr[], int n) {//��ں���
    quick_sort_helper(arr, 0, n - 1);
}
//��������
/*��������Ĺ���ԭ����ʹ��һ����������� C�����е� i ��Ԫ���Ǵ��������� A ��ֵ���� i ��Ԫ�صĸ�����Ȼ��������� C ���� A �е�Ԫ���ŵ���ȷ��λ��
���Ĺ������̷�Ϊ�������裺
1.����ÿ���������˼��Σ�
2.���ÿ�������ִ����� ǰ׺�ͣ�
3.���ó��ִ�����ǰ׺�ͣ������������ÿ������������*/
void counting_sort(int arr[], int n) {
    if (n <= 0) return;
    // ������������Ч����,ֱ�ӽ���
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }

    int* count = (int*)calloc(max + 1, sizeof(int));// �����������鲢��ʼ��Ϊ0
    for (int i = 0; i < n; i++) count[arr[i]]++;// ͳ��ÿ��Ԫ�صĳ��ִ���
    for (int i = 1; i <= max; i++) count[i] += count[i - 1];// �ۼӼ������飬����Ԫ������λ������

    int* output = (int*)malloc(n * sizeof(int));//��������������
    for (int i = n - 1; i >= 0; i--) {//�����������ƻ�ԭ����
        output[--count[arr[i]]] = arr[i];
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(count);
    free(output);//ɾ��
}
//��������
//����������һ�ַǱȽ��͵������㷨����ͨ����λ����ͨ���ǰ���λ��ʮλ����λ�ȣ��������������򡣻�������ͨ��ʹ�ü���������Ϊ���ӹ��̡�
int get_max(int arr[], int n) {//��ȡ���������ֵ
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

void count_sort_for_radix(int arr[], int n, int exp) {//��������(��������)
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = { 0 };

    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;//ͳ�Ƶ�ǰλ���ϵ����ֳ��ִ���
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];// �ۼӼ�����������λ������
    for (int i = n - 1; i >= 0; i--) {//�������������飨��֤�ȶ��ԣ�
        output[--count[(arr[i] / exp) % 10]] = arr[i];
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];// �������������ԭ����
    free(output);
}

void radix_sort(int arr[], int n) {//��ȡ���ֵ��ȷ�����λ��
    int max = get_max(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10) {//��������,�Ӹ�λ��ʼ���ν�������
        count_sort_for_radix(arr, n, exp);
    }
}