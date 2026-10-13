/* 实验十二 第2题：输出后序序列的逆序（自行实现）
   按后序 an-1,...,a1 的逆序输出，等价于"根-右-左"次序遍历 */
#include <stdio.h>
#include <stdlib.h>
typedef char DataType;
typedef struct BitNode
{ DataType data;
  struct BitNode *lchild,*rchild;
}BitNode,*BitTree;
void BinTreeInit(BitTree *BT)   /* 初始化二叉树 */
{ *BT=NULL; }
void BinTreeCreat(BitTree *BT)  /* 按先序次序建立二叉树，#表示空 */
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
void BinTraverse(BitTree BT)     /* 与后序遍历相反的遍历序列 */
{ if(BT==NULL) return;
  printf("%c ",BT->data);        /* 先访问根 */
  BinTraverse(BT->rchild);        /* 再遍历右子树 */
  BinTraverse(BT->lchild);        /* 最后遍历左子树 */
}
void BinTraversepost(BitTree BT)  /* 后序遍历二叉树 */
{ if(BT==NULL) return;
  BinTraversepost(BT->lchild);
  BinTraversepost(BT->rchild);
  printf("%c ",BT->data);
}
int main()
{ BitTree T;
  BinTreeInit(&T);
  printf("请按先序次序输入二叉树(空结点用#表示):\n");
  BinTreeCreat(&T);
  printf("后序遍历序列为:"); BinTraversepost(T); printf("\n");
  printf("后序序列的逆序为:"); BinTraverse(T); printf("\n");
  return 0;
}