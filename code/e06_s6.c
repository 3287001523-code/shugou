/* 实验六 第6题：利用单循环链表实现约瑟夫环问题（自行实现） */
#include <stdio.h>
#include <stdlib.h>
typedef struct node
{ int data;
  struct node *next;
}ListNode;
int main()
{ ListNode *head,*p,*r,*q; int n,m,i;
  printf("请输入人数n和报数上限m(如 10 3):\n");
  scanf("%d %d",&n,&m);
  head=(ListNode*)malloc(sizeof(ListNode));
  head->data=1; head->next=NULL; r=head;
  for(i=2;i<=n;i++)
  { p=(ListNode*)malloc(sizeof(ListNode));
    p->data=i; p->next=NULL; r->next=p; r=p;
  }
  r->next=head;              /* 构成单循环链表 */
  printf("出圈顺序为:\n");
  p=r;                        /* p始终指向当前报数结点的前驱 */
  while(p->next!=p)
  { for(i=1;i<m;i++) p=p->next;
    q=p->next;                 /* 报到m的结点出圈 */
    printf("%d ",q->data);
    p->next=q->next;
    free(q);
  }
  printf("%d\n",p->data);      /* 最后剩下的人 */
  return 0;
}