#include <stdio.h>
#include <stdlib.h>
#define M 3    // B+树的阶
typedef struct BPlusTreeNode {
      int n;                                             // 当前关键字个数
      int keys[M];                                  // 关键字数组
     struct BPlusTreeNode* children[M+1]; // 子节点指针数组
     struct BPlusTreeNode* next;       // 指向下一个叶子节点
      int isLeaf;                                    // 是否是叶子节点
} BPlusTreeNode;
// 创建新节点
BPlusTreeNode* createBPlusTreeNode(int isLeaf) {
    BPlusTreeNode* newNode = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    newNode->n = 0;
    newNode->isLeaf = isLeaf;
    newNode->next = NULL;
     for (int i = 0; i < M+1; i++) {
         newNode->children[i] = NULL;
    }
     return newNode;
}
// 搜索关键字
BPlusTreeNode* searchBPlusTree(BPlusTreeNode* root, int key, int* index) {
      int i = 0;
     while (i < root->n && key >= root->keys[i]) {
         i++;
    }
       if (root->isLeaf) {
             i--;
             if (i >= 0 && key == root->keys[i]) {
             *index = i;
               return root;
        }
          return NULL;
    }
     return searchBPlusTree(root->children[i], key, index);
}
// 分裂节点
void splitNode(BPlusTreeNode* parent, int pos, BPlusTreeNode* child) {
    BPlusTreeNode* newNode = createBPlusTreeNode(child->isLeaf);
      int splitPos = (M + 1) / 2;
    newNode->n = M - splitPos;
     for (int i = 0; i < newNode->n; i++) {
         newNode->keys[i] = child->keys[splitPos + i];
         newNode->children[i] = child->children[splitPos + i];
    }
    newNode->children[newNode->n] = child->children[M];
       if (child->isLeaf) {
        newNode->next = child->next;
          child->next = newNode;
              // 叶子节点分裂时，中间关键字会复制到父节点
          for (int i = parent->n; i > pos; i--) {
               parent->keys[i] = parent->keys[i-1];
               parent->children[i+1] = parent->children[i];
        }
         parent->keys[pos] = newNode->keys[0];
         parent->children[pos+1] = newNode;
         parent->n++;
    } else {
              // 内部节点分裂时，中间关键字会上移到父节点
          for (int i = parent->n; i > pos; i--) {
               parent->keys[i] = parent->keys[i-1];
               parent->children[i+1] = parent->children[i];
        }
         parent->keys[pos] = child->keys[splitPos - 1];
         parent->children[pos+1] = newNode;
         parent->n++;
    }
     child->n = splitPos - (child->isLeaf ? 0 : 1);
}
// 插入关键字
BPlusTreeNode* insertBPlusTree(BPlusTreeNode* root, int key) {
       if (root == NULL) {
          root = createBPlusTreeNode(1);
         root->keys[0] = key;
         root->n = 1;
          return root;
    }
       // 如果根节点已满，需要分裂
       if (root->n == M) {
        BPlusTreeNode* newRoot = createBPlusTreeNode(0);
         newRoot->children[0] = root;
         splitNode(newRoot, 0, root);
              // 确定插入到哪个子节点
           int i = 0;
             if (key >= newRoot->keys[0]) {
              i++;
        }
              // 递归插入
        BPlusTreeNode* child = newRoot->children[i];
             if (child->isLeaf) {
                      // 叶子节点插入
                 int pos = 0;
              while (pos < child->n && key > child->keys[pos]) {
                 pos++;
            }
               for (int j = child->n; j > pos; j--) {
                    child->keys[j] = child->keys[j-1];
            }
              child->keys[pos] = key;
              child->n++;
                      // 如果叶子节点已满，需要分裂
                    if (child->n == M) {
                  splitNode(newRoot, i, child);
            }
        } else {
                      // 内部节点处理略复杂，这里简化处理
        }
          return newRoot;
    } else {
              // 根节点未满的处理
              // 简化处理，实际实现需要递归插入
             if (root->isLeaf) {
                 int pos = 0;
              while (pos < root->n && key > root->keys[pos]) {
                 pos++;
            }
               for (int j = root->n; j > pos; j--) {
                    root->keys[j] = root->keys[j-1];
            }
              root->keys[pos] = key;
              root->n++;
        }
          return root;
    }
}
// 打印B+树
void printBPlusTree(BPlusTreeNode* root, int level) {
       if (root != NULL) {
          printf("Level %d: ", level);
          for (int i = 0; i < root->n; i++) {
              printf("%d ", root->keys[i]);
        }
           printf("\n");
             if (!root->isLeaf) {
               for (int i = 0; i <= root->n; i++) {
                    printBPlusTree(root->children[i], level + 1);
            }
        }
    }
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
   printf("范围查询 [%d, %d] 结果: ", start, end);
     while (node != NULL) {
          for (int i = 0; i < node->n; i++) {
                    if (node->keys[i] >= start && node->keys[i] <= end) {
                   printf("%d ", node->keys[i]);
            }
                    if (node->keys[i] > end) {
                   break;
            }
        }
        node = node->next;
    }
     printf("\n");
}
int main() {
    BPlusTreeNode* root = NULL;
      int keys[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 1, 8, 25};
      int n = sizeof(keys) / sizeof(keys[0]);
     for (int i = 0; i < n; i++) {
          root = insertBPlusTree(root, keys[i]);
        printf("插入 %d 后的B+树:\n", keys[i]);
          printBPlusTree(root, 0);
           printf("\n");
    }
      int searchKey = 12;
      int index;
    BPlusTreeNode* result = searchBPlusTree(root, searchKey, &index);
       if (result != NULL) {
       printf("关键字 %d 在叶子节点中位置 %d\n", searchKey, index);
    } else {
       printf("关键字 %d 未找到\n", searchKey);
    }
       // 范围查询
     rangeQuery(root, 5, 20);
     return 0;
}