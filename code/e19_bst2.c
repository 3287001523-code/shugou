#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Student {
      int id;
     char name[20];
     float score;
} Student;
typedef struct TreeNode {
     Student data;
     struct TreeNode *left;
     struct TreeNode *right;
} TreeNode;
// 创建新节点
TreeNode* createNode(Student student) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = student;
    newNode->left = NULL;
    newNode->right = NULL;
     return newNode;
}
// 插入节点
TreeNode* insert(TreeNode* root, Student student) {
       if (root == NULL) {
          return createNode(student);
    }
       if (student.id < root->data.id) {
          root->left = insert(root->left, student);
    } else if (student.id > root->data.id) {
          root->right = insert(root->right, student);
    }
     return root;
}
// 查找节点
TreeNode* search(TreeNode* root, int id) {
       if (root == NULL || root->data.id == id) {
          return root;
    }
       if (id < root->data.id) {
          return search(root->left, id);
    } else {
          return search(root->right, id);
    }
}
// 中序遍历
void inorderTraversal(TreeNode* root) {
       if (root != NULL) {
          inorderTraversal(root->left);
        printf("学号: %d, 姓名: %s, 成绩: %.1f\n",
                   root->data.id, root->data.name, root->data.score);
          inorderTraversal(root->right);
    }
}
int main() {
    TreeNode* root = NULL;
     Student students[] = {
         {1003, "王五", 78.5},
         {1001, "张三", 85.5},
         {1002, "李四", 92.0},
         {1005, "钱七", 95.5},
         {1004, "赵六", 88.0}
     };
      int n = sizeof(students) / sizeof(students[0]);
       // 构建二叉排序树
     for (int i = 0; i < n; i++) {
          root = insert(root, students[i]);
    }
   printf("学生信息表(按学号排序):\n");
     inorderTraversal(root);
     printf("\n");
      int targetId;
   printf("请输入要查找的学号: ");
     scanf("%d", &targetId);
    TreeNode* result = search(root, targetId);
       if (result != NULL) {
       printf("找到学生: 学号: %d, 姓名: %s, 成绩: %.1f\n",
                    result->data.id, result->data.name, result->data.score);
    } else {
      printf("未找到学号为 %d 的学生\n", targetId);
    }
     return 0;
}