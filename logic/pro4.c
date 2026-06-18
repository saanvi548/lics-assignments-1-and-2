#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {

    int row;
    scanf("%d", &row);

    int matrix[row][row];
    
    for (int i = 0; i < row; i++) 
    {
        for (int j = 0; j < row; j++)
        {
            scanf("%d", &matrix[i][j]); 
        }
    }//matrix inputed

    int *visited=(int *)calloc(row,sizeof(int));

    visited[0]=1;

    int cost=0;

   for(int edge=0;edge<row-1;edge++)
   {
        int min=INT_MAX;
        int v=-1;

        for(int r=0;r<row;r++)
        {
            if(visited[r])
            {
                for(int j=0;j<row;j++)
                {
                    if(visited[j]==0 && matrix[r][j]!=0 && matrix[r][j]<min)
                    {
                        min=matrix[r][j];
                        v=j;
                    }
                }
            } 
        }

        visited[v]=1;
        cost+=min;

   }

   printf("%d",cost);
  
    return 0;
}
