#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
  /*顺序表存储空间的总分配量*/
   #define MAXSIZE 100
   #define FALSE 0
   #define TRUE 1
    /* 顺序存储类型 */
typedef struct
{ElemType data[MAXSIZE]; /*存放线性表的数组*/
 int length;                   /* length 是顺序表的长度*/
}SeqList;
/* 初始化顺序表 */
SeqList SeqListInit( )
{SeqList L;
 L.length=0;
 return L;
 }
/* 清空顺序表 */
SeqList ListClear(SeqList L)
{L.length=0;
 return L;
}
/* 求顺序表长度 */
int ListLength(SeqList L)
 {return(L.length);}
/* 检查顺序表是否为空 */
int ListEmpty(SeqList L)
{if(L.length) return(FALSE);
 else return(TRUE);
}
/*检查顺序表是否为满 */
int ListFull(SeqList L)
{if(L.length==MAXSIZE) return(TRUE);
 else return(FALSE);
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
/* 从顺序表中查找元素 */
ElemType ListGet(SeqList L ,int i)
{ElemType e;
 e=L.data[i-1]; return(e);
}
/* 从顺序表中查找与给定元素值相同的元素在顺序表中的位置 */
int ListLocate(SeqList L, ElemType x)
{int i=0;
 while(i<L.length && L.data[i]!=x)
              i++;
  if (i<L.length)  return (i+1);
 else   return 0;
}
/* 向顺序表中插入元素 */
SeqList ListInsert(SeqList L,int i,ElemType x)
{int j;
 if(L.length==MAXSIZE)
     printf("表满,不能插入\n");
 else   if(i<1||i>L.length+1)
  printf("插入位置不正确\n");
         else { for(j=L.length-1;j>=i-1;j--)
        L.data[j+1]=L.data[j];
          L.data[i-1]=x;
         L.length++;
        }
 return L;
 }
/* 从顺序表中删除元素 */
SeqList ListDelete(SeqList L,int i)
{int j;ElemType x;
  if (i<1||i>L.length)
 printf("删除位置不正确\n");
 else {x=L.data[i-1];
         for(j=i;j<=L.length-1;j++)
         L.data[j-1]=L.data[j];
         L.length--;
         printf("%d 已被删除\n",x);
        }
 return L;
}
/*求顺序表中元素的前驱*/
ElemType SeqListPrior(SeqList L,ElemType e)
{int i=0;
 while(i<L.length&&L.data[i]!=e)
  i++;
 if(i==0) {printf("第一个元素没有前驱\n");return 0;}
 else if(i<=L.length-1)   return(L.data[i-1]);
        else  {printf("不存在值为%d 的元素\n",e);return 0;}
}
/*求顺序表中元素的后继*/
ElemType SeqListNext(SeqList L,ElemType e)
{int i=0;
 while(i<L.length&&L.data[i]!=e)
   i++;
 if(i==L.length-1) {printf("最后一个元素没有后继\n");return 0;}
 else if(i<L.length-1)   return(L.data[i+1]);
        else  {printf("不存在值为%d 的元素\n",e);return 0;}
}
int scan()
{int d;
 printf("请选择所要进行的操作\n");
 printf("1.初始化 2.清空3.求顺序表长度4.检查顺序表是否为空\n");
 printf("5.检查顺序表是否为满 6.遍历顺序表 7.从顺序表中查找元素\n");
 printf("8.从顺序表中查找与给定元素值相同的元素在顺序表中的位置\n");
 printf("9.向顺序表中插入元素10. 从顺序表中删除元素\n");
 printf("11.求元素的前驱    12.求元素的后继\n");
 printf("其他键退出......\n");
 scanf("%d",&d);
 return(d);
}
main()
{int quit=0;
int i,location;
 ElemType e,prior,next;
 SeqList L;
 printf("第一次操作需选择初始化\n");
 while(!quit)
 switch(scan())
 {case 1:L=SeqListInit();break;
 case 2:ListClear(L);break;
 case 3:printf("顺序表的长度为%d\n",ListLength(L));break;
 case 4:if(ListEmpty(L))printf("顺序表为空\n");else printf("顺序表不为空\n");break;
     case 5:if(ListFull(L))printf("顺序表满\n");else printf("顺序表不满\n");break;
     case 6:ListTraverse(L);
           break;
     case 7:printf("请输入要查找的元素的位置\n");
     scanf("%d",&i);
      if(L.length==0) printf("顺序表已空\n");
      else   if(i<=0||i>L.length) printf("查找的位置不正确\n");
              else
             printf("顺序表中第%d 个元素的值为:%d\n",i,ListGet(L,i));
      break;
     case 8:printf("请输入要查找的元素的值\n");
     scanf("%d",&e);
      if(L.length==0) printf("顺序表已空\n");
      else
      {location=ListLocate(L,e);
       if(location==0) printf("顺序表中不存在值为%d 的元素\n",e);
       else printf("顺序表中%d 的位置是:%d\n",e,ListLocate(L,e));
     }
      break;
     case 9:printf("请输入要插入的元素的位置和其值:\n");
     scanf("%d%d",&i,&e);
      L=ListInsert(L,i,e);
      break;
     case 10:printf("请输入要删除的元素的位置:\n");
       scanf("%d",&i);
       L=ListDelete(L,i);
       break;
     case 11:scanf("%d",&e);
       prior=SeqListPrior(L,e);
        if(prior) printf("%d 的前驱是:%d\n",e,prior);break;
     case 12:scanf("%d",&e);
       next=SeqListNext(L,e);
        if(next) printf("%d 的后继是:%d\n",e,next);break;
     default:quit=1;}
   }