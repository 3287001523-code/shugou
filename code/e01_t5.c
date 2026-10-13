#include <stdio.h>
#define SIZE 10
int main() {
      int arr[SIZE];
    printf("请输入%d 个整数: ", SIZE);
     for (int i = 0; i < SIZE; i++) {
         scanf("%d", &arr[i]);
    }
    printf("逆序输出: ");
     for (int i = SIZE - 1; i >= 0; i--) {
         printf("%d ", arr[i]);
    }
     printf("\n");
     return 0;
}