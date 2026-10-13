#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100
// 队列结构体
typedef struct {
      int data[MAX_SIZE];
      int front, rear;
} Queue;
// 初始化队列
void initQueue(Queue *q) {
     q->front = 0;
     q->rear = 0;
}
// 判断队列是否为空
bool isEmpty(Queue *q) {
     return q->front == q->rear;
}
// 判断队列是否已满
bool isFull(Queue *q) {
     return (q->rear + 1) % MAX_SIZE == q->front;
}
// 入队操作
bool enQueue(Queue *q, int value) {
       if (isFull(q)) {
          return false;
    }
     q->data[q->rear] = value;
     q->rear = (q->rear + 1) % MAX_SIZE;
     return true;
}
// 出队操作
bool deQueue(Queue *q, int *value) {
       if (isEmpty(q)) {
          return false;
    }
    *value = q->data[q->front];
     q->front = (q->front + 1) % MAX_SIZE;
     return true;
}
// 获取数组中的最大值
int getMax(int arr[], int n) {
      int max = arr[0];
     for (int i = 1; i < n; i++) {
             if (arr[i] > max) {
          max = arr[i];
        }
    }
     return max;
}
// 基数排序
void radixSort(int arr[], int n) {
       // 创建10 个队列（0-9）
    Queue queues[10];
     for (int i = 0; i < 10; i++) {
         initQueue(&queues[i]);
    }
       // 获取最大值，确定最大位数
      int max = getMax(arr, n);
       // 从个位开始，对每一位进行排序
     for (int exp = 1; max / exp > 0; exp *= 10) {
              // 将数组中的元素分配到对应的队列中
          for (int i = 0; i < n; i++) {
                 int digit = (arr[i] / exp) % 10;
              enQueue(&queues[digit], arr[i]);
        }
              // 从队列中收集元素
           int index = 0;
          for (int i = 0; i < 10; i++) {
              while (!isEmpty(&queues[i])) {
                       int value;
                  deQueue(&queues[i], &value);
                   arr[index++] = value;
            }
        }
              // 打印每一轮排序的结果
        printf("按第%d 位排序后: ", exp == 1 ? 1 : (exp == 10 ? 2 : 3));
          for (int i = 0; i < n; i++) {
              printf("%d ", arr[i]);
        }
           printf("\n");
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
      int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
      int n = sizeof(arr) / sizeof(arr[0]);
    printf("原始数组: ");
     printArray(arr, n);
     printf("\n");
     radixSort(arr, n);
     printf("\n 排序后数组: ");
     printArray(arr, n);
     return 0;
}