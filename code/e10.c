/* 实验十：鞍点问题——A[i][j]为第i行最小值且第j列最大值（自行实现）
   时间复杂度:O(m*n) */
#include <stdio.h>
#define M 10
#define N 10
int main()
{ int a[M][N],m,n,i,j,k,row,col,found=0;
  printf("请输入矩阵的行数和列数(如 3 4):\n");
  scanf("%d %d",&m,&n);
  printf("请输入%d个整数作为矩阵元素:\n",m*n);
  for(i=0;i<m;i++)
    for(j=0;j<n;j++) scanf("%d",&a[i][j]);
  printf("输入的矩阵为:\n");
  for(i=0;i<m;i++)
  { for(j=0;j<n;j++) printf("%4d",a[i][j]);
    printf("\n");
  }
  for(i=0;i<m;i++)                  /* 对每一行 */
  { col=0;
    for(j=1;j<n;j++)                 /* 找第i行最小值所在列col */
      if(a[i][j]<a[i][col]) col=j;
    for(k=0;k<m;k++)                 /* 检查a[i][col]是否为第col列最大值 */
      if(a[k][col]>a[i][col]) break;
    if(k>=m)
    { found=1;
      printf("矩阵中存在鞍点:a[%d][%d]=%d\n",i,col,a[i][col]);
    }
  }
  if(!found) printf("矩阵中不存在鞍点。\n");
  return 0;
}