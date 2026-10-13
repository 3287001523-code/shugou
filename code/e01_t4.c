#include <stdio.h>
long long factorial(int n) {
       if (n == 0 || n == 1)
          return 1;
     else
          return n * factorial(n - 1);
}
int main() {
      int num;
   printf("请输入一个整数: ");
     scanf("%d", &num);
       if (num < 0) {
        printf("错误: 阶乘未定义负数!\n");
    } else {
          printf("%d! = %lld\n", num, factorial(num));
    }
     return 0;
}