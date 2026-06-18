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

int main() 
{
    int R, C;
    scanf("%d %d", &R, &C);

    if(R-1!=C)
    {
        printf("NO");
        return 0;
    }

    int grid[R][R];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < R; j++)
            grid[i][j] = 0;

    int *visit = (int *)calloc(R, sizeof(int));

    for (int j = 0; j < C; j++) {
        int u, v;
        scanf("%d %d", &u, &v);
        grid[u][v] = 1;
        grid[v][u] = 1;

    }

    node *head = NULL, *tail = NULL;

    int components=0;

    

    for(int i=0;i<R;i++)
    {
        if(!visit[i])
        {
            components++;
            push(&head,&tail,i);
            visit[i]=1;

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
                    }
                }
            }

        }
    }

    if(components>1)
        printf("NO");
    else
        printf("YES");

    return 0;
}