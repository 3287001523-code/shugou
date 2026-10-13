/* 实验六 第7题：在双向链表上实现线性表运算（建立/插入/删除/遍历）（自行实现） */
#include <stdio.h>
#include <stdlib.h>
typedef int DataType;
typedef struct DNode
{ DataType data;
  struct DNode *prior,*next;
}DLinkNode,*DLinkList;
/* 初始化：建立仅含头结点的双向链表 */
DLinkList DListInit(void)
{ DLinkList L=(DLinkList)malloc(sizeof(DLinkNode));
  L->prior=L->next=NULL;
  return L;
}
/* 按输入次序用尾插法建立双向链表 */
void DListCreat(DLinkList L)
{ DLinkNode *r=L,*p; DataType x;
  printf("请输入双向链表元素(以0结束):\n");
  scanf("%d",&x);
  while(x)
  { p=(DLinkNode*)malloc(sizeof(DLinkNode));
    p->data=x; p->next=NULL;
    p->prior=r; r->next=p; r=p;
    scanf("%d",&x);
  }
}
/* 在第i个结点之前插入元素x */
int DListInsert(DLinkList L,int i,DataType x)
{ DLinkNode *p=L,*s; int k=0;
  while(p->next&&k<i){ p=p->next; k++; }
  if(k<i) return 0;
  s=(DLinkNode*)malloc(sizeof(DLinkNode));
  s->data=x;
  s->prior=p->prior; p->prior->next=s;
  s->next=p; p->prior=s;
  return 1;
}
/* 删除第i个结点 */
int DListDelete(DLinkList L,int i)
{ DLinkNode *p=L; int k=0;
  while(p->next&&k<i){ p=p->next; k++; }
  if(k<i||p->next==NULL&&k==i&&p==NULL) return 0;
  if(p->next==NULL&&k<i) return 0;
  p->prior->next=p->next;
  if(p->next) p->next->prior=p->prior;
  free(p);
  return 1;
}
/* 从头到尾遍历 */
void DListPrint(DLinkList L)
{ DLinkNode *p=L->next;
  while(p){ printf("%d ",p->data); p=p->next; }
  printf("\n");
}
int main()
{ DLinkList L; int i,x;
  L=DListInit();
  DListCreat(L);
  printf("建立的双向链表为:"); DListPrint(L);
  printf("请输入插入位置和元素(如 2 99):\n");
  scanf("%d %d",&i,&x);
  if(DListInsert(L,i,x))
  { printf("插入后链表为:"); DListPrint(L); }
  else printf("插入位置不合法!\n");
  printf("请输入删除位置(如 3):\n");
  scanf("%d",&i);
  if(DListDelete(L,i))
  { printf("删除后链表为:"); DListPrint(L); }
  else printf("删除位置不合法!\n");
  return 0;
}