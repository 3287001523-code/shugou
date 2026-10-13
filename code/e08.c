#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 100
// 题目1：栈的基本操作实现（顺序栈）
typedef struct {
      int data[MAX_SIZE];
      int top;
} SeqStack;
// 初始化栈
void InitStack(SeqStack *s) {
     s->top = -1;
}
// 判断栈是否为空
bool IsEmpty(SeqStack *s) {
     return s->top == -1;
}
// 判断栈是否已满
bool IsFull(SeqStack *s) {
     return s->top == MAX_SIZE - 1;
}
// 入栈操作
bool Push(SeqStack *s, int value) {
       if (IsFull(s)) {
       printf("栈已满，无法入栈\n");
          return false;
    }
     s->data[++s->top] = value;
     return true;
}
// 出栈操作
bool Pop(SeqStack *s, int *value) {
       if (IsEmpty(s)) {
       printf("栈为空，无法出栈\n");
          return false;
    }
    *value = s->data[s->top--];
     return true;
}
// 获取栈顶元素
bool GetTop(SeqStack *s, int *value) {
       if (IsEmpty(s)) {
        printf("栈为空\n");
          return false;
    }
    *value = s->data[s->top];
     return true;
}
// 打印栈内容
void PrintStack(SeqStack *s) {
       if (IsEmpty(s)) {
        printf("栈为空\n");
          return;
    }
   printf("栈内容（从栈底到栈顶）: ");
     for (int i = 0; i <= s->top; i++) {
         printf("%d ", s->data[i]);
    }
     printf("\n");
}
// 题目2：括号匹配检测
bool IsBracketMatch(char *expr) {
    SeqStack s;
     InitStack(&s);
     for (int i = 0; expr[i] != '\0'; i++) {
         char ch = expr[i];
              // 如果是左括号，入栈
             if (ch == '(' || ch == '[' || ch == '{') {
             Push(&s, ch);
        }
              // 如果是右括号，检查匹配
          else if (ch == ')' || ch == ']' || ch == '}') {
                    if (IsEmpty(&s)) {
                    return false;
            }
                 int top;
            GetTop(&s, &top);
                    if ((ch == ')' && top == '(') ||
                   (ch == ']' && top == '[') ||
                   (ch == '}' && top == '{')) {
                 Pop(&s, &top);
            } else {
                    return false;
            }
        }
    }
     return IsEmpty(&s);
}
// 题目3：表达式求值辅助函数
int GetPriority(char op) {
     switch (op) {
         case '+':
         case '-': return 1;
         case '*':
         case '/': return 2;
          default: return 0;
    }
}
int Calculate(int a, int b, char op) {
     switch (op) {
         case '+': return a + b;
         case '-': return a - b;
         case '*': return a * b;
         case '/': return a / b;
          default: return 0;
    }
}
// 表达式求值
int EvaluateExpression(char *expr) {
    SeqStack numStack;    // 数字栈
    SeqStack opStack;     // 运算符栈
    InitStack(&numStack);
     InitStack(&opStack);
     for (int i = 0; expr[i] != '\0'; i++) {
              // 跳过空格
             if (expr[i] == ' ') continue;
// 如果是数字
if (isdigit(expr[i])) {
      int num = 0;
     while (isdigit(expr[i])) {
       num = num * 10 + (expr[i] - '0');
         i++;
    }
       i--;
    Push(&numStack, num);
}
// 如果是左括号
else if (expr[i] == '(') {
    Push(&opStack, expr[i]);
}
// 如果是右括号
else if (expr[i] == ')') {
     while (1) {
           int op;
        GetTop(&opStack, &op);
             if (op == '(') {
             Pop(&opStack, &op);
              break;
        }
           int b, a;
        Pop(&numStack, &b);
        Pop(&numStack, &a);
        Pop(&opStack, &op);
        Push(&numStack, Calculate(a, b, op));
    }
}
// 如果是运算符
else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
     while (!IsEmpty(&opStack)) {
           int topOp;
        GetTop(&opStack, &topOp);
             if (topOp != '(' && GetPriority(topOp) >= GetPriority(expr[i])) {
                 int b, a;
            Pop(&numStack, &b);
            Pop(&numStack, &a);
             Pop(&opStack, &topOp);
            Push(&numStack, Calculate(a, b, topOp));
                 } else {
                        break;
                 }
            }
             Push(&opStack, expr[i]);
        }
    }
       // 处理剩余的运算符
     while (!IsEmpty(&opStack)) {
           int op, b, a;
        Pop(&opStack, &op);
        Pop(&numStack, &b);
        Pop(&numStack, &a);
        Push(&numStack, Calculate(a, b, op));
    }
      int result;
    Pop(&numStack, &result);
     return result;
}
// 题目4：数制转换
void ConvertBase(int num, int base) {
    SeqStack s;
     InitStack(&s);
     char digits[] = "0123456789ABCDEF";
     printf("%d 的 %d 进制表示为: ", num, base);
       // 处理0 的情况
       if (num == 0) {
           printf("0\n");
          return;
    }
       // 将余数入栈
     while (num > 0) {
         Push(&s, num % base);
       num /= base;
    }
       // 出栈并输出结果
     while (!IsEmpty(&s)) {
           int remainder;
        Pop(&s, &remainder);
          printf("%c", digits[remainder]);
    }
     printf("\n");
}
// 题目5：迷宫求解
#define ROWS 5
#define COLS 5
typedef struct {
      int x, y;
} Position;
int maze[ROWS][COLS] = {
     {0, 1, 0, 0, 0},
     {0, 1, 0, 1, 0},
     {0, 0, 0, 0, 0},
     {0, 1, 1, 1, 0},
     {0, 0, 0, 1, 0}
};
// 检查位置是否有效
bool IsValidPosition(int x, int y) {
     return x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 0;
}
// 解决迷宫问题
bool SolveMaze(Position start, Position end) {
    SeqStack s;
     InitStack(&s);
       // 记录访问过的位置
      int visited[ROWS][COLS] = {0};
       // 方向：上、右、下、左
      int dx[] = {-1, 0, 1, 0};
      int dy[] = {0, 1, 0, -1};
    Push(&s, start.x * COLS + start.y);
      visited[start.x][start.y] = 1;
while (!IsEmpty(&s)) {
      int posValue;
    GetTop(&s, &posValue);
      int x = posValue / COLS;
      int y = posValue % COLS;
       // 如果到达终点
       if (x == end.x && y == end.y) {
       printf("找到路径: ");
         SeqStack path;
          InitStack(&path);
              // 将路径存入另一个栈以便正序输出
         while (!IsEmpty(&s)) {
                 int p;
             Pop(&s, &p);
             Push(&path, p);
        }
              // 输出路径
         while (!IsEmpty(&path)) {
                 int p;
             Pop(&path, &p);
              printf("(%d,%d) ", p / COLS, p % COLS);
             Push(&s, p); // 恢复原栈
        }
           printf("\n");
          return true;
    }
    bool found = false;
     for (int i = 0; i < 4; i++) {
           int nx = x + dx[i];
           int ny = y + dy[i];
             if (IsValidPosition(nx, ny) && !visited[nx][ny]) {
             Push(&s, nx * COLS + ny);
               visited[nx][ny] = 1;
             found = true;
              break;
        }
    }
              // 如果没有可走的方向，回溯
             if (!found) {
             Pop(&s, &posValue);
        }
    }
    printf("没有找到路径\n");
     return false;
}
// 测试函数
int main() {
    printf("========== 题目1：栈的基本操作 ==========\n");
    SeqStack s;
     InitStack(&s);
       // 测试入栈
     for (int i = 1; i <= 5; i++) {
         Push(&s, i);
        printf("入栈: %d\n", i);
    }
     PrintStack(&s);
       // 测试获取栈顶元素
      int top;
       if (GetTop(&s, &top)) {
       printf("栈顶元素: %d\n", top);
    }
       // 测试出栈
      int value;
     while (!IsEmpty(&s)) {
        Pop(&s, &value);
        printf("出栈: %d\n", value);
    }
    printf("\n========== 题目2：括号匹配检测 ==========\n");
     char *expr1 = "((1+2)*3)";
     char *expr2 = "([{()}])";
     char *expr3 = "((1+2)*3";
     char *expr4 = "([)]";
    printf("表达式 %s 括号匹配: %s\n", expr1, IsBracketMatch(expr1) ? "是" : "否");
    printf("表达式 %s 括号匹配: %s\n", expr2, IsBracketMatch(expr2) ? "是" : "否");
    printf("表达式 %s 括号匹配: %s\n", expr3, IsBracketMatch(expr3) ? "是" : "否");
    printf("表达式 %s 括号匹配: %s\n", expr4, IsBracketMatch(expr4) ? "是" : "否");
    printf("\n========== 题目3：表达式求值 ==========\n");
     char *expr5 = "3 + 5 * 2";
     char *expr6 = "(3 + 5) * 2";
     char *expr7 = "10 - 2 * 3 + 1";
    printf("表达式 %s = %d\n", expr5, EvaluateExpression(expr5));
    printf("表达式 %s = %d\n", expr6, EvaluateExpression(expr6));
    printf("表达式 %s = %d\n", expr7, EvaluateExpression(expr7));
    printf("\n========== 题目4：数制转换 ==========\n");
    ConvertBase(10, 2);     // 10 转2 进制
    ConvertBase(255, 16); // 255 转16 进制
    ConvertBase(100, 8);    // 100 转8 进制
    printf("\n========== 题目5：迷宫求解 ==========\n");
     Position start = {0, 0};
     Position end = {4, 4};
   printf("迷宫地图 (0 可通行, 1 障碍物):\n");
     for (int i = 0; i < ROWS; i++) {
          for (int j = 0; j < COLS; j++) {
              printf("%d ", maze[i][j]);
        }
           printf("\n");
    }
     SolveMaze(start, end);
     return 0;
}