/* 实验十二 第1题：由前序和中序序列唯一确定二叉树（自行实现）
   前序 abd##e##cf### 格式输入的只是前序和中序字符序列 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
typedef char DataType;
typedef struct BitNode
{ DataType data;
  struct BitNode *lchild,*rchild;
}BitNode,*BitTree;
char pre[100],in[100];
/* 根据输入的前序和中序序列确定二叉树 */
void BuildSub(int PreStart,int PreEnd,int InStart,int InEnd,BitTree *root)
{ int i,LeftLen;
  if(PreStart>PreEnd){ *root=NULL; return; }
  *root=(BitTree)malloc(sizeof(BitNode));
  (*root)->data=pre[PreStart];
  for(i=InStart; i<=InEnd; i++)            /* 在中序中找根的位置 */
    if(in[i]==pre[PreStart]) break;
  LeftLen=i-InStart;                         /* 左子树结点个数 */
  BuildSub(PreStart+1,PreStart+LeftLen,InStart,i-1,&(*root)->lchild);
  BuildSub(PreStart+LeftLen+1,PreEnd,i+1,InEnd,&(*root)->rchild);
}
void BinTraversepost(BitTree BT)   /* 后序遍历二叉树 */
{ if(BT==NULL) return;
  BinTraversepost(BT->lchild);
  BinTraversepost(BT->rchild);
  printf("%c ",BT->data);
}
void PreTraverse(BitTree BT)
{ if(BT==NULL) return;
  printf("%c ",BT->data);
  PreTraverse(BT->lchild);
  PreTraverse(BT->rchild);
}
int main()
{ BitTree root; int len;
  printf("请输入前序序列(如 abdecf):\n");
  scanf("%s",pre);
  printf("请输入中序序列(如 dbaecf):\n");
  scanf("%s",in);
  len=strlen(pre);
  BuildSub(0,len-1,0,len-1,&root);
  printf("建立的二叉树的前序序列为:"); PreTraverse(root); printf("\n");
  printf("后序遍历序列为:"); BinTraversepost(root); printf("\n");
  return 0;
}