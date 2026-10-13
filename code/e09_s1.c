/* 实验九 第1题：顺序栈的定义和操作（自行实现，函数框架按手册要求） */
#include <stdio.h>
#define MAXSIZE 1024
typedef int DataType;
typedef struct
{ DataType data[MAXSIZE];
  int top;
}SeqStack;
SeqStack *SeqStackInit(void)          /* 初始化顺序栈 */
{ SeqStack *S;
  S=(SeqStack*)malloc(sizeof(SeqStack)*1);
  S->top=0;
  return S;
}
int SeqStackEmpty(SeqStack S)          /* 检查顺序栈是否为空 */
{ return S.top==0;
}
void ClearStack(SeqStack *S)           /* 把S置为空栈 */
{ S->top=0;
}
void SeqStackPush(SeqStack *S,DataType x) /* 把x压入栈顶 */
{ if(S->top>=MAXSIZE){ printf("栈已满!\n"); return; }
  S->data[S->top]=x;
  S->top++;
}
DataType SeqStackPop(SeqStack *S)      /* 弹出栈顶元素 */
{ if(S->top==0){ printf("栈为空!\n"); return 0; }
  S->top--;
  return S->data[S->top];
}
DataType SeqStackGetTop(SeqStack S)    /* 取栈顶元素 */
{ if(S.top==0){ printf("栈为空!\n"); return 0; }
  return S.data[S.top-1];
}
void SeqStackPrint(SeqStack S)          /* 输出顺序栈中的元素 */
{ int i;
  for(i=0;i<S.top;i++) printf("%d ",S.data[i]);
  printf("\n");
}
int main()
{ SeqStack *S; DataType x; int i;
  S=SeqStackInit();
  printf("请输入入栈元素(以0结束):\n");
  scanf("%d",&x);
  while(x)
  { SeqStackPush(S,x); scanf("%d",&x); }
  printf("栈中元素(自栈底到栈顶)为:"); SeqStackPrint(*S);
  printf("栈顶元素为:%d\n",SeqStackGetTop(*S));
  printf("出栈一次,弹出元素:%d\n",SeqStackPop(S));
  printf("此时栈中元素为:"); SeqStackPrint(*S);
  if(SeqStackEmpty(*S)) printf("栈为空\n");
  else printf("栈非空\n");
  ClearStack(S);
  printf("清空栈后"); SeqStackPrint(*S);
  return 0;
}