/* 实验十二 第4题：完全二叉树顺序存储结构上的非递归前序遍历（自行实现） */
#include <stdio.h>
#define MAXSIZE 100
/* 根据顺序存储结构建立二叉链表 */
void CreateBitree_SqList(int *a,int total)
{ /* 顺序存储时下标i结点的左孩子为2i+1,右孩子为2i+2(0起) */
  ;
}
/* 用一维数组模拟栈，对完全二叉树作非递归前序遍历 */
void BinTraverse(int *a,int total)
{ int stack[MAXSIZE],top=0,root=0;
  if(total<=0) return;
  stack[top++]=root;
  while(top>0)
  { root=stack[--top];
    printf("%d ",a[root]);
    if(2*root+2<total) stack[top++]=2*root+2;  /* 右孩子先入栈 */
    if(2*root+1<total) stack[top++]=2*root+1;  /* 左孩子后入栈 */
  }
  printf("\n");
}
int main()
{ int a[MAXSIZE],n=0,x;
  printf("请按完全二叉树顺序存储方式输入结点(以0结束):\n");
  scanf("%d",&x);
  while(x&&n<MAXSIZE){ a[n++]=x; scanf("%d",&x); }
  printf("非递归前序遍历序列为:");
  BinTraverse(a,n);
  return 0;
}