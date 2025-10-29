#include <stdio.h>
#define ROW 3
#define COL 3

void updateSector(int grid[ROW][COL]) {
    int r, c, bit;
    printf("Enter row and col: ");
    scanf("%d%d", &r, &c);
    printf("Enter bit to toggle (0=Power,1=Overload,2=Maintain): ");
    scanf("%d", &bit);
    grid[r][c] ^= (1 << bit);
    printf("status updated\n");
}
void querySector(int grid[ROW][COL]) {
    int r, c;
    printf("Enter row and col: ");
    scanf("%d%d", &r, &c);
    int val = grid[r][c];
    printf("Power: %s\n", (val & 1) ? "ON" : "OFF");
    printf("Overload: %s\n", (val & 2) ? "Yes" : "No");
    printf("Maintenance: %s\n", (val & 4) ? "Yes" : "No");
}
void diagnostic(int grid[ROW][COL]) {
    int ovr = 0, main = 0;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (grid[i][j] & 2) ovr++;
            if (grid[i][j] & 4) main++;
        }
    }
    printf("Total overloaded: %d\n", ovr);
    printf("Total maintenance: %d\n", main);
}
int main() {
    int grid[ROW][COL] = {0};
    int opt;
    while (1) {
        printf("\n--- IESCO Grid Menu ---\n");
        printf("1. Update sector\n");
        printf("2. Query sector\n");
        printf("3. Diagnostic\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                updateSector(grid);
                break;
            case 2:
                querySector(grid);
                break;
            case 3:
                diagnostic(grid);
                break;
            case 4:
                printf("bye\n");
                return 0;
            default:
                printf("wrong option\n");
        }
    }
}
