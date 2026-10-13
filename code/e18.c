#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
   #define LT(a,b) ((a)<(b))
   typedef int KeyType;
   typedef int InfoType;
   typedef struct
  { KeyType key;
    InfoType otherinfo;
  }RedType;
   typedef struct
  { RedType r[MAXSIZE+1];
     int length;
   }SqList;
  /* 2、简单插入排序 */
 void InsertSort(SqList *L)         /*简单插入排序*/
 { int i,j;
    for(i=2;i<=L->length;++i)
  if(LT(L->r[i].key,L->r[i-1].key))
 { L->r[0]=L->r[i];
          for(j=i-1; LT(L->r[0].key,L->r[j].key); --j)
  L->r[j+1]=L->r[j];
         L->r[j+1]=L->r[0];
      }
 }
 /* 3、折半插入排序 */
 void BInsertSort(SqList *L)        /*折半插入排序*/
 { int i,j;
     int low,high,m;
    for(i=2;i<=L->length;++i){
      L->r[0]=L->r[i];              /*将R[i]暂存到R[0]*/
      low=1;high=i-1;
      while(low<=high)     /*在R[low..high]中折半查找插入的位置*/
        {m=(low+high)/2;
            if (LT(L->r[0].key,L->r[m].key))
  high=m-1;                    /*插入点在低半区*/
         else low=m+1;               /*插入点在高半区*/
      }
       for(j=i-1;j>=high+1;--j)          /*记录后移*/
         L->r[j+1]=L->r[j];
      L->r[high+1]=L->r[0];             /*插入*/
  }
}
 /* 4、快速排序 */
int Partition(SqList *L,int low,int high)      /*快速排序*/
{   int pivotkey;
  L->r[0]=L->r[low];     /*用子表的第一个记录作枢轴记录*/
  pivotkey=L->r[low].key;       /*枢轴记录关键字*/
  while(low<high)          /*从表的两端交替地向中间扫描*/
{ while(low<high&&L->r[high].key>=pivotkey) --high;
       L->r[low]=L->r[high];    /*将比枢轴记录小的记录移到低端*/
    while(low<high&&L->r[low].key<=pivotkey) ++low;
     L->r[high]=L->r[low];     /*将比枢轴记录大的记录移到高端*/
  }
  L->r[low]=L->r[0];        /*枢轴记录到位*/
   return low;            /*返回枢轴位置*/
}
void QSort(SqList *L,int low,int high)
{ int pivotloc;
  if(low<high){
     pivotloc=Partition(L,low,high);   /*将L.r[low..high]一分为二*/
     QSort(L,low,pivotloc-1); /*对低子表递归排序pivotloc 是枢轴位置*/
     QSort(L,pivotloc+1,high);   /*对高子表递归排序*/
  }
}
void QuickSort(SqList *L)       /*对记录序列进行快速排序*/
{ QSort(L,1,L->length);
}
 /* 5、简单选择排序 */
int SelectMinKey(SqList L,int i)           /*简单选择排序*/
{ int k;
   int j;
  k=i;
  for(j=i;j<L.length+1;j++)
     if(L.r[k].key>L.r[j].key)
       k=j;
   return k;
}
void SelectSort(SqList *L)            /*简单选择排序*/
{ RedType t;
   int i,j;
  for(i=1;i<L->length;++i)     /*选择第i 小的记录，并交换到位*/
{ j=SelectMinKey(*L,i);        /*在R[i..n]中选择key 最小的记录*/
if(i!=j)
 { t=L->r[i]; L->r[i]=L->r[j]; L->r[j]=t; }   /*与第i 个记录交换*/
  }
}
 /* 6、堆排序 */
typedef SqList HeapType;                     /*堆排序*/
void HeapAdjust(HeapType *H,int s,int m)
{ RedType rc;
   int j;
  rc=H->r[s];
  for(j=2*s;j<=m;j*=2)          /*沿key 较大的孩子结点向下筛选*/
{ if(j<m&&LT(H->r[j].key,H->r[j+1].key)) ++j;       /*j 为key 较大的记录的下标*/
     if(!LT(rc.key,H->r[j].key)) break;     /*rc 应插入在位置s 上*/
     H->r[s]=H->r[j];
     s=j;
  }
  H->r[s]=rc;              /*插入*/
}
void HeapSort(HeapType *H)
{ RedType t;
   int i;
  for(i=H->length/2;i>0;--i)      /*把R[1..n]建成大顶堆*/
     HeapAdjust(H,i,H->length);
  for(i=H->length;i>1;--i)
/*将堆顶记录和当前未经排序子序列 R[1..i]中最后一个记录相互交换*/
{ t=H->r[1];
     H->r[1]=H->r[i];
     H->r[i]=t;
     HeapAdjust(H,1,i-1);         /*将R[1..i-1] 重新调整为大顶堆*/
  }
}
 /* 7、主程序 */
main()
{ int i,k,num;
  SqList s;
  printf("请输入待排序序列的个数:\n");
  scanf("%d",&num);
  printf("请输入序列中的元素:\n");
  for(i=1;i<=num;i++)
     scanf("%d",&s.r[i].key);
   s.length=i-1;
  printf("\n\t1,简单插入排序\n\t2,折半插入排序\n\t3,快速排序\n\t4,直接选择排序\n");
  printf("\t5,堆排序\n\t 按1..5 选择操作\n");
  scanf("%d",&k);
  switch(k)
{ case 1:  InsertSort(&s);break;
        case 2:  BInsertSort(&s); break;
        case 3:  QuickSort(&s); break;
        case 4:  SelectSort(&s); break;
        case 5:  HeapSort(&s); break;
      default:printf("你没有选择一个操作.\n");
      }
        printf("\n 已经排好序,序列为:\n");
       for(i=1;i<=num;i++)
         printf("%d   ",s.r[i].key);
        printf("\n\t 按任意键退出.\n");
        getchar();
    }