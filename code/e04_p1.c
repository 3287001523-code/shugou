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
     SeqList reverse(SeqList A)     /*顺序表的就地逆置 */
    { int i,j;ElemType temp;
        for(i=0,j=A.length-1;i<j;i++,j--) /*i,j 分别是低端和高端下标*/
     {temp=A.data[i];                 /*交换*/
       A.data[i]=A.data[j];
      A.data[j] =temp;
    }
          return A;
    }
     /* 遍历顺序表 */
    void ListTraverse(SeqList L)
     {int i;
      if(L.length<=0) printf("顺序表为空\n");
      else {printf("当前顺序表中的元素为:\n");
         for(i=1;i<=L.length;i++) printf("%d ",L.data[i-1]);
                printf("\n");
     }
    }
     SeqList create(int n)
     {SeqList L;ElemType e;
       int i;
      printf("input element:\n");
      for(i=0;i<n;i++)
     {scanf("%d",&e); L.data[i]=e;}
      L.length=n;
      return L;
    }
    main()
     {int n;SeqList L;
      printf("input the number:");
      scanf("%d",&n);
      L=create(n);
      L=reverse(L);
    printf("顺序表已经逆置\n");
      ListTraverse(L);
    }