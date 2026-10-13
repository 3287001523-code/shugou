#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
   #define TRUE 1
   #define FALSE 0
   #define NULL 0
   #define flag -1
   typedef struct Lnode                  /* 单链表的结点类型 */
   {ElemType data;
     struct LNode *next;
   } LNode,*LinkedList;
   LinkedList LinkedListInit()        /* 初始化单链表 */
   {LinkedList L;
     L=(LinkedList)malloc(sizeof(LNode));
    L->next=NULL;
 return L;
}
void LinkedListClear(LinkedList L)      /* 清空单链表 */
{L->next=NULL;
 printf("链表已经清空\n");
}
int LinkedListEmpty(LinkedList L)         /* 检查单链表是否为空 */
{if(L->next==NULL) return TRUE;
 else return FALSE;
}
void LinkedListTraverse(LinkedList L)     /* 遍历单链表 */
{LinkedList p;
 p=L->next;
 if(p==NULL) printf("单链表为空表\n");
 else
 {printf("链表中的元素为:\n");
   while(p!=NULL)
     {printf("%d ",p->data);    p=p->next;}
     }
      printf("\n");
}
int  LinkedListLength (LinkedList L)
{LinkedList p;
 int j;
 p=L->next;
 j=0;
 while(p!=NULL)
  { j++;p=p->next; }
 return    j;
 }
LinkedList  LinkedListGet(LinkedList L,int i)
{LinkedList p;int j;
 p=L->next; j=1;
 while (p!=NULL && j<i )
   {p=p->next;  j++;  }
  if (j==i) return p;
 else   return NULL;
}
int  LinkedListLocate ( LinkedList  L, ElemType  x)
{LinkedList p;int j;
 p=L->next; j=1;
 while ( p!=NULL && p->data != x)
   {p=p->next;j++;}
 if(p) return j;
 else return 0;
  }
void  LinkedListInsert(LinkedList L, int i, ElemType  x)
{LinkedList p,s;
 int j;
 j=1;p=L;
 while(p&&j<i)
   {p=p->next;j++;}
 if(p==NULL||j>i)
  printf("插入位置不正确\n");
 else {s=(LNode *)malloc(sizeof(LNode));
         s->data=x;
        s->next=p->next;
        p->next=s;
         printf("%d 已插入到链表中\n",x);
        }
}
void LinkedListDel(LinkedList L,int i)
{ LinkedList p,q;
 int j;
  j=1;p=L;
  while(p->next&&j<i)
  {p=p->next;j++;}
  if(p->next==NULL)
 printf("删除位置不正确\n");
   else {q=p->next;p->next=q->next;free(q);
         printf("第%d 个元素已从链表中删除\n",i);
         }
}
LinkedList  LinkedListCreat( )
{ LinkedList L=LinkedListInit(),p,r;
  ElemType x;
  r=L;
 printf("请依次输入链表中的元素,输入-1 结束\n");
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
int scan()
{int d;
 printf("请选择要进行的操作\n");
 printf("1.初始化 2.清空3.求链表长度4.检查链表是否为空\n");
 printf("5.遍历链表 6.从链表中查找元素\n");
 printf("7.从链表中查找与给定元素值相同的元素在顺序表中的位置\n");
 printf("8.向链表中插入元素9. 从链表中删除元素\n");
 printf("其他键退出。。。。。\n");
 scanf("%d",&d);
 return(d);
}
main()
{int quit=0;
int i,locate;
ElemType e;
 LinkedList L,p;
 while(!quit)
 switch(scan())
 {case 1:L=LinkedListInit();printf("\n");break;
 case 2:LinkedListClear(L);printf("\n");break;
 case 3:printf("链表的长度为 %d\n",LinkedListLength(L));break;
 case 4:if(LinkedListEmpty(L))printf("链表为空\n");else printf("链表非空\n");break;
 case 5:LinkedListTraverse(L);
  break;
 case 6:printf("请输入待查询元素在链表中的位置:");
  scanf("%d",&i);
  p=LinkedListGet(L,i);
  if(p) printf("链表中第%d 个元素的值为:%d\n",i,p->data);
  else printf("查询位置不正确\n");
  break;
 case 7:printf("请输入待查询元素的值:");
  scanf("%d",&e);
     locate=LinkedListLocate(L,e);
      if(locate)
        printf("%d 在链表中的位置是:%d\n",e,locate);
      else printf("链表中没有值为%d 的元素\n",e);
      break;
     case 8:printf("请输入插入元素的位置和值(中间以空格或回车分隔):\n");
     scanf("%d%d",&i,&e);
      LinkedListInsert(L,i,e);
      break;
     case 9:if(LinkedListLength(L)==0)
           printf("链表已经为空,不能删除\n");
       else {printf("请输入待删除元素的位置:\n");
     scanf("%d",&i);
      LinkedListDel(L,i);}
      break;
     case 10:L=LinkedListCreat();
       printf("\n");break;
     default:quit=1;}
   }