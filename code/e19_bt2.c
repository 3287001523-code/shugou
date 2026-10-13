#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 3
typedef struct FileEntry {
      int inode;                  // 文件inode 号
     char name[20];           // 文件名
      int size;                    // 文件大小
} FileEntry;
typedef struct BTreeNode {
      int n;                                             // 当前关键字个数
     FileEntry entries[M];                  // 文件条目数组
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
// 搜索文件
BTreeNode* searchBTree(BTreeNode* root, int inode, int* index) {
      int i = 0;
     while (i < root->n && inode > root->entries[i].inode) {
         i++;
    }
       if (i < root->n && inode == root->entries[i].inode) {
         *index = i;
          return root;
    }
       if (root->isLeaf) {
          return NULL;
    }
     return searchBTree(root->children[i], inode, index);
}
// 分裂子节点
void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
    BTreeNode* newNode = createBTreeNode(child->isLeaf);
    newNode->n = M / 2;
       // 复制后半部分条目到新节点
     for (int j = 0; j < M/2; j++) {
         newNode->entries[j] = child->entries[j + M/2 + 1];
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
          parent->entries[j+1] = parent->entries[j];
    }
     parent->entries[i] = child->entries[M/2];
     parent->n++;
}
// 插入条目（非满节点）
void insertNonFull(BTreeNode* node, FileEntry entry) {
      int i = node->n - 1;
       if (node->isLeaf) {
         while (i >= 0 && entry.inode < node->entries[i].inode) {
              node->entries[i+1] = node->entries[i];
                    i--;
        }
          node->entries[i+1] = entry;
        node->n++;
    } else {
         while (i >= 0 && entry.inode < node->entries[i].inode) {
                    i--;
        }
         i++;
             if (node->children[i]->n == M) {
               splitChild(node, i, node->children[i]);
                    if (entry.inode > node->entries[i].inode) {
                   i++;
            }
        }
          insertNonFull(node->children[i], entry);
    }
}
// 插入条目
BTreeNode* insertBTree(BTreeNode* root, FileEntry entry) {
       if (root == NULL) {
          root = createBTreeNode(1);
          root->entries[0] = entry;
         root->n = 1;
          return root;
    }
       if (root->n == M) {
        BTreeNode* newRoot = createBTreeNode(0);
         newRoot->children[0] = root;
         splitChild(newRoot, 0, root);
           int i = 0;
             if (newRoot->entries[0].inode < entry.inode) {
              i++;
        }
         insertNonFull(newRoot->children[i], entry);
          return newRoot;
    } else {
          insertNonFull(root, entry);
          return root;
    }
}
// 打印B 树
void printBTree(BTreeNode* root, int level) {
       if (root != NULL) {
          printf("Level %d: ", level);
          for (int i = 0; i < root->n; i++) {
              printf("(%d,%s) ", root->entries[i].inode, root->entries[i].name);
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
     FileEntry files[] = {
         {1001, "file1.txt", 1024},
         {1003, "file3.txt", 2048},
         {1002, "file2.txt", 512},
         {1005, "file5.txt", 4096},
         {1004, "file4.txt", 8192},
         {1006, "file6.txt", 10240}
     };
      int n = sizeof(files) / sizeof(files[0]);
     for (int i = 0; i < n; i++) {
          root = insertBTree(root, files[i]);
       printf("插入文件 %s 后的B 树:\n", files[i].name);
          printBTree(root, 0);
           printf("\n");
    }
      int searchInode = 1004;
      int index;
    BTreeNode* result = searchBTree(root, searchInode, &index);
       if (result != NULL) {
       printf("找到文件: inode=%d, 名称=%s, 大小=%d\n",
                   result->entries[index].inode,
                   result->entries[index].name,
                    result->entries[index].size);
    } else {
        printf("未找到inode 为 %d 的文件\n", searchInode);
    }
     return 0;
}