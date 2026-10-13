#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 10
typedef struct Record {
      int id;
     char name[20];
      int age;
} Record;
typedef struct BPlusTreeNode {
      int n;
      int keys[M];
    union {
           struct BPlusTreeNode* children[M+1]; // 内部节点使用
        Record* records[M];                                // 叶子节点使用
     };
     struct BPlusTreeNode* next;
      int isLeaf;
} BPlusTreeNode;
// 创建新节点
BPlusTreeNode* createBPlusTreeNode(int isLeaf) {
    BPlusTreeNode* newNode = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    newNode->n = 0;
    newNode->isLeaf = isLeaf;
    newNode->next = NULL;
       if (isLeaf) {
          for (int i = 0; i < M; i++) {
             newNode->records[i] = NULL;
        }
    } else {
          for (int i = 0; i < M+1; i++) {
             newNode->children[i] = NULL;
        }
    }
     return newNode;
}
// 搜索记录
Record* searchBPlusTree(BPlusTreeNode* root, int id) {
       if (root == NULL) return NULL;
      int i = 0;
     while (i < root->n && id >= root->keys[i]) {
         i++;
    }
       if (root->isLeaf) {
             i--;
             if (i >= 0 && id == root->keys[i]) {
               return root->records[i];
        }
          return NULL;
    }
     return searchBPlusTree(root->children[i], id);
}
// 插入记录
BPlusTreeNode* insertBPlusTree(BPlusTreeNode* root, Record* record) {
       // 简化实现，实际B+树插入需要处理节点分裂等复杂情况
       if (root == NULL) {
          root = createBPlusTreeNode(1);
         root->keys[0] = record->id;
          root->records[0] = record;
         root->n = 1;
          return root;
    }
       // 查找插入位置
    BPlusTreeNode* node = root;
     while (!node->isLeaf) {
           int i = 0;
         while (i < node->n && record->id >= node->keys[i]) {
              i++;
        }
        node = node->children[i];
    }
       // 在叶子节点中插入
      int pos = 0;
     while (pos < node->n && record->id > node->keys[pos]) {
         pos++;
    }
       // 移动元素腾出空间
     for (int j = node->n; j > pos; j--) {
         node->keys[j] = node->keys[j-1];
          node->records[j] = node->records[j-1];
    }
    node->keys[pos] = record->id;
     node->records[pos] = record;
    node->n++;
       // 简化处理，实际需要检查是否需要进行节点分裂
     return root;
}
// 范围查询
void rangeQuery(BPlusTreeNode* root, int start, int end) {
       if (root == NULL) return;
       // 找到包含start 的叶子节点
    BPlusTreeNode* node = root;
     while (!node->isLeaf) {
           int i = 0;
         while (i < node->n && start >= node->keys[i]) {
              i++;
        }
        node = node->children[i];
    }
       // 在叶子节点中查找
   printf("范围查询 [%d, %d] 结果:\n", start, end);
     while (node != NULL) {
          for (int i = 0; i < node->n; i++) {
                    if (node->keys[i] >= start && node->keys[i] <= end) {
                    printf("ID: %d, Name: %s, Age: %d\n",
                            node->records[i]->id,
                          node->records[i]->name,
                           node->records[i]->age);
            }
                    if (node->keys[i] > end) {
                   break;
            }
        }
        node = node->next;
    }
}
int main() {
    BPlusTreeNode* root = NULL;
       // 创建一些测试记录
    Record records[] = {
         {1001, "Alice", 25},
         {1003, "Bob", 30},
         {1002, "Charlie", 35},
         {1005, "David", 28},
         {1004, "Eve", 32},
         {1006, "Frank", 29}
     };
      int n = sizeof(records) / sizeof(records[0]);
       // 插入记录
     for (int i = 0; i < n; i++) {
          root = insertBPlusTree(root, &records[i]);
    }
       // 查找记录
      int searchId = 1003;
    Record* result = searchBPlusTree(root, searchId);
       if (result != NULL) {
       printf("找到记录: ID: %d, Name: %s, Age: %d\n",
                    result->id, result->name, result->age);
    } else {
       printf("未找到ID 为 %d 的记录\n", searchId);
    }
       // 范围查询
     rangeQuery(root, 1002, 1005);
     return 0;
}