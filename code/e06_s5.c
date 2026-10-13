/* 实验六 第5题：输入正整数序列存入链表，反复找出最小结点并删除，直至表空（自行实现） */
#include <stdio.h>
#include <stdlib.h>
typedef int DataType;
typedef struct node
{ DataType data;
  struct node *next;
}ListNode, *LinkList;
LinkList head;
/* 输入一串正整数建立链表 */
void CreatList(void)
{ ListNode *p,*r=NULL; DataType x;
  head=NULL;
  printf("请输入一串正整数(以0结束):\n");
  scanf("%d",&x);
  while(x>0)
  { p=(ListNode*)malloc(sizeof(ListNode));
    p->data=x; p->next=NULL;
    if(head==NULL) head=p; else r->next=p;
    r=p;
    scanf("%d",&x);
  }
}
/* 找出最小结点并删除，返回其值 */
DataType DelMin(void)
{ ListNode *p=head,*pre=NULL,*minp=head,*minpre=NULL;
  DataType k;
  while(p)
  { if(p->data<minp->data){ minp=p; minpre=pre; }
    pre=p; p=p->next;
  }
  k=minp->data;
  if(minpre==NULL) head=minp->next;
  else minpre->next=minp->next;
  free(minp);
  return k;
}
int main()
{ int n=0;
  CreatList();
  printf("依次删除的最小结点为:\n");
  while(head){ printf("%d ",DelMin()); n++; }
  printf("\n共删除了%d个结点，链表已空。\n",n);
  return 0;
}