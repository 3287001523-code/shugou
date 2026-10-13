#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 链式队列节点结构体
typedef struct QueueNode {
      int data;
     struct QueueNode *next;
} QueueNode;
// 链式队列结构体
typedef struct {
    QueueNode *front; // 队头指针
    QueueNode *rear;    // 队尾指针
} LinkedQueue;
// 初始化队列
void initQueue(LinkedQueue *q) {
     q->front = NULL;
     q->rear = NULL;
}
// 判断队列是否为空
bool isEmpty(LinkedQueue *q) {
     return q->front == NULL;
}
// 入队操作
void enQueue(LinkedQueue *q, int value) {
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
       if (!newNode) {
       printf("内存分配失败\n");
          return;
    }
    newNode->data = value;
    newNode->next = NULL;
       if (isEmpty(q)) {
          q->front = newNode;
         q->rear = newNode;
    } else {
         q->rear->next = newNode;
         q->rear = newNode;
    }
    printf("入队元素: %d\n", value);
}
// 出队操作
bool deQueue(LinkedQueue *q, int *value) {
       if (isEmpty(q)) {
      printf("队列为空，无法出队\n");
          return false;
    }
    QueueNode *temp = q->front;
    *value = temp->data;
     q->front = q->front->next;
       // 如果出队后队列为空，重置rear 指针
       if (q->front == NULL) {
         q->rear = NULL;
    }
     free(temp);
    printf("出队元素: %d\n", *value);
     return true;
}
// 获取队头元素
bool getFront(LinkedQueue *q, int *value) {
       if (isEmpty(q)) {
        printf("队列为空\n");
          return false;
    }
    *value = q->front->data;
     return true;
}
// 打印队列元素
void printQueue(LinkedQueue *q) {
       if (isEmpty(q)) {
        printf("队列为空\n");
          return;
    }
    printf("队列元素: ");
    QueueNode *current = q->front;
     while (current != NULL) {
         printf("%d ", current->data);
          current = current->next;
    }
     printf("\n");
}
// 销毁队列
void destroyQueue(LinkedQueue *q) {
      int value;
     while (!isEmpty(q)) {
         deQueue(q, &value);
    }
}
int main() {
    LinkedQueue q;
     initQueue(&q);
       // 测试入队操作
    printf("进行入队操作:\n");
     for (int i = 1; i <= 5; i++) {
        enQueue(&q, i * 10);
         printQueue(&q);
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
         printQueue(&q);
    }
     return 0;
}