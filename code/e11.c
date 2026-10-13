/* 实验十一：二叉树结点的类型定义和基本操作（自行实现，函数框架按手册要求） */
#include <stdio.h>
#include <stdlib.h>
typedef char DataType;
typedef struct BitNode
{ DataType data;
  struct BitNode *lchild,*rchild;
}BitNode,*BitTree;
void BinTreeInit(BitTree *BT)          /* 初始化二叉树，树根指针置空 */
{ *BT=NULL;
}
/* 按先序次序建立二叉树，空结点以#表示 */
void BinTreeCreat(BitTree *BT)
{ char ch;
  scanf("%c",&ch);
  if(ch=='#') *BT=NULL;
  else
  { *BT=(BitTree)malloc(sizeof(BitNode));
    (*BT)->data=ch;
    BinTreeCreat(&(*BT)->lchild);
    BinTreeCreat(&(*BT)->rchild);
  }
}
int BinTreeEmpty(BitTree *BT)          /* 检查二叉树是否为空 */
{ return *BT==NULL;
}
/* 按指定次序输出所有结点:1先序 2中序 3后序 */
void BinTraverse(BitTree BT,int order)
{ if(BT==NULL) return;
  if(order==1) printf("%c ",BT->data);
  BinTraverse(BT->lchild,order);
  if(order==2) printf("%c ",BT->data);
  BinTraverse(BT->rchild,order);
  if(order==3) printf("%c ",BT->data);
}
int BinTreeDepth(BitTree BT)          /* 求二叉树的深度 */
{ int l,r;
  if(BT==NULL) return 0;
  l=BinTreeDepth(BT->lchild);
  r=BinTreeDepth(BT->rchild);
  return (l>r?l:r)+1;
}
int BinTreeCount(BitTree BT)          /* 求所有结点数 */
{ if(BT==NULL) return 0;
  return BinTreeCount(BT->lchild)+BinTreeCount(BT->rchild)+1;
}
void BinTreeClear(BitTree *BT)          /* 清除二叉树 */
{ if(*BT)
  { BinTreeClear(&(*BT)->lchild);
    BinTreeClear(&(*BT)->rchild);
    free(*BT);
    *BT=NULL;
  }
}
int main()
{ BitTree T;
  BinTreeInit(&T);
  printf("请按先序次序输入二叉树结点(空结点用#表示):\n");
  BinTreeCreat(&T);
  if(BinTreeEmpty(&T)) { printf("二叉树为空!\n"); return 0; }
  printf("先序遍历序列为:"); BinTraverse(T,1); printf("\n");
  printf("中序遍历序列为:"); BinTraverse(T,2); printf("\n");
  printf("后序遍历序列为:"); BinTraverse(T,3); printf("\n");
  printf("二叉树的深度为:%d\n",BinTreeDepth(T));
  printf("二叉树的结点数为:%d\n",BinTreeCount(T));
  BinTreeClear(&T);
  if(BinTreeEmpty(&T)) printf("清除后二叉树为空。\n");
  return 0;
}