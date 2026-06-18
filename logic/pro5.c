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

    int grid[R][R];
    for(int i=0;i<R;i++)
        for(int j=0;j<R;j++)
            grid[i][j]=0;


    for (int i = 0; i < C; i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        grid[u][v]=1;//rivalry between u and v
         grid[v][u]=1;
    }

    int color[R];
    for(int i=0;i<R;i++)
    {
        color[i]=-1;
    }//color array assigned

    for(int i=0;i<R;i++)
    {
        if(color[i]==-1)
        {
            //i is the starting point
            node *head=NULL;
            node *tail=NULL;

            color[i]=0;

            push(&head,&tail,i);

            while(head!=NULL)
            {
                int temp=head->r;
                pop(&head,&tail);//popping the head
                for(int k=0;k<R;k++)
                {
                    if(grid[temp][k]==1)//means rivalry
                    {
                        if(color[k]==-1)//not colored yet like not visited neighbours kosam
                        {
                            color[k]=1-color[temp];
                            push(&head,&tail,k);
                        }
                        else if(color[temp]==color[k])
                        {
                            printf("IMPOSSIBLE");
                            return 0;
                        }
                    }
                }

            }

        }
    }
   



    printf("POSSIBLE");
    return 0;
}