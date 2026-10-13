#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct BSTNode {
      int data;
     struct BSTNode *left;
     struct BSTNode *right;
} BSTNode;
// 创建BST 节点
BSTNode* createBSTNode(int value) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
     return newNode;
}
// BST 插入
BSTNode* insertBST(BSTNode* node, int value) {
       if (node == NULL) {
          return createBSTNode(value);
    }
       if (value < node->data) {
          node->left = insertBST(node->left, value);
    } else if (value > node->data) {
         node->right = insertBST(node->right, value);
    }
     return node;
}
// BST 查找
BSTNode* searchBST(BSTNode* root, int key) {
       if (root == NULL || root->data == key) {
          return root;
    }
       if (key < root->data) {
          return searchBST(root->left, key);
    } else {
          return searchBST(root->right, key);
    }
}
/* 手册注明 AVL 定义"同上(略)"，此处补全题目1中的 AVL 树定义与运算 */
typedef struct AVLNode {
      int data;
     struct AVLNode *left;
     struct AVLNode *right;
      int height;
} AVLNode;
// 获取节点高度
int getHeight(AVLNode *node) {
       if (node == NULL) {
          return 0;
    }
     return node->height;
}
// 获取平衡因子
int getBalanceFactor(AVLNode *node) {
       if (node == NULL) {
          return 0;
    }
     return getHeight(node->left) - getHeight(node->right);
}
// 右旋
AVLNode* rightRotate(AVLNode *y) {
   AVLNode *x = y->left;
   AVLNode *T2 = x->right;
     x->right = y;
     y->left = T2;
     y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
     x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
     return x;
}
// 左旋
AVLNode* leftRotate(AVLNode *x) {
   AVLNode *y = x->right;
   AVLNode *T2 = y->left;
     y->left = x;
     x->right = T2;
     x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
     y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
     return y;
}
// 创建新节点
AVLNode* createAVLNode(int value) {
   AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
     return newNode;
}
// 插入节点
AVLNode* insertAVL(AVLNode* node, int value) {
       if (node == NULL) {
          return createAVLNode(value);
    }
       if (value < node->data) {
          node->left = insertAVL(node->left, value);
    } else if (value > node->data) {
         node->right = insertAVL(node->right, value);
    } else {
          return node; // 不允许重复值
    }
    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) :
getHeight(node->right));
      int balance = getBalanceFactor(node);
       // 左左情况
       if (balance > 1 && value < node->left->data) {
          return rightRotate(node);
    }
       // 右右情况
       if (balance < -1 && value > node->right->data) {
          return leftRotate(node);
    }
       // 左右情况
       if (balance > 1 && value > node->left->data) {
          node->left = leftRotate(node->left);
          return rightRotate(node);
    }
       // 右左情况
       if (balance < -1 && value < node->right->data) {
         node->right = rightRotate(node->right);
          return leftRotate(node);
    }
     return node;
}
// 查找节点
AVLNode* searchAVL(AVLNode* root, int key) {
       if (root == NULL || root->data == key) {
          return root;
    }
       if (key < root->data) {
          return searchAVL(root->left, key);
    } else {
          return searchAVL(root->right, key);
    }
}
// 中序遍历
void inorderAVL(AVLNode* root) {
       if (root != NULL) {
         inorderAVL(root->left);
         printf("%d ", root->data);
         inorderAVL(root->right);
    }
}
// 生成随机数组
void generateRandomArray(int arr[], int n, int max) {
    srand(time(NULL));
     for (int i = 0; i < n; i++) {
            arr[i] = rand() % max;
    }
}
int main() {
     const int SIZE = 10000;
     int* data = (int*)malloc(SIZE * sizeof(int));
    generateRandomArray(data, SIZE, 100000);
       // 构建BST
    BSTNode* bstRoot = NULL;
     clock_t start = clock();
     for (int i = 0; i < SIZE; i++) {
         bstRoot = insertBST(bstRoot, data[i]);
    }
     clock_t end = clock();
     printf("BST 构建时间: %f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);
       // 构建AVL 树
   AVLNode* avlRoot = NULL;
      start = clock();
     for (int i = 0; i < SIZE; i++) {
         avlRoot = insertAVL(avlRoot, data[i]);
    }
    end = clock();
    printf("AVL 树构建时间: %f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);
       // 测试查找性能
      int searchKeys[] = {data[0], data[SIZE/2], data[SIZE-1], 99999};
     printf("\nBST 查找时间:\n");
     for (int i = 0; i < 4; i++) {
            start = clock();
       BSTNode* result = searchBST(bstRoot, searchKeys[i]);
        end = clock();
             if (result != NULL) {
            printf("元素 %d 找到，时间: %f 秒\n", searchKeys[i], (double)(end - start) / CLOCKS_PER_SEC);
        } else {
            printf("元素 %d 未找到，时间: %f 秒\n", searchKeys[i], (double)(end - start) /
CLOCKS_PER_SEC);
        }
    }
    printf("\nAVL 树查找时间:\n");
     for (int i = 0; i < 4; i++) {
            start = clock();
       AVLNode* result = searchAVL(avlRoot, searchKeys[i]);
        end = clock();
             if (result != NULL) {
            printf("元素 %d 找到，时间: %f 秒\n", searchKeys[i], (double)(end - start) / CLOCKS_PER_SEC);
        } else {
            printf("元素 %d 未找到，时间: %f 秒\n", searchKeys[i], (double)(end - start) /
CLOCKS_PER_SEC);
        }
    }
     free(data);
     return 0;
}