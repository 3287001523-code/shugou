#define NULL 0
     typedef struct  DLNode
     {int data,freq;
       struct DLNode *prior,*next;
    }DLNode,*DLinkedList;
    DLinkedList creat()
     {int num;
     DLinkedList head,p1,p2;
      head=(DLinkedList)malloc(sizeof(DLNode));
    head->next=NULL;            /*表头为空 */
     p2=head;
    printf("输入元素,以-1 结束:");
    scanf("%d",&num);
    while(num!=-1)
        {p1=(DLinkedList)malloc(sizeof(DLNode));
        p1->data=num; p1->freq=0;
         p2->next=p1; p1->prior=p2;
        p2=p1;
        scanf("%d",&num);
       }
     p2->next=NULL;
     return head;
    }
    void search(DLinkedList head, int key)
    {DLinkedList p1,p2,temp;
     p2=head; p1=p2->next;
      while(p1)
         {if(p1->data==key)
            { p1->freq++; break;}
            else
             {p2=p1; p1=p2->next;}
         }
     if(p1==NULL)  printf("没有发现.\n");
      else {if(p1->next==NULL)
             {p2->next=p1->next; temp=p1;}
             else
             {p2->next=p1->next;
     p1->next->prior=p2;
    temp=p1;
    }
     for(p2=head,p1=p2->next;
     p1 && p1->freq > temp->freq;p2=p1,p1=p2->next); /*插入*/
       if(p1==NULL)
            {p2->next=temp; temp->prior=p2; temp->next=NULL; }
         else
            {p2->next=temp; temp->prior=p2;
    temp->next=p1; p1->prior=temp;
    }
    }
    }
    void print(DLinkedList head)
    {DLinkedList p;
      p=head->next;
     do{printf("元素=%d " , p->data);
        printf("频度=%d\n", p->freq);
          p=p->next;
          }while(p);
    }
      int main()
    {DLinkedList head;
       int key;
      head=creat();
   printf("现在元素和其访问的频度(按递减的顺序输出)为:\n" );
      print(head);
    printf("请输入要访问的元素,以-1 结束:");
      scanf("%d",&key);
      while(key!=-1)
        {search(head,key);
          print(head);
        printf( "请输入要访问的元素,以-1 结束:");
         scanf("%d",&key);
     }
    }