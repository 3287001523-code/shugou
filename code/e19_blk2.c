#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 9
#define BLOCK_SIZE 3
#define BLOCK_NUM 3
typedef struct {
      int id;
     char name[20];
     float score;
} Student;
typedef struct {
      int maxId;       // 块内最大学号
      int start;       // 块起始位置
      int end;           // 块结束位置
} Block;
// 分块查找学生信息
int blockSearchStudent(Student students[], Block blocks[], int targetId) {
       // 确定目标学号所在的块
      int blockIndex = -1;
     for (int i = 0; i < BLOCK_NUM; i++) {
             if (targetId <= blocks[i].maxId) {
             blockIndex = i;
              break;
        }
    }
       if (blockIndex == -1) {
          return -1; // 不在任何块中
    }
       // 在确定的块中顺序查找
     for (int i = blocks[blockIndex].start; i <= blocks[blockIndex].end; i++) {
             if (students[i].id == targetId) {
               return i;
        }
    }
     return -1;
}
int main() {
     Student students[MAX_STUDENTS] = {
         {1001, "张三", 85.5},
         {1003, "王五", 78.5},
         {1002, "李四", 92.0},
         {1005, "钱七", 95.5},
         {1004, "赵六", 88.0},
         {1006, "孙八", 76.5},
         {1008, "周十", 89.0},
         {1009, "吴十一", 91.5},
         {1007, "郑九", 83.0}
     };
    Block blocks[BLOCK_NUM];
       // 初始化块信息
     blocks[0].start = 0;
     blocks[0].end = 2;
     blocks[0].maxId = 1003;
     blocks[1].start = 3;
     blocks[1].end = 5;
     blocks[1].maxId = 1006;
     blocks[2].start = 6;
     blocks[2].end = 8;
     blocks[2].maxId = 1009;
    printf("学生信息表:\n");
     for (int i = 0; i < MAX_STUDENTS; i++) {
        printf("学号: %d, 姓名: %s, 成绩: %.1f\n",
                    students[i].id, students[i].name, students[i].score);
    }
     printf("\n 块信息:\n");
     for (int i = 0; i < BLOCK_NUM; i++) {
         printf("块%d: 最大学号=%d, 范围[%d,%d]\n",
                            i, blocks[i].maxId, blocks[i].start, blocks[i].end);
    }
      int targetId;
     printf("\n 请输入要查找的学号: ");
     scanf("%d", &targetId);
      int result = blockSearchStudent(students, blocks, targetId);
       if (result != -1) {
       printf("找到学生: 学号: %d, 姓名: %s, 成绩: %.1f\n",
                    students[result].id, students[result].name, students[result].score);
    } else {
      printf("未找到学号为 %d 的学生\n", targetId);
    }
     return 0;
}