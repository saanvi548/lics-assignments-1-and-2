#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int r;
    int c;
} node;

void push(node **head, node **tail, int r, int c) {
    node *new = (node *)calloc(1, sizeof(node));
    new->r = r;
    new->c = c;
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

    char grid[R][C];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            scanf(" %c", &grid[i][j]); // space before %c to skip whitespace

    int visited[R][C];
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            visited[i][j] = 0;

    int islandCount = 0;

    // Traverse every cell
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            // Start BFS if we find an unvisited land '1'
            if (grid[i][j] == '1' && !visited[i][j]) {
                islandCount++;

                node *head = NULL, *tail = NULL;
                push(&head, &tail, i, j);
                visited[i][j] = 1;

                // BFS
                while (head != NULL) {
                    int r = head->r;
                    int c = head->c;

                    // Up
                    if (r - 1 >= 0 && grid[r - 1][c] == '1' && !visited[r - 1][c]) {
                        visited[r - 1][c] = 1;
                        push(&head, &tail, r - 1, c);
                    }
                    // Down
                    if (r + 1 < R && grid[r + 1][c] == '1' && !visited[r + 1][c]) {
                        visited[r + 1][c] = 1;
                        push(&head, &tail, r + 1, c);
                    }
                    // Left
                    if (c - 1 >= 0 && grid[r][c - 1] == '1' && !visited[r][c - 1]) {
                        visited[r][c - 1] = 1;
                        push(&head, &tail, r, c - 1);
                    }
                    // Right
                    if (c + 1 < C && grid[r][c + 1] == '1' && !visited[r][c + 1]) {
                        visited[r][c + 1] = 1;
                        push(&head, &tail, r, c + 1);
                    }

                    pop(&head, &tail);
                }
            }
        }
    }

    printf("%d\n", islandCount);
    return 0;
}
