#include <stdlib.h>
#include <stdio.h>

void print_queens(int n, int* queens){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (queens[i] != j) {
                printf("  _");

            } else {
                printf("  Q");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

int is_safe(int* queens, int row, int col) {
    for(int i = 0; i < row; ++i) {
//      check diagonals and rows for other queens
        if((queens[i] == col) || (abs(i - row) == abs(queens[i] - col))) {
            return 0;
        }
    }
    return 1;
}

//  Complexitate: O(n^n)
void n_queens(int* queens, int row, int n) {
    for(int i = 0; i < n; ++i) {
//        check for queen's placement
        if(is_safe(queens, row, i)) {
//            set queen's row to i
            queens[row] = i;
//            end cond: all queens placed
            if(row == n - 1) {
                print_queens(n, queens);
            }
//            get to next row
            n_queens(queens, row + 1, n);
        }
    }
}

void test1() {
    int b_size = 4;
    int* queens = calloc(b_size, sizeof(int));

    printf("=========test1=========\n");
    n_queens(queens, 0, b_size);

    printf("\n");
}

void test2() {
    int b_size = 5;
    int *queens = calloc(b_size, sizeof(int));

    printf("=========test2=========\n");
    n_queens(queens, 0, b_size);

    printf("\n");
}

int main() {
    printf("---------------------------------Queens---------------------------------\n\n");

    test1();
    test2();

    return 0;
}
