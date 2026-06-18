#include <stdio.h>
#include <stdlib.h>

int n;
int grid[100][100]; // adjacency matrix
int visited[100];
int path[100];
int pathLen = 0;
int found = 0;

void dfs(int current, int target) {
    visited[current] = 1;
    path[pathLen++] = current;

    if (current == target) {
        found = 1;
        return;
    }

    for (int i = 0; i < n; i++) 
    {
        if (grid[current][i] == 1 && !visited[i]) 
        {
            dfs(i, target);
            if (found) return; // stop once we reach target
        }
    }

    pathLen--; // backtrack if this branch didn’t reach target
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            grid[i][j] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        grid[u][v] = grid[v][u] = 1;
    }

    int s, t;
    scanf("%d %d", &s, &t);

    dfs(s, t);

    for (int i = 0; i < pathLen; i++) {
        printf("%d ", path[i]);
    }

    return 0;
}
