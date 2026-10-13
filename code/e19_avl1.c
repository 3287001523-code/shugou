#include <stdio.h>
#include <stdlib.h>
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
int main() {
   AVLNode* root = NULL;
      int values[] = {10, 20, 30, 40, 50, 25};
      int n = sizeof(values) / sizeof(values[0]);
     for (int i = 0; i < n; i++) {
          root = insertAVL(root, values[i]);
    }
    printf("AVL 树中序遍历结果: ");
     inorderAVL(root);
     printf("\n");
      int key;
   printf("请输入要查找的元素: ");
     scanf("%d", &key);
   AVLNode* result = searchAVL(root, key);
       if (result != NULL) {
        printf("元素 %d 找到\n", key);
    } else {
        printf("元素 %d 未找到\n", key);
    }
     return 0;
}