#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int r;
    int c;
    int cost;
} node;

void push(node **head, node **tail, int r, int c, int cost) {
    node *new = (node *)calloc(1, sizeof(node));
    new->r = r;
    new->c = c;
    new->cost = cost;
    new->next = NULL;

    if (*head == NULL) {
        *head = *tail = new;
    } else {
        (*tail)->next = new;
        *tail = new;
    }
}

void pop(node **head, node **tail) {
    if (*head == NULL)
        return;

    node *temp = *head;
    if ((*head)->next == NULL)
        *head = *tail = NULL;
    else
        *head = (*head)->next;

    free(temp);
}

int main() {
    int r, c;
    scanf("%d %d", &r, &c);

    char matrix[r][c];
    int sr, sc;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf(" %c", &matrix[i][j]); // note the space before %c
            if (matrix[i][j] == 'S') {
                sr = i;
                sc = j;
            }
        }
    }

    int visited[r][c];
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            visited[i][j] = 0;

    int found = 0, shortest = -1;
    node *head = NULL, *tail = NULL;

    push(&head, &tail, sr, sc, 0);
    visited[sr][sc] = 1;

    while (head != NULL) {
        int cr = head->r;
        int cc = head->c;
        int cd = head->cost;

        if (matrix[cr][cc] == 'T') {
            found = 1;
            shortest = cd;
            break;
        }

        // Up
        if (cr - 1 >= 0 && !visited[cr - 1][cc] && matrix[cr - 1][cc] != 'X') {
            visited[cr - 1][cc] = 1;
            push(&head, &tail, cr - 1, cc, cd + 1);
        }
        // Down
        if (cr + 1 < r && !visited[cr + 1][cc] && matrix[cr + 1][cc] != 'X') {
            visited[cr + 1][cc] = 1;
            push(&head, &tail, cr + 1, cc, cd + 1);
        }
        // Left
        if (cc - 1 >= 0 && !visited[cr][cc - 1] && matrix[cr][cc - 1] != 'X') {
            visited[cr][cc - 1] = 1;
            push(&head, &tail, cr, cc - 1, cd + 1);
        }
        // Right
        if (cc + 1 < c && !visited[cr][cc + 1] && matrix[cr][cc + 1] != 'X') {
            visited[cr][cc + 1] = 1;
            push(&head, &tail, cr, cc + 1, cd + 1);
        }

        pop(&head, &tail);
    }

    printf("%d\n", shortest);
    return 0;
}
