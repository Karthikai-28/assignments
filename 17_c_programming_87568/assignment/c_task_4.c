#include<stdio.h>
// function to print Pascal's Triangle
int PascalsTriangle(int n) {
    int arr[100][100];
    int i, j;
    for (i = 0; i < n; ++i) {
        // printing spaces
        for (j = 0; j < n - 1 - i; ++j) {
            printf(" ");
        }
        // calculating then printing the data of ith
        // row of Pascal's Trianle
        for (j = 0; j <= i; ++j) {
            if (j == 0 || j == i)
                arr[i][j] = 1;
            else
                arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int n;
    printf("Enter Number of Rows in Pascal's Trianle : ");
    scanf("%d", &n);
    PascalsTriangle(n);
    return 0;
}
