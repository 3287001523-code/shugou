#include <stdio.h>
#include <stdlib.h>
     #define MAXSIZE 100
    void Js(int n,int k)
     {int i,j,s,A[MAXSIZE];
      for(i=0;i<n;i++) A[i]=1;     /*1 为是否输出标志*/
      j=0;
      for(i=0;i<n;i++)
     {s=0;
      while(s<k)  {j=(j%n)+1; s=s+A[j-1];}
      printf("%d ",j); A[j-1]=0;  /*输出当前应该出列的元素,标志置为0*/
    }
    }
    main()
     {int N,K;
   printf("请输入约瑟夫环中的元素个数N 和K :");
     scanf("%d%d",&N,&K);
      Js(N,K);
    }