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
    int R, C;
    scanf("%d %d", &R, &C);

    int grid[R][R];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < R; j++)
            grid[i][j] = 0;

    int *depend = (int *)calloc(R, sizeof(int));

    for (int j = 0; j < C; j++) {
        int u, v;
        scanf("%d %d", &u, &v);
        grid[u][v] = 1;
        depend[v]++; // indegree increment
    }

    node *head = NULL, *tail = NULL;

    // push all nodes with indegree 0
    for (int i = 0; i < R; i++)
        if (depend[i] == 0)
            push(&head, &tail, i);

    int count = 0;

    // BFS (Kahn’s algorithm)
    while (head != NULL) {
        int curr = head->r;
        count++;
        pop(&head, &tail);

        for (int i = 0; i < R; i++) {
            if (grid[curr][i] == 1) {
                depend[i]--;
                if (depend[i] == 0)
                    push(&head, &tail, i);
            }
        }
    }

    if (count < R)
        printf("PARADOX\n");
    else
        printf("VALID\n");

    return 0;
}
