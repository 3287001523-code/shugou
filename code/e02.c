#include <stdio.h>
#include <time.h>
#include <stdlib.h>
// 题目1：常数时间复杂度 O(1)
int square(int x) {
     return x * x;
}
// 题目2：线性时间复杂度 O(n)
long long arrayProduct(int arr[], int n) {
    long long product = 1;
     for (int i = 0; i < n; i++) {
         product *= arr[i];
    }
     return product;
}
// 题目3：对数时间复杂度 O(log n)
int countBinaryDigits(int n) {
      int count = 0;
     while (n > 0) {
         count++;
        n /= 2;
    }
     return count;
}
// 题目4：线性对数时间复杂度 O(n log n)
long long power(int x, int n) {
       if (n == 0) return 1;
       if (n % 2 == 0) {
         long long half = power(x, n/2);
          return half * half;
    } else {
          return x * power(x, n-1);
    }
}
// 题目5：平方时间复杂度 O(n²)
void matrixMultiply(int n, int A[][100], int B[][100], int C[][100]) {
     for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
                C[i][j] = 0;
               for (int k = 0; k < n; k++) {
                      C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
// 测试函数
void testO1() {
    printf("测试O(1)时间复杂度:\n");
     clock_t start, end;
    double cpu_time_used;
      start = clock();
      int result = square(12345);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("结果: %d, 执行时间: %.8f 秒\n", result, cpu_time_used);
}
void testON() {
     printf("\n 测试O(n)时间复杂度:\n");
     for (int size = 100; size <= 1000000; size *= 10) {
           int *arr = (int*)malloc(size * sizeof(int));
          for (int i = 0; i < size; i++) {
                  arr[i] = 1 + (i % 10); // 避免乘积溢出太大
        }
          clock_t start = clock();
         long long product = arrayProduct(arr, size);
          clock_t end = clock();
         double time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
       printf("数组大小: %d, 执行时间: %.6f 秒\n", size, time_used);
           free(arr);
    }
}
void testOLogN() {
     printf("\n 测试O(log n)时间复杂度:\n");
     for (int n = 10; n <= 1000000000; n *= 100) {
          clock_t start = clock();
           int digits = countBinaryDigits(n);
          clock_t end = clock();
         double time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
          printf("n = %d, 二进制位数: %d, 执行时间: %.8f 秒\n", n, digits, time_used);
    }
}
void testONLogN() {
     printf("\n 测试O(n log n)时间复杂度:\n");
     for (int n = 10; n <= 1000000; n *= 10) {
          clock_t start = clock();
         long long result = power(2, n);
          clock_t end = clock();
         double time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
         printf("2^%d, 执行时间: %.6f 秒\n", n, time_used);
    }
}
void testON2() {
     printf("\n 测试O(n²)时间复杂度:\n");
     for (int n = 10; n <= 200; n += 40) {
           int A[210][210], B[210][210], C[210][210];
              // 初始化矩阵
          for (int i = 0; i < n; i++) {
               for (int j = 0; j < n; j++) {
                     A[i][j] = i + j;
                      B[i][j] = i - j;
            }
        }
          clock_t start = clock();
         matrixMultiply(n, A, B, C);
          clock_t end = clock();
         double time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
       printf("矩阵大小: %dx%d, 执行时间: %.6f 秒\n", n, n, time_used);
    }
}
int main() {
     testO1();
     testON();
    testOLogN();
    testONLogN();
     testON2();
     return 0;
}