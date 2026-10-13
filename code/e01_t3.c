#include <stdio.h>
int main() {
      int n, sum = 0;
   printf("请输入一个正整数: ");
     scanf("%d", &n);
     for (int i = 1; i <= n; i++) {
       sum += i; // 在此行设置断点
    }
     printf("1 到%d 的和为: %d\n", n, sum);
     return 0;
}