#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 100
// 客户结构体
typedef struct {
      int id;                  // 客户编号
      int arrivalTime; // 到达时间
      int serviceTime; // 所需服务时间
} Customer;
// 队列结构体
typedef struct {
    Customer data[MAX_SIZE];
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
bool enQueue(Queue *q, Customer customer) {
       if (isFull(q)) {
          return false;
    }
     q->data[q->rear] = customer;
     q->rear = (q->rear + 1) % MAX_SIZE;
     return true;
}
// 出队操作
bool deQueue(Queue *q, Customer *customer) {
       if (isEmpty(q)) {
          return false;
    }
    *customer = q->data[q->front];
     q->front = (q->front + 1) % MAX_SIZE;
     return true;
}
// 模拟银行排队系统
void bankSimulation() {
    Queue queue;
    initQueue(&queue);
      int currentTime = 0;           // 当前时间
      int totalCustomers = 0;     // 总客户数
      int totalWaitTime = 0;       // 总等待时间
       // 添加一些客户到队列中
    Customer customers[] = {
          {1, 0, 5},
          {2, 1, 3},
          {3, 2, 8},
          {4, 3, 6},
          {5, 5, 4}
     };
      int numCustomers = sizeof(customers) / sizeof(customers[0]);
       // 将所有客户加入队列
     for (int i = 0; i < numCustomers; i++) {
        enQueue(&queue, customers[i]);
    }
   printf("银行排队模拟开始:\n");
    printf("时间\t 事件\n");
       // 处理队列中的客户
     while (!isEmpty(&queue)) {
        Customer currentCustomer;
        deQueue(&queue, &currentCustomer);
              // 计算等待时间
           int waitTime = currentTime - currentCustomer.arrivalTime;
             if (waitTime < 0) {
             waitTime = 0;
             currentTime = currentCustomer.arrivalTime;
        }
         totalWaitTime += waitTime;
         totalCustomers++;
          printf("%d\t 客户%d 到达，等待时间: %d\n",
                  currentCustomer.arrivalTime, currentCustomer.id, waitTime);
          printf("%d\t 开始为客户%d 服务，服务时间: %d\n",
                 currentTime, currentCustomer.id, currentCustomer.serviceTime);
              // 更新当前时间
         currentTime += currentCustomer.serviceTime;
          printf("%d\t 客户%d 服务完成\n", currentTime, currentCustomer.id);
    }
       // 计算平均等待时间
    double averageWaitTime = (double)totalWaitTime / totalCustomers;
     printf("\n 总客户数: %d\n", totalCustomers);
   printf("总等待时间: %d\n", totalWaitTime);
   printf("平均等待时间: %.2f\n", averageWaitTime);
}
int main() {
     bankSimulation();
     return 0;
}