/* 实验十二 第5题：递归算法交换二叉树中所有结点的左右子树（自行实现） */
#include <stdio.h>
#include <stdlib.h>
typedef char DataType;
typedef struct BitNode
{ DataType data;
  struct BitNode *lchild,*rchild;
}BitNode,*Bitree;
void createbitree(Bitree *t)     /* 按前序次序建立二叉树 */
{ char ch;
  scanf("%c",&ch);
  if(ch=='#') *t=NULL;
  else
  { *t=(Bitree)malloc(sizeof(BitNode));
    (*t)->data=ch;
    createbitree(&(*t)->lchild);
    createbitree(&(*t)->rchild);
  }
}
void preorder(Bitree t)          /* 前序遍历二叉树 */
{ if(t==NULL) return;
  printf("%c ",t->data);
  preorder(t->lchild);
  preorder(t->rchild);
}
void change(Bitree *t)           /* 交换二叉树的左右子树 */
{ Bitree temp;
  if(*t==NULL) return;
  temp=(*t)->lchild;
  (*t)->lchild=(*t)->rchild;
  (*t)->rchild=temp;
  change(&(*t)->lchild);
  change(&(*t)->rchild);
}
int main()
{ Bitree T;
  printf("请按前序次序输入二叉树(空结点用#表示):\n");
  createbitree(&T);
  printf("交换前前序序列为:"); preorder(T); printf("\n");
  change(&T);
  printf("交换后前序序列为:"); preorder(T); printf("\n");
  return 0;
}