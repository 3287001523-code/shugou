#define NULL 0
typedef struct LNode
{int data;
 struct LNode *next;
} LNode,*LinkedList;
LinkedList  LinkedListCreat()
{ LinkedList L,p,r;
   int x,flag=-1;
  L=(LinkedList)malloc(sizeof(LNode));
  L->next=NULL;
  r=L;
 printf("请输入非递减有序表,以-1 结束\n");
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
     LinkedList un(LinkedList La,LinkedList Lb)       /*合并链表*/
     {LinkedList p,q,r;
     p=La->next;
     q=Lb->next;
      r=La;
     while((p!=NULL)&&(q!=NULL))
        if(p->data<=q->data) {r->next=p; r=p;p=p->next;}
         else {r->next=q; r=q;q=q->next;}
     if(p!=NULL) r->next=p;
     if(q!=NULL) r->next=q;
      return La;
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
     {LinkedList La,Lb,Lc;
      La=LinkedListCreat( );
    Lb= LinkedListCreat( );
     Lc=un(La,Lb);
      print(Lc);
    }