#include <stdio.h>
#include <stdlib.h>
#define M 3    // B 树的阶
typedef struct BTreeNode {
      int n;                                             // 当前关键字个数
      int keys[M];                                  // 关键字数组
     struct BTreeNode* children[M+1]; // 子节点指针数组
      int isLeaf;                                    // 是否是叶子节点
} BTreeNode;
// 创建新节点
BTreeNode* createBTreeNode(int isLeaf) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->n = 0;
    newNode->isLeaf = isLeaf;
     for (int i = 0; i < M+1; i++) {
         newNode->children[i] = NULL;
    }
     return newNode;
}
// 搜索关键字
BTreeNode* searchBTree(BTreeNode* root, int key, int* index) {
      int i = 0;
     while (i < root->n && key > root->keys[i]) {
         i++;
    }
       if (i < root->n && key == root->keys[i]) {
         *index = i;
          return root;
    }
       if (root->isLeaf) {
          return NULL;
    }
     return searchBTree(root->children[i], key, index);
}
// 分裂子节点
void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
    BTreeNode* newNode = createBTreeNode(child->isLeaf);
    newNode->n = M / 2;
       // 复制后半部分关键字到新节点
     for (int j = 0; j < M/2; j++) {
         newNode->keys[j] = child->keys[j + M/2 + 1];
    }
       // 如果不是叶子节点，复制后半部分子节点指针
       if (!child->isLeaf) {
          for (int j = 0; j < M/2 + 1; j++) {
             newNode->children[j] = child->children[j + M/2 + 1];
        }
    }
     child->n = M / 2;
       // 为父节点腾出空间
     for (int j = parent->n; j >= i+1; j--) {
          parent->children[j+1] = parent->children[j];
    }
     parent->children[i+1] = newNode;
     for (int j = parent->n-1; j >= i; j--) {
         parent->keys[j+1] = parent->keys[j];
    }
     parent->keys[i] = child->keys[M/2];
     parent->n++;
}
// 插入关键字（非满节点）
void insertNonFull(BTreeNode* node, int key) {
      int i = node->n - 1;
       if (node->isLeaf) {
         while (i >= 0 && key < node->keys[i]) {
             node->keys[i+1] = node->keys[i];
                    i--;
        }
         node->keys[i+1] = key;
        node->n++;
    } else {
         while (i >= 0 && key < node->keys[i]) {
                    i--;
        }
         i++;
             if (node->children[i]->n == M) {
               splitChild(node, i, node->children[i]);
                    if (key > node->keys[i]) {
                   i++;
            }
        }
          insertNonFull(node->children[i], key);
    }
}
// 插入关键字
BTreeNode* insertBTree(BTreeNode* root, int key) {
       if (root == NULL) {
          root = createBTreeNode(1);
         root->keys[0] = key;
         root->n = 1;
          return root;
    }
       if (root->n == M) {
        BTreeNode* newRoot = createBTreeNode(0);
         newRoot->children[0] = root;
         splitChild(newRoot, 0, root);
           int i = 0;
             if (newRoot->keys[0] < key) {
              i++;
        }
         insertNonFull(newRoot->children[i], key);
          return newRoot;
    } else {
          insertNonFull(root, key);
          return root;
    }
}
// 打印B 树
void printBTree(BTreeNode* root, int level) {
       if (root != NULL) {
          printf("Level %d: ", level);
          for (int i = 0; i < root->n; i++) {
              printf("%d ", root->keys[i]);
        }
           printf("\n");
             if (!root->isLeaf) {
               for (int i = 0; i <= root->n; i++) {
                    printBTree(root->children[i], level + 1);
            }
        }
    }
}
int main() {
    BTreeNode* root = NULL;
      int keys[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 1, 8, 25};
      int n = sizeof(keys) / sizeof(keys[0]);
     for (int i = 0; i < n; i++) {
          root = insertBTree(root, keys[i]);
        printf("插入 %d 后的B 树:\n", keys[i]);
          printBTree(root, 0);
           printf("\n");
    }
      int searchKey = 12;
      int index;
    BTreeNode* result = searchBTree(root, searchKey, &index);
       if (result != NULL) {
       printf("关键字 %d 在节点中位置 %d\n", searchKey, index);
    } else {
       printf("关键字 %d 未找到\n", searchKey);
    }
     return 0;
}