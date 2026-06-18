#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int r;
} node;

void push(node **head, node **tail, int r) {
    node *new = (node *)calloc(1, sizeof(node));
    new->r = r;
    new->next = NULL;

    if (*head == NULL)
        *head = *tail = new;
    else {
        (*tail)->next = new;
        *tail = new;
    }
}

void pop(node **head, node **tail) {
    if (*head == NULL) return;
    node *temp = *head;
    if ((*head)->next == NULL)
        *head = *tail = NULL;
    else
        *head = (*head)->next;
    free(temp);
}

int main() {
    int R, C,k;
    scanf("%d %d %d", &R, &C,&k);

    int grid[R][R];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < R; j++)
            grid[i][j] = 0;

    int *visit = (int *)calloc(R, sizeof(int));
    int distance[R];
     for(int i=0;i<R;i++)
    {
        distance[i]=-1;
       
    }




    for (int j = 0; j < C; j++) {
        int u, v;
        scanf("%d %d", &u, &v);
        grid[u][v] = 1;
        grid[v][u] = 1;

    }

    node *head = NULL, *tail = NULL;

    int start;

    scanf(" %d",&start);

    push(&head,&tail,start);

    distance[start]=0;
    visit[start]=1;

    while(head!=NULL)
    {
        int temp=head->r;
        pop(&head,&tail);

        for(int i=0;i<R;i++)
        {
            if(grid[temp][i]==1 && visit[i]!=1)
            {
                visit[i]=1;
                push(&head,&tail,i);
                distance[i]=distance[temp]+1;
            }
        }
    }

    int found=0;

    for(int i=0;i<R;i++)
    {
        if(distance[i]==k)
        {
            found++;
            printf( "%d ",i);
        }
    }

    if(!found)
    printf("-1");

    return 0;
}
