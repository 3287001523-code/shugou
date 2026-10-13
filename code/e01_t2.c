#include <stdio.h>
int main() {
      int a, b;
   printf("请输入两个整数: ");
    scanf("%d %d", &a, &b);
     printf("和: %d\n", a + b);
     printf("差: %d\n", a - b);
     printf("积: %d\n", a * b);
       if (b != 0) {
         printf("商: %.2f\n", (float)a / b);
        printf("余数: %d\n", a % b);
    } else {
       printf("除数不能为0!\n");
    }
     return 0;
}