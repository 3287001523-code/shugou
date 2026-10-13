/* 实验六 第4题：已知一个单链表，利用原表把单链表逆置（自行实现） */
#include <stdio.h>
#include <stdlib.h>
typedef int DataType;
typedef struct node
{ DataType data;
  struct node *next;
}ListNode, *LinkList;
/* 尾插法建立单链表 */
LinkList CreatList(void)
{ LinkList head=(LinkList)malloc(sizeof(ListNode));
  ListNode *p,*r=head; DataType x;
  head->next=NULL;
  printf("请输入链表元素(以0结束):\n");
  scanf("%d",&x);
  while(x)
  { p=(ListNode*)malloc(sizeof(ListNode));
    p->data=x; p->next=NULL; r->next=p; r=p;
    scanf("%d",&x);
  }
  return head;
}
/* 利用原表逆置：摘下首元结点，头插到链表前面 */
void ReverseList(LinkList L)
{ ListNode *p=L->next,*q;
  L->next=NULL;
  while(p)
  { q=p->next;
    p->next=L->next;
    L->next=p;
    p=q;
  }
}
void PrintList(LinkList L)
{ ListNode *p=L->next;
  while(p){ printf("%d ",p->data); p=p->next; }
  printf("\n");
}
int main()
{ LinkList L;
  L=CreatList();
  printf("逆置前的链表为:"); PrintList(L);
  ReverseList(L);
  printf("逆置后的链表为:"); PrintList(L);
  return 0;
}