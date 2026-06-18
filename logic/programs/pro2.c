#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int r;
int visited[100];
int grid[100][100];
int len=0;
int path[100];
int found=0;

void dfs(int curr,int t)
{
    visited[curr]=1;
    path[len++]=curr;

    if(curr==t)
    {
        found=1;
        return;
    }

    for(int i=0;i<r;i++)
    {
        if(grid[curr][i]==1 && !visited[i])
        {
            dfs(i,t);
            if(found);
                return;
        }
    }

    len--;
}

int main()
{   

    scanf("%d",&r);

    for(int i=0;i<r;i++)
    {
        for(int j=0;j<r;j++)
        {
           
            grid[i][j]=0;
        }
    }
    
   
    for(int j=0;j<r-1;j++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        grid[u][v]=1;
        grid[v][u]=1;
    }
   
int s,t;
scanf("%d %d",&s,&t);
dfs(s,t);

for(int i=0;i<len;i++)
{
    printf("%d ",path[i]);
}

return 0;
}