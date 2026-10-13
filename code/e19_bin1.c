#include <stdio.h>
#define SIZE 10
// 二分查找
int binarySearch(int arr[], int n, int key) {
      int low = 0, high = n - 1, mid;
     while (low <= high) {
        mid = (low + high) / 2;
             if (arr[mid] == key) {
               return mid;
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
             high = mid - 1;
        }
    }
     return -1;
}
// 递归二分查找
int binarySearchRecursive(int arr[], int low, int high, int key) {
       if (low > high) {
          return -1;
    }
      int mid = (low + high) / 2;
       if (arr[mid] == key) {
          return mid;
    } else if (arr[mid] < key) {
          return binarySearchRecursive(arr, mid + 1, high, key);
    } else {
          return binarySearchRecursive(arr, low, mid - 1, key);
    }
}
int main() {
      int arr[SIZE] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72};
      int key, result;
    printf("有序数组: ");
     for (int i = 0; i < SIZE; i++) {
         printf("%d ", arr[i]);
    }
     printf("\n");
   printf("请输入要查找的元素: ");
     scanf("%d", &key);
       // 迭代版本
     result = binarySearch(arr, SIZE, key);
       if (result != -1) {
      printf("迭代二分查找: 元素 %d 找到，位置为 %d\n", key, result);
    } else {
      printf("迭代二分查找: 元素 %d 未找到\n", key);
    }
       // 递归版本
     result = binarySearchRecursive(arr, 0, SIZE - 1, key);
       if (result != -1) {
      printf("递归二分查找: 元素 %d 找到，位置为 %d\n", key, result);
    } else {
      printf("递归二分查找: 元素 %d 未找到\n", key);
    }
     return 0;
}