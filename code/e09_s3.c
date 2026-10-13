/* 实验九 第3题：链栈实现算术表达式求值（自行实现，与第2题要求相同） */
#include <stdio.h>
#include <stdlib.h>
typedef char DataType;
typedef struct StackNode
{ DataType data;
  struct StackNode *next;
}StackNode,*LinkedStack;
int LEmpty(LinkedStack top){ return top==NULL; }
LinkedStack LPush(LinkedStack top,char value)
{ StackNode *p=(StackNode*)malloc(sizeof(StackNode));
  p->data=value; p->next=top;
  return p;
}
LinkedStack LPop(LinkedStack top,char *value)
{ StackNode *p;
  if(LEmpty(top)){ printf("栈空!\n"); exit(1); }
  *value=top->data; p=top; top=top->next; free(p);
  return top;
}
int operation(char op)
{ return op=='+'||op=='-'||op=='*'||op=='/'; }
int priority(char op)
{ if(op=='(') return 0;
  if(op=='+'||op=='-') return 1;
  if(op=='*'||op=='/') return 2;
  return -1;
}
void mid_to_post(char *mid,char *post)
{ LinkedStack top=NULL; int i,j=0; char c;
  for(i=0; mid[i]!='\0'&&mid[i]!='\n'; i++)
  { if(mid[i]>='0'&&mid[i]<='9') post[j++]=mid[i];
    else if(mid[i]=='(') top=LPush(top,mid[i]);
    else if(mid[i]==')')
    { top=LPop(top,&c);
      while(c!='('){ post[j++]=c; top=LPop(top,&c); }
    }
    else if(operation(mid[i]))
    { if(!LEmpty(top))
      { while(!LEmpty(top)&&priority(top->data)>=priority(mid[i]))
        { top=LPop(top,&c); post[j++]=c; }
      }
      top=LPush(top,mid[i]);
    }
  }
  while(!LEmpty(top)){ top=LPop(top,&c); post[j++]=c; }
  post[j++]='#'; post[j]='\0';
}
double count(char *backorder)
{ double st[1024]; int t=0,i; double a,b;
  for(i=0; backorder[i]!='#'; i++)
  { if(backorder[i]>='0'&&backorder[i]<='9') st[t++]=backorder[i]-'0';
    else
    { b=st[--t]; a=st[--t];
      switch(backorder[i])
      { case '+': st[t++]=a+b; break;
        case '-': st[t++]=a-b; break;
        case '*': st[t++]=a*b; break;
        case '/': st[t++]=a/b; break;
      }
    }
  }
  return st[0];
}
int main()
{ char mid[1024],post[1024];
  printf("请输入中序表达式(数字限单位数,如 2*(6-4)+8/4):\n");
  fgets(mid,1024,stdin);
  mid_to_post(mid,post);
  printf("后序表达式为:%s\n",post);
  printf("表达式的值为:%.2f\n",count(post));
  return 0;
}