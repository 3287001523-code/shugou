#include <stdio.h>
#include <stdlib.h>
#define NULL 0
   #define ERROR 0
   #define OK 1
   typedef struct Lnode{
          int key;
         struct Lnode *lchild,*rchild;}BiTnode,*BiTree;
   void InitBiTree(BiTree *t)
   {*t=NULL;
   }
    int EmptyBitree(BiTree t)
   {if(t==NULL) return 1;
     else return 0;
    }
BiTree SearchBST(BiTree t, int k)
{ BiTree p;
  p=t;
  while((p!=NULL)&&(p->key!=k))
       if(k<p->key)  p=p->lchild;
        else  p=p->rchild;
    return(p);
}
void InorderBiTree(BiTree p)
{if(p)
  {InorderBiTree(p->lchild);
   printf("%d ",p->key);
    InorderBiTree(p->rchild);}
 }
void InsertBST(BiTree *t,int k)
{BiTnode *f,*p=*t;
 while(p)
   {if(p->key==k) return;
     f=p;
     p=(k<p->key)?p->lchild:p->rchild;
    }
 p=(BiTree)malloc(sizeof(BiTnode));
 p->key=k;
 p->lchild=p->rchild=NULL;
 if(*t==NULL) *t=p;
 else if (k<f->key) f->lchild=p;
        else f->rchild=p;
 }
void DelBST(BiTree *t,int k)
{/*在二叉排序树*t 中删除关键字为k 的结点*/
 BiTree p,f,r,q,s,root;
 root=*t;
 p=*t;  f=NULL;
 while(p)
    {if(p->key==k) break;           /*找到关键字为k 的结点*/
      f=p;
      p=(k<p->key)?p->lchild:p->rchild;
    /*  分别在*p 的左、右子树中查找*/
    }
 if(!p) return;         /*二叉排序树中无关键字为k 的结点*/
 if(p->lchild==NULL&&p->rchild==NULL)
    {if(p==*t) *t=NULL;
     else if(p==f->lchild) f->lchild=NULL;
   else f->rchild=NULL;
     free(p);
    }
 else
   if(p->lchild==NULL&&p->rchild!=NULL)               /* *p 无左子树*/
       { if(f->lchild==p)
           f->lchild=p->rchild;  /*将*p 的右子树链接到其父结点的左链上*/
         else
           f->rchild=p->rchild;  /*将*p 的右子树链接到其父结点的右链上*/
    free(p);
       }
    else if(p->rchild==NULL&&p->lchild!=NULL)        /**p 有左子树*/
     { if (f->lchild==p)            /*用*p 的左子树代替*p*/
          f->lchild=p->lchild;
        else
          f->rchild=p->lchild;
         free(p);
      }
   else if(p->lchild!=NULL&&p->rchild!=NULL)
       {q=p;s=p->lchild;
         while(s->rchild) {q=s;s=s->rchild;}
        p->key=s->key;
         if(q!=p) q->rchild=s->lchild;
         else q->lchild=s->lchild;
          free(s);
        }
}
main()
{BiTree t=NULL,p;
 int key;
 InitBiTree(&t);
 printf("请输入关键字的值,以0 结束:");
 scanf("%d",&key);
 while(key)
   {InsertBST(&t,key);
    scanf("%d",&key);
    }
 printf("中序遍历建立的二叉排序树的序列为:");
 InorderBiTree(t);
 printf("\n");
 printf("请输入要删除的结点的关键字的值:\n");
    scanf("%d",&key);
    DelBST(&t,key);
   printf("删除后的二叉排序树的中序序列为:");
     InorderBiTree(t);
     printf("\n");
   printf("请输入要查找的结点的关键字的值:\n");
    scanf("%d",&key);
    p=SearchBST(t,key);
    if(p==NULL) printf("没有查找到该结点\n");
     else printf("查找到该结点\n");
    }