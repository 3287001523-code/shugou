#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;      /* 定义ElemType 为int 类型 */
  /*顺序表存储空间的总分配量*/
     #define MAXSIZE 100
     #define FALSE 0
     #define TRUE 1
     typedef struct                           /* 顺序存储类型 */
    {ElemType data[MAXSIZE];       /*存放线性表的数组*/
       int length;                            /* length 是顺序表的长度*/
     }SeqList;
     SeqList MergeSeqList(SeqList La,SeqList Lb,int m,int n)
     {int i,j,k;
      SeqList Lc;
     i=La.length-1;j=Lb.length-1;k=m+n-1;/*从后向前比较*/
     while(i>=0&&j>=0)
     if(La.data[i]>=Lb.data[j])        /*大的向La 的后面复制*/
            {La.data[k]=La.data[i];i--;k--;}
      else   {La.data[k]=Lb.data[j];j--;k--;}
      while(i>0) {Lc.data[k]=La.data[i];i--;k--;}/*La 没有结束*/
      while(j>0) {Lc.data[k]=Lb.data[j];j--;k--;} /*Lb 没有结束*/
     La.length=m+n;          /*合并后的表长*/
      return La;
    }
    void ListTraverse(SeqList L)        /* 遍历顺序表 */
     {int i;
      if(L.length<=0) printf("顺序表为空\n");
      else {printf("当前顺序表中的元素为:\n");
         for(i=1;i<=L.length;i++) printf("%d ",L.data[i-1]);
                printf("\n");
     }
    }
     SeqList create()
     {SeqList L;ElemType e;
       int i=0;
      scanf("%d",&e);
      while(e!=-1)
          { L.data[i]=e;i++;scanf("%d",&e);}
      L.length=i;
      return L;
    }
    main()
     {int n;SeqList La,Lb,Lc;
    printf("请输入非递减有序的La 的元素,输入-1 结束:\n");
      La=create();
    printf("请输入非递减有序的Lb 的元素,输入-1 结束:\n");
      Lb=create();
      Lc=MergeSeqList(La,Lb,La.length,Lb.length);
    printf("顺序表已经合并\n");
      ListTraverse(Lc);
    }