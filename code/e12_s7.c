/* 实验十二 第7题：哈夫曼树和哈夫曼编码（自行实现，按手册要求的四个子程序）
   从终端输入若干字符组成的正文，统计频率建立哈夫曼树并编码 */
#include <stdio.h>
#include <string.h>
#define LEAF 30        /* 最多叶子(字符)数 */
#define NODE 2*LEAF    /* 总结点数上限 */
typedef struct
{ int weight;          /* 权值(字符出现频率) */
  int parent,lchild,rchild;
  char ch;             /* 叶子对应的字符 */
}HTree;
HTree t[NODE];
int leafnum=0;         /* 实际叶子数 */
/* 统计字符出现的频率,成功返回1 */
int freqchar(char *text, HTree *t)
{ int i,j,w[256]={0};
  for(i=0; text[i]!='\0'&&text[i]!='\n'; i++)
    w[(unsigned char)text[i]]++;
  for(i=0,j=0; i<256; i++)
    if(w[i])
    { t[j].weight=w[i]; t[j].ch=(char)i;
      t[j].parent=t[j].lchild=t[j].rchild=0;
      j++;
    }
  leafnum=j;
  return leafnum>0;
}
/* 根据字符出现的频率建立哈夫曼树,返回根结点下标 */
int createhtree(HTree *t)
{ int total,i,min1,min2,k1,k2;
  total=2*leafnum-1;
  for(i=leafnum;i<total;i++)
  { t[i].weight=0; t[i].ch=0;
    t[i].parent=t[i].lchild=t[i].rchild=0;
  }
  for(i=leafnum;i<total;i++)
  { min1=min2=0x7fffffff; k1=k2=-1;
    for(int j=0;j<i;j++)
      if(t[j].parent==0)
      { if(t[j].weight<min1){ min2=min1;k2=k1; min1=t[j].weight;k1=j; }
        else if(t[j].weight<min2){ min2=t[j].weight; k2=j; }
      }
    t[k1].parent=i; t[k2].parent=i;
    t[i].lchild=k1; t[i].rchild=k2;
    t[i].weight=t[k1].weight+t[k2].weight;
  }
  return total-1;
}
/* 对哈夫曼树进行编码:从根走到叶子,左0右1 */
void coding(HTree *t,int head_i,char *code)
{ char buf[100];
  int i;
  for(i=0;i<leafnum;i++)
  { int j=i,len=0,p;
    p=t[j].parent;
    while(p)
    { if(t[p].lchild==j) buf[len++]='0';
      else buf[len++]='1';
      j=p; p=t[j].parent;
    }
    buf[len]='\0';
    /* 逆序得到真正的编码 */
    for(int k=0;k<len;k++) code[k]=buf[len-1-k];
    code[len]='\0';
    printf("字符%c 出现%d次 编码:%s\n",t[i].ch,t[i].weight,code);
    code+=64;
  }
}
/* 中序打印哈夫曼树形状 */
void printhtree(HTree *t,int head_i,int deep,int *path)
{ int i;
  if(head_i==0) return;
  printhtree(t,t[head_i].lchild,deep+1,path);
  for(i=0;i<deep;i++) printf("    ");
  if(t[head_i].ch) printf("%c(%d)\n",t[head_i].ch,t[head_i].weight);
  else printf("%d\n",t[head_i].weight);
  printhtree(t,t[head_i].rchild,deep+1,path);
}
int main()
{ char text[1000],code[64*LEAF];
  int root;
  printf("请输入一段由若干字符组成的文本:\n");
  fgets(text,1000,stdin);
  if(!freqchar(text,t)) { printf("无有效字符!\n"); return 0; }
  printf("共统计到%d种字符,频率(权值)分别为:\n",leafnum);
  for(int i=0;i<leafnum;i++)
    printf("字符%c: %d次  ",t[i].ch,t[i].weight);
  printf("\n");
  root=createhtree(t);
  printf("哈夫曼树(中序缩进打印,叶处显示字符):\n");
  printhtree(t,root,0,NULL);
  printf("各字符的哈夫曼编码:\n");
  coding(t,root,code);
  return 0;
}