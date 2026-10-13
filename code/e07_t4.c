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
// 获取队头元素但不删除
bool getFront(Queue *q, int *value) {
       if (isEmpty(q)) {
          return false;
    }
    *value = q->data[q->front];
     return true;
}
// 打印杨辉三角
void printPascalTriangle(int n) {
       if (n <= 0) return;
    Queue queue;
    initQueue(&queue);
       // 第一行
    enQueue(&queue, 1);
   printf("杨辉三角前%d 行:\n", n);
     for (int i = 0; i < n; i++) {
              // 打印每行前面的空格
          for (int j = 0; j < n - i - 1; j++) {
                printf("   ");
        }
              // 用于计算下一行的值
           int pre = 0, cur = 0;
              // 打印当前行并计算下一行
          for (int j = 0; j <= i; j++) {
            deQueue(&queue, &cur);
              printf("%4d", cur);
                      // 计算下一行的值并入队
                 int next = pre + cur;
              pre = cur;
            enQueue(&queue, next);
        }
              // 每行最后一个1
        enQueue(&queue, 1);
           printf("\n");
    }
}
int main() {
      int n;
   printf("请输入要打印的杨辉三角行数: ");
     scanf("%d", &n);
     printPascalTriangle(n);
     return 0;
}