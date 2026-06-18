#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int tower;     // current tower
    int parent;    // tower we came from
    int hops;      // current hop count
    struct node *next;
} node;

void push(node **head, node **tail, int tower, int parent, int hops) {
    node *new = (node *)calloc(1, sizeof(node));
    new->tower = tower;
    new->parent = parent;
    new->hops = hops;
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

    // array to mark towers reached exactly at K hops
    int reached[N];
    for (int i = 0; i < N; i++) reached[i] = 0;

    node *head = NULL, *tail = NULL;
    push(&head, &tail, S, -1, 0); // parent=-1 for source

    while (head != NULL) {
        int curr = head->tower;
        int parent = head->parent;
        int hops = head->hops;
        pop(&head, &tail);

        if (hops == K) {
            reached[curr] = 1;
            continue; // do not propagate further
        }

        for (int i = 0; i < N; i++) {
            if (grid[curr][i] && i != parent) {
                push(&head, &tail, i, curr, hops + 1);
            }
        }
    }

    int found = 0;
    for (int i = 0; i < N; i++) {
        if (reached[i]) {
            printf("%d ", i);
            found = 1;
        }
    }
    if (!found) printf("-1");

    return 0;
}
