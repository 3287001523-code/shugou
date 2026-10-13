#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define SIZE 15
#define BLOCK_SIZE 5
#define BLOCK_NUM 3
typedef struct {
      int maxValue;    // 块内最大值
      int start;         // 块起始位置
      int end;             // 块结束位置
} Block;
// 分块查找
int blockSearch(int arr[], Block blocks[], int key) {
       // 首先确定key 所在的块
      int blockIndex = -1;
     for (int i = 0; i < BLOCK_NUM; i++) {
             if (key <= blocks[i].maxValue) {
             blockIndex = i;
              break;
        }
    }
       if (blockIndex == -1) {
          return -1; // 不在任何块中
    }
       // 在确定的块中顺序查找
     for (int i = blocks[blockIndex].start; i <= blocks[blockIndex].end; i++) {
             if (arr[i] == key) {
               return i;
        }
    }
     return -1;
}
int main() {
      int arr[SIZE] = {9, 10, 13, 5, 8, 20, 25, 18, 22, 30, 35, 40, 28, 32, 38};
    Block blocks[BLOCK_NUM];
       // 初始化块信息
     blocks[0].start = 0;
     blocks[0].end = 4;
    blocks[0].maxValue = 13;
     blocks[1].start = 5;
     blocks[1].end = 9;
    blocks[1].maxValue = 30;
     blocks[2].start = 10;
     blocks[2].end = 14;
    blocks[2].maxValue = 40;
    printf("数组: ");
     for (int i = 0; i < SIZE; i++) {
         printf("%d ", arr[i]);
    }
     printf("\n");
    printf("块信息:\n");
     for (int i = 0; i < BLOCK_NUM; i++) {
         printf("块%d: 最大值=%d, 范围[%d,%d]\n",
                            i, blocks[i].maxValue, blocks[i].start, blocks[i].end);
    }
      int key;
   printf("请输入要查找的元素: ");
     scanf("%d", &key);
      int result = blockSearch(arr, blocks, key);
       if (result != -1) {
        printf("元素 %d 找到，位置为 %d\n", key, result);
    } else {
        printf("元素 %d 未找到\n", key);
    }
     return 0;
}