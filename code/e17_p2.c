#include <stdio.h>
#include <stdlib.h>
/* 2、链地址法 */
#define m 13
#define n 20
#define NULL 0
typedef struct  nodetype
    {int key;
     struct nodetype *next;
    } CHashTable;
void HashListInit(CHashTable  **HT)    /* 初始化哈希表 */
{int i;
 for(i=0;i<n;i++) HT[i]=NULL;
}
void HashListClear (CHashTable  **HT)    /* 清空哈希表 */
{CHashTable  *p;
 int i;
 for(i=0;i<n;i++)
 {p=HT[i];
  while(p!=NULL)
  {HT[i]=p->next;
   HashListDelete(**HT,p->key);
   p=HT[i];
  }
 }
}
int Hash(int k) /* 设计哈希函数 */
{return k%m;
}
/* 在哈希表中查找元素 */
int HashListSearch(CHashTable **HT,int k)
{int d;CHashTable *p;
 d=Hash(k);
 p=HT[d];
 while(p!=NULL)
   {if(p->key==k) return(1);
     else p=p->next;
   }
 return 0;
}
/* 在哈希表中插入一个元素 */
void HashListInsert(CHashTable  **HT,int k)
{int d;CHashTable *p;
 d=Hash(k);
 p=(CHashTable *)malloc(sizeof(CHashTable));
 p->key=k;
 p->next=HT[d];
 HT[d]=p;
}
HashListDelete(CHashTable  **HT,int k)
{int d;
 CHashTable *p,*q;
 d=Hash(k);
 p=HT[d];
 if(p==NULL)
   {printf("哈希表中无%d",k);
     exit(1);
   }
 if(p->key==k)
   {HT[d]=p->next;
     free(p);
     return;
   }
 else {q=p->next;
       while(q!=NULL)
     {if(q->key==k)
         {p->next=q->next;
            free(q);
        return ;
        }
       else {p=q;q=q->next;}
     }
       }
  printf("哈希表中无%d",k);
   exit(1);
 }
/* 输出哈希表中所有元素 */
void PrintHashList(CHashTable  **HT)
{int i;CHashTable *p;
 for(i=0;i<n;i++)
 {p=HT[i];
   printf("\n ");
  printf("%d--> ",i);
  while(p)
  {printf("%d--> ",p->key);
   p=p->next;
  }
  printf("NULL");
 }
}
main()
{int k;
 CHashTable **HT;
  HT=(CHashTable**)malloc(n*sizeof(CHashTable*));
 HashListInit(HT);
 printf("请输入要插入到哈希表中的关键字,以0 结束:\n");
 scanf("%d",&k);
 while(k!=0)
     {HashListInsert(HT,k);
      scanf("%d",&k);
     }
  printf("所建立的哈希表长为20,哈希函数为H(key)=key%13\n");
  printf("所建立的哈希表为:\n");
 PrintHashList(HT);
 printf("\n");
 printf("请输入要删除的关键字:\n");
 scanf("%d",&k);
 HashListDelete(HT,k);
 printf("删除成功后的哈希表为:\n");
 PrintHashList(HT);
}