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
 printf("请输入链表中的结点,以-1 结束\n");
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
LinkedList ListConcat(LinkedList La,LinkedList Lb)/*把链表Lb 接在La 后面*/
{ LinkedList Lc,p;
  Lc=La;p=La;
  while(p->next) p=p->next;
  p->next=Lb->next;
   return Lc;
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
{LinkedList La,Lb;
 La=LinkedListCreat( );
 Lb= LinkedListCreat( );
 La=ListConcat(La,Lb);
 print(La);
}