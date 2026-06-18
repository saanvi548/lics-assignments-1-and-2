#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    int grid[N][N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            grid[i][j] = 0;

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        grid[u][v] = 1;
        grid[v][u] = 1;
    }

    int S;
    scanf("%d", &S);

    int active_curr[N], active_next[N];
    int parents_curr[N][N], parents_next[N][N];

     for (int i = 0; i < N; i++) 
        {
            active_curr[i] = 0;
            for (int j = 0; j < N; j++) 
            {
                parents_curr[i][j] = 0;
            }
        }

    active_curr[S]=1;

    for(int hop=0;hop<K;hop++)
    {
        for (int i = 0; i < N; i++) 
        {
            active_next[i] = 0;
            for (int j = 0; j < N; j++) 
            {
                parents_next[i][j] = 0;
            }
        }


        for(int i=0;i<N;i++)
        {
            if(active_curr[i])
            {
                for(int j=0;j<N;j++)
                {
                    if(grid[i][j])
                    {
                        if(!parents_curr[i][j])
                        {
                            active_next[j]=1;
                            parents_next[j][i]=1;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < N; i++) 
        {
            active_curr[i] = active_next[i];
            for (int j = 0; j < N; j++) 
            {
                parents_curr[i][j] = parents_next[i][j];
            }
        }
    }






    int found = 0;
    for (int i = 0; i < N; i++) {
        if (active_curr[i]) 
        {
            printf("%d ",i);
            found = 1;
        }
    }
    if (!found) printf("-1");
    printf("\n");

    return 0;
}
