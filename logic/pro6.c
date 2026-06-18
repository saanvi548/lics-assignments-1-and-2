#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,m,k;

    scanf("%d %d %d", &n, &m,&k);

    int grid[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            grid[i][j]=0;


    for (int i = 0; i < m; i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        grid[u][v]=1;
        grid[v][u]=1;
    }
    
    int *degree=(int *)calloc(n,sizeof(int));

    for(int i=0;i<n;i++)
    {

        for(int j=0;j<n;j++)
        {
           degree[i]+=grid[i][j]; 
        }
    }

    int possible=1;

    while(possible)
    {
        possible=0;
        for(int i=0;i<n;i++)
        {
            if(degree[i]<k && degree[i]>=0)
            {   

                for(int j=0;j<n;j++)
                {   
                    if(grid[i][j]==1)
                    {
                        grid[i][j]=0;
                        grid[j][i]=0;
                        degree[j]--;

                    }
                }
                degree[i]=-1;
                possible=1;
            }
        }
    }
    
    int total =0;

    for(int i=0;i<n;i++)
    {
        if(degree[i]>=0)
        {
            total+=1;
        }
    }
    printf("%d ",total);
    return 0;

}