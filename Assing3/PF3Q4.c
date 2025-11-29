#include <stdio.h>
#include <string.h>

struct Book {
    int id;
    int pop;
    int lastAccess;
};

int findBook(struct Book shelf[], int size, int id)
{
    for (int i = 0; i < size; i++)
        if (shelf[i].id == id)
            return i;
    return -1;
}

int findLRU(struct Book shelf[], int size)
{
    int index = 0;
    for (int i = 1; i < size; i++)
        if (shelf[i].lastAccess < shelf[index].lastAccess)
            index = i;
    return index;
}

int main()
{
    int capacity, Q;
    printf("Enter capacity and number of operations: ");
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[100];
    int size = 0;
    int time = 1;

    char op[10];

    for (int i = 0; i < Q; i++)
    {
        printf("Enter operation (ADD / ACCESS): ");
        scanf("%s", op);

        if (strcmp(op, "ADD") == 0)
        {
            int x, y;
            scanf("%d %d", &x, &y);

            int pos = findBook(shelf, size, x);

            if (pos != -1)
            {
                shelf[pos].pop = y;
                shelf[pos].lastAccess = time++;
            }
            else
            {
                if (size < capacity)
                {
                    shelf[size].id = x;
                    shelf[size].pop = y;
                    shelf[size].lastAccess = time++;
                    size++;
                }
                else
                {
                    int lru = findLRU(shelf, size);
                    shelf[lru].id = x;
                    shelf[lru].pop = y;
                    shelf[lru].lastAccess = time++;
                }
            }
        }
        else if (strcmp(op, "ACCESS") == 0)
        {
            int x;
            scanf("%d", &x);

            int pos = findBook(shelf, size, x);

            if (pos == -1)
                printf("-1\n");
            else
            {
                printf("%d\n", shelf[pos].pop);
                shelf[pos].lastAccess = time++;
            }
        }
        else
        {
            printf("Invalid command!\n");
        }
    }

    return 0;
}
