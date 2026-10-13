#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 5
typedef struct {
      int id;
     char name[20];
     float score;
} Student;
// 顺序查找学生信息
int searchStudent(Student students[], int n, int targetId) {
     for (int i = 0; i < n; i++) {
             if (students[i].id == targetId) {
               return i;
        }
    }
     return -1;
}
int main() {
     Student students[MAX_STUDENTS] = {
         {1001, "张三", 85.5},
         {1002, "李四", 92.0},
         {1003, "王五", 78.5},
         {1004, "赵六", 88.0},
         {1005, "钱七", 95.5}
     };
      int targetId, result;
    printf("学生信息表:\n");
     for (int i = 0; i < MAX_STUDENTS; i++) {
        printf("学号: %d, 姓名: %s, 成绩: %.1f\n",
                    students[i].id, students[i].name, students[i].score);
    }
     printf("\n 请输入要查找的学号: ");
     scanf("%d", &targetId);
     result = searchStudent(students, MAX_STUDENTS, targetId);
       if (result != -1) {
       printf("找到学生: 学号: %d, 姓名: %s, 成绩: %.1f\n",
                    students[result].id, students[result].name, students[result].score);
    } else {
      printf("未找到学号为 %d 的学生\n", targetId);
    }
     return 0;
}