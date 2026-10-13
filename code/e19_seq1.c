#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 20
// 顺序查找
int sequentialSearch(int arr[], int n, int key) {
     for (int i = 0; i < n; i++) {
             if (arr[i] == key) {
               return i; // 找到返回索引
        }
    }
     return -1; // 未找到返回-1
}
// 生成随机数组
void generateRandomArray(int arr[], int n) {
    srand(time(NULL));
     for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100;
    }
}
// 打印数组
void printArray(int arr[], int n) {
     for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
     printf("\n");
}
int main() {
      int arr[SIZE];
      int key, result;
    generateRandomArray(arr, SIZE);
   printf("生成的数组: ");
     printArray(arr, SIZE);
   printf("请输入要查找的元素: ");
     scanf("%d", &key);
     result = sequentialSearch(arr, SIZE, key);
       if (result != -1) {
        printf("元素 %d 找到，位置为 %d\n", key, result);
    } else {
        printf("元素 %d 未找到\n", key);
    }
     return 0;
}