#include <stdio.h>
#include <stdlib.h>
#define n 5
   #define MAXSIZE 10   /*广度优先遍历时所使用的队列的最大容量*/
   #define MaxNum 10000  /*定义一个最大数*/
    /* 定义邻接矩阵类型 */
   typedef int  adjmatrix[n+1][n+1];   /* 0 号单元没用*/
    int visited[n+1];                       /* 0 号单元没用*/
    int arcnum;                 /*边的个数*/
    /* 建立图的邻接矩阵 */
   void CreatMatrix(adjmatrix GA)
    {int i,j,k;
    printf("图中有%d 个顶点\n",n);
     for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
          if(i==j) GA[i][j]=0;   /*对角线的值置为0*/
          else GA[i][j]=MaxNum;  /*其它位置的值初始化为一个最大数*/
   printf("请输入边的个数(限制在1 到10 的范围内):");
    scanf("%d",&arcnum);
   printf("请输入图的所有边(一条边的两个端点中间用,分隔): , \n");
    for(k=1;k<=arcnum;k++)
         {scanf("%d,%d",&i,&j);   /*读入边的信息*/
           GA[i][j]=1;
           GA[j][i]=1;
        }
   }
    /* 从初始点v 出发深度优先搜索邻接矩阵GA 表示的图 */
void DfsMatrix(adjmatrix GA,int v)
{int j;
   visited[v]=1;   printf("%d,",v);
  for(j=1;j<=n;j++)
    if(v!=j&&GA[v][j]!=MaxNum&&!visited[j]) DfsMatrix(GA,j);
}
void BfsMatrix(adjmatrix GA,int v)
{int i,k,j,Q[MAXSIZE],front=0,rear=0;
 for(i=1;i<=n;i++) visited[i]=0;
 visited[v]=1;
 printf("%d ",v);
 rear=(rear+1)%MAXSIZE;          /*开始遍历的顶点入队列*/
 Q[rear]=v;
 while(front!=rear)
  {front=(front+1)%MAXSIZE;       /*队头元素出队*/
   k=Q[front];
   for(j=1;j<=n;j++)
      if((!visited[j])&&(GA[k][j]==1))  /*访问与队头元素邻接的还未被访问的结点*/
        {visited[j]=1;
         printf("%d ",j);
       rear=(rear+1)%MAXSIZE;
         Q[rear]=j;
        }
   }
}
 main()
 {adjmatrix GA;
   int v;
  CreatMatrix(GA);
 printf("请输入深度优先遍历的开始结点:");
  scanf("%d",&v);
  printf("深度优先遍历序列是:");
  DfsMatrix(GA,v);
   printf("\n");
 printf("请输入广度优先遍历的开始结点:");
  scanf("%d",&v);
  printf("广度优先遍历序列是:");
  BfsMatrix(GA,v);
   }