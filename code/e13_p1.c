#include <stdio.h>
#include <stdlib.h>
#define MAXNODE 10
   #define NULL 0
   typedef struct arc
        {int adjvex;
         struct arc *next;}ArcNode;
   typedef struct VexNode
    {int vertex;
    ArcNode *firstarc;
   }VerNode;
   typedef VerNode AdjList[MAXNODE];
    int visited[MAXNODE];
    int vexnum,arcnum;
   void creatgraph(AdjList GL)
    {int i,j,k;
    ArcNode *p;
   printf("请输入顶点个数和边的个数:");
    scanf("%d%d",&vexnum,&arcnum);
   printf("请输入顶点(顶点用整型数代表):\n");
     for(i=1;i<=vexnum;i++)
         {scanf("%d",&GL[i].vertex);
          GL[i].firstarc=NULL;
         }
   printf("请输入图的所有边(一条边的两个端点中间用,分隔): , \n");
    for(k=1;k<=arcnum;k++)
         {scanf("%d,%d",&i,&j);
           if(i&&j)
       {p=(ArcNode*)malloc(sizeof(ArcNode));
         p->adjvex=j;p->next=GL[i].firstarc;GL[i].firstarc=p;
        p=(ArcNode*)malloc(sizeof(ArcNode));
         p->adjvex=i;p->next=GL[j].firstarc; GL[j].firstarc=p;
       }
         }
    }
void DfsAdjlist(AdjList GL,int v)
{int i;
 for(i=1;i<=vexnum;i++) visited[i]=0;
 if(!visited[v]) dfs(GL,v);
 }
int dfs(AdjList G,int v)
 {ArcNode *q;
   if(!visited[v])  printf("%d,",G[v].vertex);
   visited[v]=1;
   q=G[v].firstarc;
  while(q!=NULL)
      {if(!visited[q->adjvex]) dfs(G,q->adjvex);
       q=q->next;
  }
}
int BfsAdjlist(AdjList GL,int v)
{int k,i,j,Q[MAXNODE],front=0,rear=0;
 ArcNode *p;
 for(i=1;i<=vexnum;i++) visited[i]=0;
 visited[v]=1;
 printf("%d ",GL[v].vertex);
 rear=(rear+1)%MAXNODE;
 Q[rear]=v;
 while(front!=rear)
  {front=(front+1)%MAXNODE;
   k=Q[front];
   p=GL[k].firstarc;
   while(p!=NULL)
      {if(!visited[p->adjvex])
        {visited[p->adjvex]=1;
         printf("%d ",p->adjvex);
       rear=(rear+1)%MAXNODE;
        Q[rear]=p->adjvex;
        }
       p=p->next;
      }
   }
}
 main()
 {AdjList GL;
       int v;
      creatgraph(GL);
    printf("请输入深度优先遍历的开始结点:");
      scanf("%d",&v);
    printf("深度优先遍历序列是:");
      DfsAdjlist(GL,v);
       printf("\n");
    printf("请输入广度优先遍历的开始结点:");
      scanf("%d",&v);
    printf("广度优先遍历序列是:");
      BfsAdjlist(GL,v);
     }