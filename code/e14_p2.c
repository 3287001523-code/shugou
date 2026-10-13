#include <stdio.h>
#include <stdlib.h>
#define n 5
#define MaxNum 10000  /*定义一个最大数*/
/* 定义邻接矩阵类型 */
typedef int  adjmatrix[n+1][n+1];   /* 0 号单元没用*/
typedef struct
   {int fromvex,tovex;
    int weight;
  }Edge;
typedef Edge *EdgeNode;
/* 1、普里姆算法 */
int arcnum;                 /*边的个数*/
 int arcnum;                 /*边的个数*/
 /* 建立图的邻接矩阵 */
 void CreatMatrix(adjmatrix GA)
 {int i,j,k,e;
  printf("图中有%d 个顶点\n",n);
 for(i=1;i<=n;i++)
     for(j=1;j<=n;j++)
     if(i==j) GA[i][j]=0;   /*对角线的值置为0*/
     else GA[i][j]=MaxNum;  /*其它位置的值初始化为一个最大数*/
 printf("请输入边的个数:");
 scanf("%d",&arcnum);
 printf("请输入边的信息,按照起点,终点,权值的形式输入:\n");
 for(k=1;k<=arcnum;k++)
     {scanf("%d,%d,%d",&i,&j,&e);   /*读入边的信息*/
       GA[i][j]=e;
       GA[j][i]=e;
     }
}
/*初始化图的边集数组*/
void InitEdge(EdgeNode GE,int m)
{int i;
 for(i=1;i<=m;i++) GE[i].weight=0;
}
/*根据图的邻接矩阵生成图的边集数组*/
void GetEdgeSet(adjmatrix GA,EdgeNode GE)
{int i,j,k=1;
 for(i=1;i<=n;i++)
    for(j=i+1;j<=n;j++)
     if(GA[i][j]!=0&&GA[i][j]!=MaxNum)
  {GE[k].fromvex=i;
   GE[k].tovex=j;
   GE[k].weight=GA[i][j];
   k++;
   }
}
/*按升序排列图的边集合数组*/
void SortEdge(EdgeNode GE,int m)
{int i,j,k;
 Edge temp;
 for(i=1;i<m;i++)
    {k=i;
     for(j=i+1;j<=m;j++)
   if(GE[k].weight>GE[j].weight) k=j;
     if(k!=i) {temp=GE[i];GE[i]=GE[k];GE[k]=temp;}
    }
}
/*输出边集数组的每条边*/
void OutEdge(EdgeNode GE,int e)
{int i;
    printf("按照起点,终点,权值的形式输出的最小生成树为:\n");
      for(i=1;i<=e;i++)
      printf("%d,%d,%d\n",GE[i].fromvex,GE[i].tovex,GE[i].weight);
    }
/* 利用克鲁斯卡尔算法从初始点v 出发求邻接矩阵表示的图的最小生成树 */
    void Kruskal(EdgeNode GE,EdgeNode T)
     {int i,j,k=1,s=1,m1,m2,flagi,flagj;
      for(i=1;i<n;i++)
        {T[i].fromvex=-1;
          T[i].tovex=-1;
        T[i].weight=MaxNum;
       }
      while(k<n)
       {m1=GE[s].fromvex;m2=GE[s].tovex;
          flagi=0;flagj=0;
          for(i=1;i<k;i++)
        {if(T[i].fromvex==m1||T[i].tovex==m1) flagi=1;
         if(T[i].fromvex==m2||T[i].tovex==m2) flagj=1;
        }
          if(!(flagi&&flagj))
        {T[k].fromvex=GE[s].fromvex;
          T[k].tovex=GE[s].tovex;
          T[k].weight=GE[s].weight;
         GE[s].weight=MaxNum;
         SortEdge(GE,arcnum);
        }
          else {GE[s].weight=MaxNum;
       SortEdge(GE,arcnum);
         k--;
       }
        k++;
     }
    }
      main()
      {adjmatrix GA;
      EdgeNode GE,T;
  GE=(EdgeNode)malloc(n*n*sizeof(Edge));
  T=(EdgeNode)malloc(n*sizeof(Edge));
       CreatMatrix(GA);
       InitEdge(GE,arcnum);
      GetEdgeSet(GA,GE);
      SortEdge(GE,arcnum);
       Kruskal(GE,T);
        printf("\n");
       OutEdge(T,n-1);
    }