#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX 50

// ---------- PRINT GRID ----------
void printGrid(int matrix[MAX][MAX], int rows, int cols) {
    printf("\nBattlefield Grid:\n");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ---------- RANDOM GRID ----------
void generateGrid(int matrix[MAX][MAX], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            matrix[i][j] = (rand() % 31) - 10;
        }
    }
}

// ---------- MANUAL INPUT ----------
void inputGrid(int matrix[MAX][MAX], int rows, int cols) {
    printf("Enter grid values:\n");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// ---------- KADANE ----------
int kadane(int arr[], int n, int *start, int *finish) {
    int sum = 0, maxSum = INT_MIN;
    int local_start = 0;
    *finish = -1;

    for(int i = 0; i < n; i++) {
        sum += arr[i];

        if(sum < arr[i]) {
            sum = arr[i];
            local_start = i;
        }

        if(sum > maxSum) {
            maxSum = sum;
            *start = local_start;
            *finish = i;
        }
    }

    if(*finish != -1)
        return maxSum;

    maxSum = arr[0];
    *start = *finish = 0;

    for(int i = 1; i < n; i++) {
        if(arr[i] > maxSum) {
            maxSum = arr[i];
            *start = *finish = i;
        }
    }

    return maxSum;
}

// ---------- MAX SUM SUBMATRIX ----------
int maxSumSubmatrix(int matrix[MAX][MAX], int rows, int cols,
                    int *top, int *bottom, int *left, int *right) {

    int maxSum = INT_MIN;

    for(int l = 0; l < cols; l++) {
        int temp[MAX] = {0};

        for(int r = l; r < cols; r++) {

            for(int i = 0; i < rows; i++)
                temp[i] += matrix[i][r];

            int start, finish;
            int sum = kadane(temp, rows, &start, &finish);

            if(sum > maxSum) {
                maxSum = sum;
                *left = l;
                *right = r;
                *top = start;
                *bottom = finish;
            }
        }
    }

    return maxSum;
}

// ---------- ITEM STRUCT ----------
struct Item {
    char name[20];
    int value;
    int weight;
};

// ---------- 0/1 KNAPSACK ----------
int knapsack01(struct Item items[], int n, int capacity) {
    int dp[n+1][capacity+1];

    for(int i = 0; i <= n; i++) {
        for(int w = 0; w <= capacity; w++) {
            if(i == 0 || w == 0)
                dp[i][w] = 0;
            else if(items[i-1].weight <= w) {
                int include = items[i-1].value + dp[i-1][w - items[i-1].weight];
                int exclude = dp[i-1][w];
                dp[i][w] = (include > exclude) ? include : exclude;
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    printf("\nSelected Items:\n");
    int w = capacity;

    for(int i = n; i > 0 && w > 0; i--) {
        if(dp[i][w] != dp[i-1][w]) {
            printf("%s (taken)\n", items[i-1].name);
            w -= items[i-1].weight;
        }
    }

    return dp[n][capacity];
}

// ---------- MAIN ----------
int main() {
    int matrix[MAX][MAX];
    int rows, cols, choice;

    srand(time(0));

    printf("Enter battlefield grid size (rows cols): ");
    scanf("%d %d", &rows, &cols);

    printf("\n1. Manual Input\n2. Random Generation\nEnter choice: ");
    scanf("%d", &choice);

    if(choice == 1)
        inputGrid(matrix, rows, cols);
    else if(choice == 2)
        generateGrid(matrix, rows, cols);
    else {
        printf("Invalid choice\n");
        return 0;
    }

    printGrid(matrix, rows, cols);

    // ---------- FIND BEST REGION ----------
    int top, bottom, left, right;

    int bestSum = maxSumSubmatrix(matrix, rows, cols,
                                 &top, &bottom, &left, &right);

    printf("\nBest battlefield region score = %d\n", bestSum);

    // ---------- EXTRACT ITEMS FROM REGION ----------
    int guns=0, ammo=0, medkit=0, armor=0;

    for(int i = top; i <= bottom; i++) {
        for(int j = left; j <= right; j++) {

            int val = matrix[i][j];

            if(val >= 15) guns++;
            else if(val >= 10) armor++;
            else if(val >= 5) medkit++;
            else if(val > 0) ammo++;
        }
    }

    printf("\nItems found in region:\n");
    printf("Guns=%d Ammo=%d Medkit=%d Armor=%d\n",
           guns, ammo, medkit, armor);

    // ---------- CREATE ITEMS ----------
    struct Item items[4];
    int n = 0;

    if(guns > 0)
        items[n++] = (struct Item){"Guns", 60 * guns, 40 * guns};

    if(ammo > 0)
        items[n++] = (struct Item){"Ammo", 40 * ammo, 20 * ammo};

    if(medkit > 0)
        items[n++] = (struct Item){"Medkit", 50 * medkit, 30 * medkit};

    if(armor > 0)
        items[n++] = (struct Item){"Armor", 50 * armor, 40 * armor};

    int capacity = 120;
    printf("\nPlayer Capacity = %d\n", capacity);

    int maxValue = knapsack01(items, n, capacity);

    printf("\nMaximum loot value = %d\n", maxValue);

    return 0;
}
