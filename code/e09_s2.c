/* 实验九 第2题：顺序栈实现算术表达式求值——中序转后序并求值（自行实现）
   例:输入 2*(6-4)+8/4  输出后序 264-*84/+ 值为6.00 */
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1024
typedef char DataType;
typedef struct
{ DataType data[MAXSIZE];
  int top;
}SeqStack;
int empty(SeqStack stack)            /* 检查栈是否为空 */
{ return stack.top==0;
}
int operation(char op)               /* 判断是否为运算符 */
{ return op=='+'||op=='-'||op=='*'||op=='/';
}
int priority(char op)                /* 判断运算符的优先权 */
{ if(op=='(') return 0;
  if(op=='+'||op=='-') return 1;
  if(op=='*'||op=='/') return 2;
  return -1;
}
SeqStack push(SeqStack stack,char value)  /* 入栈 */
{ if(stack.top>=MAXSIZE){ printf("栈满!\n"); exit(1); }
  stack.data[stack.top++]=value;
  return stack;
}
SeqStack pop(SeqStack stack,char *value)  /* 出栈 */
{ if(stack.top==0){ printf("栈空!\n"); exit(1); }
  *value=stack.data[--stack.top];
  return stack;
}
/* 中序表达式转换为后序表达式 */
void mid_to_post(char *mid,char *post)
{ SeqStack S; int i,j=0; char c;
  S.top=0;
  for(i=0; mid[i]!='\0'&&mid[i]!='\n'; i++)
  { if(mid[i]>='0'&&mid[i]<='9')          /* 操作数直接输出 */
      post[j++]=mid[i];
    else if(mid[i]=='(')                    /* 左括号入栈 */
      S=push(S,mid[i]);
    else if(mid[i]==')')                    /* 右括号:弹出至左括号 */
    { S=pop(S,&c);
      while(c!='('){ post[j++]=c; S=pop(S,&c); }
    }
    else if(operation(mid[i]))              /* 运算符:弹出优先级更高的 */
    { if(!empty(S))
      { c=S.data[S.top-1];
        while(!empty(S)&&priority(c)>=priority(mid[i]))
        { S=pop(S,&c); post[j++]=c;
          if(!empty(S)) c=S.data[S.top-1];
        }
      }
      S=push(S,mid[i]);
    }
  }
  while(!empty(S)) { S=pop(S,&c); post[j++]=c; }
  post[j++]='#'; post[j]='\0';
}
double count(char *backorder)        /* 计算后序(逆波兰)表达式的值 */
{ double st[MAXSIZE]; int top=0,i; double a,b;
  for(i=0; backorder[i]!='#'; i++)
  { if(backorder[i]>='0'&&backorder[i]<='9')
      st[top++]=backorder[i]-'0';
    else
    { b=st[--top]; a=st[--top];
      switch(backorder[i])
      { case '+': st[top++]=a+b; break;
        case '-': st[top++]=a-b; break;
        case '*': st[top++]=a*b; break;
        case '/': st[top++]=a/b; break;
      }
    }
  }
  return st[0];
}
int main()
{ char mid[MAXSIZE],post[MAXSIZE];
  printf("请输入中序表达式(数字限单位数,如 2*(6-4)+8/4):\n");
  fgets(mid,MAXSIZE,stdin);
  mid_to_post(mid,post);
  printf("后序表达式为:%s\n",post);
  printf("表达式的值为:%.2f\n",count(post));
  return 0;
}