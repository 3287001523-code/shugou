/* 实验十二 第3题：前序/中序/后序遍历的非递归算法（自行实现） */
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef char DataType;
typedef struct BitNode
{ DataType data;
  struct BitNode *lchild,*rchild;
}BitNode,*BitTree;
void BinTreeInit(BitTree *BT){ *BT=NULL; }
void BinTreeCreat(BitTree *BT)      /* 按前序次序建立二叉树 */
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
typedef struct
{ BitTree data[MAXSIZE]; int top;
}Stack;
void Push(Stack *S,BitTree p){ S->data[S->top++]=p; }
BitTree Pop(Stack *S){ return S->data[--S->top]; }
int Empty(Stack *S){ return S->top==0; }
void preorder_stack(BitTree T)     /* 前序遍历非递归 */
{ Stack S; S.top=0; BitTree p=T;
  if(T==NULL) return;
  Push(&S,T);
  while(!Empty(&S))
  { p=Pop(&S);
    printf("%c ",p->data);
    if(p->rchild) Push(&S,p->rchild);
    if(p->lchild) Push(&S,p->lchild);
  }
}
void inorder_stack(BitTree T)      /* 中序遍历非递归 */
{ Stack S; S.top=0; BitTree p=T;
  while(p||!Empty(&S))
  { if(p){ Push(&S,p); p=p->lchild; }
    else { p=Pop(&S); printf("%c ",p->data); p=p->rchild; }
  }
}
void postorder_stack(BitTree T)    /* 后序遍历非递归(带标志栈) */
{ Stack S; S.top=0;
  BitTree p=T,pre=NULL;
  Push(&S,p);
  while(!Empty(&S))
  { p=S.data[S.top-1];
    if((p->lchild==NULL&&p->rchild==NULL)
       ||(pre!=NULL&&(pre==p->lchild||pre==p->rchild)))
    { printf("%c ",p->data); Pop(&S); pre=p; }
    else
    { if(p->rchild) Push(&S,p->rchild);
      if(p->lchild) Push(&S,p->lchild);
    }
  }
}
int main()
{ BitTree T;
  BinTreeInit(&T);
  printf("请按前序次序输入二叉树(空结点用#表示):\n");
  BinTreeCreat(&T);
  printf("非递归前序遍历:"); preorder_stack(T); printf("\n");
  printf("非递归中序遍历:"); inorder_stack(T); printf("\n");
  printf("非递归后序遍历:"); postorder_stack(T); printf("\n");
  return 0;
}