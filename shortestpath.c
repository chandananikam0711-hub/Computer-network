#include <stdio.h>

#define MAX_NODES 10
#define INFINITY 10000

int dist[MAX_NODES][MAX_NODES];
int distance[MAX_NODES];
int visited[MAX_NODES];
int predecessor[MAX_NODES];
int path[MAX_NODES];

int main()
{
    int n, i, j, src, dst;
    int min, current, count = 0;

    printf("SHORTEST PATH CALCULATION\n");

    printf("Enter number of nodes (less than 10): ");
    scanf("%d", &n);

    if (n < 2 || n >= MAX_NODES)
    {
        printf("Invalid number of nodes!\n");
        return 0;
    }

    printf("Enter distance matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &dist[i][j]);
        }
    }

    printf("Enter source node: ");
    scanf("%d", &src);

    printf("Enter destination node: ");
    scanf("%d", &dst);

    if (src < 1 || src > n ||
        dst < 1 || dst > n || src == dst)
    {
        printf("Invalid source or destination!\n");
        return 0;
    }

    src--;
    dst--;

    for (i = 0; i < n; i++)
    {
        distance[i] = INFINITY;
        visited[i] = 0;
        predecessor[i] = -1;
    }

    distance[src] = 0;

    for (i = 0; i < n; i++)
    {
        min = INFINITY;
        current = -1;

        for (j = 0; j < n; j++)
        {
            if (!visited[j] && distance[j] < min)
            {
                min = distance[j];
                current = j;
            }
        }

        if (current == -1)
            break;

        visited[current] = 1;

        for (j = 0; j < n; j++)
        {
            if (dist[current][j] > 0 &&
                !visited[j] &&
                distance[current] + dist[current][j]
                    < distance[j])
            {
                distance[j] =
                    distance[current] + dist[current][j];

                predecessor[j] = current;
            }
        }
    }

    if (distance[dst] == INFINITY)
    {
        printf("No path exists!\n");
        return 0;
    }

    current = dst;

    while (current != -1)
    {
        path[count++] = current;
        current = predecessor[current];
    }

    printf("Shortest path: ");

    for (i = count - 1; i >= 0; i--)
    {
        printf("%d", path[i] + 1);

        if (i > 0)
            printf(" ==> ");
    }

    printf("\nDistance of shortest path: %d\n",
           distance[dst]);

    return 0;
}