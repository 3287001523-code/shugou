#include <stdio.h>
// 查找第一个等于给定值的元素
int findFirstEqual(int arr[], int n, int key) {
      int low = 0, high = n - 1, mid;
     while (low <= high) {
        mid = low + ((high - low) >> 1);
             if (arr[mid] >= key) {
             high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
       if (low < n && arr[low] == key) {
          return low;
    }
     return -1;
}
int main() {
      int arr[] = {1, 2, 2, 2, 3, 4, 4, 5, 5, 5, 6};
      int n = sizeof(arr) / sizeof(arr[0]);
      int key;
    printf("数组: ");
     for (int i = 0; i < n; i++) {
         printf("%d ", arr[i]);
    }
     printf("\n");
   printf("请输入要查找的元素: ");
     scanf("%d", &key);
      int result = findFirstEqual(arr, n, key);
       if (result != -1) {
       printf("第一个等于 %d 的元素位置为 %d\n", key, result);
    } else {
       printf("未找到元素 %d\n", key);
    }
     return 0;
}