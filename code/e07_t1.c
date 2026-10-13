#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 5
// 顺序队列结构体
typedef struct {
      int data[MAX_SIZE];
      int front; // 队头指针
      int rear;    // 队尾指针
} SeqQueue;
// 初始化队列
void initQueue(SeqQueue *q) {
     q->front = 0;
     q->rear = 0;
}
// 判断队列是否为空
bool isEmpty(SeqQueue *q) {
     return q->front == q->rear;
}
// 判断队列是否已满
bool isFull(SeqQueue *q) {
     return (q->rear + 1) % MAX_SIZE == q->front;
}
// 入队操作
bool enQueue(SeqQueue *q, int value) {
       if (isFull(q)) {
      printf("队列已满，无法入队\n");
          return false;
    }
     q->data[q->rear] = value;
     q->rear = (q->rear + 1) % MAX_SIZE;
     return true;
}
// 出队操作
bool deQueue(SeqQueue *q, int *value) {
       if (isEmpty(q)) {
      printf("队列为空，无法出队\n");
          return false;
    }
    *value = q->data[q->front];
     q->front = (q->front + 1) % MAX_SIZE;
     return true;
}
// 获取队头元素
bool getFront(SeqQueue *q, int *value) {
       if (isEmpty(q)) {
        printf("队列为空\n");
          return false;
    }
    *value = q->data[q->front];
     return true;
}
// 打印队列元素
void printQueue(SeqQueue *q) {
       if (isEmpty(q)) {
        printf("队列为空\n");
          return;
    }
    printf("队列元素: ");
      int i = q->front;
     while (i != q->rear) {
         printf("%d ", q->data[i]);
              i = (i + 1) % MAX_SIZE;
    }
     printf("\n");
}
int main() {
    SeqQueue q;
     initQueue(&q);
       // 测试入队操作
    printf("进行入队操作:\n");
     for (int i = 1; i <= 5; i++) {
             if (enQueue(&q, i * 10)) {
           printf("入队元素: %d\n", i * 10);
             printQueue(&q);
        }
    }
       // 测试获取队头元素
      int frontValue;
       if (getFront(&q, &frontValue)) {
       printf("队头元素: %d\n", frontValue);
    }
       // 测试出队操作
     printf("\n 进行出队操作:\n");
      int deValue;
     while (!isEmpty(&q)) {
        deQueue(&q, &deValue);
       printf("出队元素: %d\n", deValue);
         printQueue(&q);
    }
     return 0;
}