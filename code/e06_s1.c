#include "stdio.h"
     #define NULL 0
     typedef struct LNode
     {int data;
       struct LNode *next;
    } LNode,*LinkedList;
     LinkedList  LinkedListCreat( )
    { LinkedList L,p,r;
         int x,flag=-1;
       L=(LinkedList)malloc(sizeof(LNode));
      L->next=NULL;
       r=L;
    printf("请输入递增的有序序列,输入-1 结束\n");
       scanf("%d",&x);
       while (x!=flag)
     {p=(LinkedList)malloc(sizeof(LNode));
           p->data=x;
           r->next=p;
           r=p;
     scanf("%d",&x);
          }
       r->next=NULL;
         return L;
    }
    void InsertList(LinkedList L,int x)
     {LinkedList p,q,s;
     q=L;p=q->next;
     while(p!=NULL&&p->data<x)
           {q=p; p=p->next;}
       s=(LinkedList)malloc(sizeof(LNode));
       s->data=x;
      s->next=q->next; q->next=s;
    }
    void print(LinkedList L)             /*输出链表中的结点*/
{LinkedList p;
 p=L->next;
 while(p!=NULL)
 {printf("%d ",p->data);
  p=p->next;
 }
}
main( )
{LinkedList L;
 int x;
 L=LinkedListCreat( );
 printf("请输入要插入的元素:");
 scanf("%d",&x);
 InsertList(L,x);
 print(L);
}