#include <stdio.h>
#include <stdlib.h>
#define NIL 0          /* 用NIL 作为空闲单元的标志 */
   #define DelNIL -1          /* 用DelNIL 作为已删除单元的标志 */
#define m 13
#define n 20
typedef struct
    {int key;
    }LHashTable;
/* 初始化哈希表 */
void HashListInit(LHashTable  HT[n])
{int i;
 for(i=0;i<n;i++) HT[i].key=NIL;
 }
/* 清空哈希表 */
void HashListClear (LHashTable  HT[])
{int i;
 for(i=0;i<n;i++) HT[i].key=NIL;
 }
/* 定义哈希函数 */
int Hash (int k)
{return (k%m);
 }
/* 在哈希表中查找元素 */
int HashListSearch(LHashTable HT[n],int k)
{int d,temp;
 d=Hash(k);                             /* 计算k 的哈希地址 */
 temp=d;                            /* temp 暂存k 的哈希地址 */
 while(HT[d].key!=NIL)
   {if(HT[d].key==k) return d;   /* 在哈希表中查找到元素k */
     else d=(d+1)%n;                /* 没找到进行线性探测法继续查找 */
  if(d==temp) return -1;        /* 哈希中没有待查元素k */
  }
   return -1;
}
/* 在哈希表中插入一个元素 */
void HashListInsert(LHashTable  HT[n],int k)
{int d,temp;
 d=Hash(k);                               /* 计算k 的哈希地址 */
 temp=d;                                   /* temp 暂存k 的哈希地址 */
 while(HT[d].key!=NIL&&HT[d].key!=DelNIL)    /* 当前位置已有元素 */
   {d=(d+1)%n;                            /* 进行线性探测 */
    if(d==temp) {printf("哈希表无空间");    /* 哈希表已满 */
         exit(1);
       }
   }
  HT[d].key=k;                          /* 插入k */
}
/* 从哈希表中删除元素 */
void HashListDelete(LHashTable  HT[n],int k)
{int d,temp;
 d=Hash(k);
 temp=d;
 while(HT[d].key!=NIL)
 {if(HT[d].key==k)
   {HT[d].key=DelNIL;         /* 找到k，写上删除标志 */
     return ;
   }
     else d=(d+1)%n;            /* 当前位置没找到k，进行线性探测 */
  if(d==temp) break;
 }
 printf("哈希表中无待删除元素%d",k);
 exit(1);
}
/* 输出哈希表中所有元素 */
void PrintHashList(LHashTable  HT[n])
{int i;
 for(i=0;i<n;i++) printf(" %d ",i);
 printf("\n");
 for(i=0;i<n;i++) printf(" %d ",HT[i].key);
}
main()
{int k;
 LHashTable HT[n];
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