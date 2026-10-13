#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
      int data;
     struct TreeNode *left;
     struct TreeNode *right;
} TreeNode;
// 创建新节点
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
     return newNode;
}
// 插入节点
TreeNode* insert(TreeNode* root, int value) {
       if (root == NULL) {
          return createNode(value);
    }
       if (value < root->data) {
          root->left = insert(root->left, value);
    } else if (value > root->data) {
          root->right = insert(root->right, value);
    }
     return root;
}
// 查找节点
TreeNode* search(TreeNode* root, int key) {
       if (root == NULL || root->data == key) {
          return root;
    }
       if (key < root->data) {
          return search(root->left, key);
    } else {
          return search(root->right, key);
    }
}
// 中序遍历
void inorderTraversal(TreeNode* root) {
       if (root != NULL) {
          inorderTraversal(root->left);
         printf("%d ", root->data);
          inorderTraversal(root->right);
    }
}
// 查找最小值节点
TreeNode* findMin(TreeNode* root) {
     while (root && root->left != NULL) {
          root = root->left;
    }
     return root;
}
// 删除节点
TreeNode* deleteNode(TreeNode* root, int key) {
       if (root == NULL) {
          return root;
    }
       if (key < root->data) {
          root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
          root->right = deleteNode(root->right, key);
    } else {
              // 节点有一个或没有子节点
             if (root->left == NULL) {
            TreeNode* temp = root->right;
                free(root);
               return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
                free(root);
               return temp;
        }
              // 节点有两个子节点，找到右子树的最小节点
        TreeNode* temp = findMin(root->right);
          root->data = temp->data;
          root->right = deleteNode(root->right, temp->data);
    }
     return root;
}
int main() {
    TreeNode* root = NULL;
      int values[] = {50, 30, 20, 40, 70, 60, 80};
      int n = sizeof(values) / sizeof(values[0]);
       // 构建二叉排序树
     for (int i = 0; i < n; i++) {
          root = insert(root, values[i]);
    }
   printf("中序遍历结果: ");
     inorderTraversal(root);
     printf("\n");
      int key;
   printf("请输入要查找的元素: ");
     scanf("%d", &key);
    TreeNode* result = search(root, key);
       if (result != NULL) {
        printf("元素 %d 找到\n", key);
    } else {
        printf("元素 %d 未找到\n", key);
    }
   printf("请输入要删除的元素: ");
     scanf("%d", &key);
     root = deleteNode(root, key);
   printf("删除后的中序遍历结果: ");
     inorderTraversal(root);
     printf("\n");
     return 0;
}