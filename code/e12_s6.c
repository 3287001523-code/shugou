/* 实验十二 第6题：二叉链表存储的二叉树按层次遍历（自行实现） */
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef char DataType;
typedef struct BitNode
{ DataType data;
  struct BitNode *lchild,*rchild;
}BitNode,*BitTree;
void BinTreeCreat(BitTree *BT)          /* 按前序次序建立二叉树 */
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
void layorder(BitTree T)     /* 按层次遍历二叉树:借助队列 */
{ BitTree queue[MAXSIZE],p;
  int front=0,rear=0;
  if(T==NULL) return;
  queue[rear++]=T;
  while(front<rear)
  { p=queue[front++];
    printf("%c ",p->data);
    if(p->lchild) queue[rear++]=p->lchild;
    if(p->rchild) queue[rear++]=p->rchild;
  }
  printf("\n");
}
int main()
{ BitTree T;
  printf("请按前序次序输入二叉树(空结点用#表示):\n");
  BinTreeCreat(&T);
  printf("层次遍历序列为:");
  layorder(T);
  return 0;
}