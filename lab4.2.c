#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 5
#define m 8

void print_matrix(int **C, int N, int M);

void max_min_A(int **c, int N, int M);

void transpose_B(int **c, int N, int M);

void aXb(int **a, int **b, int N, int M);

void sort_a(int **a, int N, int M);

void sum_a_b(int **a, int **b, int N, int M);


int main() {
    int **a, **b;
    unsigned int work_flag = 0, array_filling_method_A, array_filling_method_B, action_number;

    srand(time(NULL));

    do {
        printf("\nHow to fill matrix A:"
               "\n1 - Enter values from the keyboard"
               "\n2 - Fill with random values");
        printf("\nPlease enter your choice: ");
        scanf("\n%d", &array_filling_method_A);
    } while (array_filling_method_A != 1 && array_filling_method_A != 2);

    //system("cls");

    a = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        a[i] = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (array_filling_method_A == 1) {
                printf("a[%d][%d] = ", i, j);
                scanf("%d", &a[i][j]);
            } else { a[i][j] = (0 + rand() % (1000 - 0 + 1)); }
        }
    }

    print_matrix(a, n, n);

    do {
        printf("\nHow to fill matrix B:"
               "\n1 - Enter values from the keyboard"
               "\n2 - Fill with random values");
        printf("\nPlease enter your choice: ");
        scanf("%d", &array_filling_method_B);
    } while (array_filling_method_B != 1 && array_filling_method_B != 2);

    // system("cls");


    b = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        b[i] = (int *) malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            if (array_filling_method_B == 1) {
                printf("a[%d][%d] = ", i, j);
                scanf("%d", &b[i][j]);
            } else { b[i][j] = (0 + rand() % (1000 - 0 + 1)); }
        }
    }
    print_matrix(b, n, m);

    while (work_flag != 1) {
        printf("\nSelect an action:"
               "\n1 - The maximum and minimum element of the matrix A"
               "\n2 - Transpose the matrix B"
               "\n3 - Find the matrix product A×B"
               "\n4 - Sort the elements of array A in ascending order"
               "\n5 - Display the sum of the elements of the rows of the matrix A and the columns of the matrix B"
               "\n6 - Exit the program");
        printf("\nPlease enter your choice: ");
        scanf("%d", &action_number);
        //system("cls");
        switch (action_number) {
            case 1:
                max_min_A(a, n, n);
                break;
            case 2:
                transpose_B(b, n, m);
                break;
            case 3:
                aXb(a, b, n, m);
                break;
            case 4:
                sort_a(a, n, n);
                break;
            case 5:
                sum_a_b(a, b, n, m);
                break;
            case 6:
                work_flag = 1;
                break;
            default:
                printf("\nSomething went wrong");
                break;
        }
    }
    for (int i = 0; i < n; i++) { free(a[i]); }
    free(a);
    for (int i = 0; i < n; i++) { free(b[i]); }
    free(b);
    return 0;
}


void print_matrix(int **c, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) { printf("%5d ", c[i][j]); }
        printf("\n");
    }
}

void max_min_A(int **c, int N, int M) {
    int max = c[0][0], min = c[0][0];
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; ++j) {
            if (min > c[i][j]) min = c[i][j];
            if (max < c[i][j]) max = c[i][j];
        }
    }
    printf("\nMin A: %d\nMax A: %d", min, max);
}

void transpose_B(int **c, int N, int M) {
    int **d;
    d = (int **) malloc(M * sizeof(int *));
    for (int i = 0; i < M; i++) {
        d[i] = (int *) malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) { d[i][j] = c[j][i]; }
    }

    print_matrix(d, M, N);

    for (int i = 0; i < M; i++) { free(d[i]); }
    free(d);
}


void aXb(int **a, int **b, int N, int M) {
    int **d;
    d = (int **) malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        d[i] = (int *) malloc(M * sizeof(int));
        for (int j = 0; j < M; j++) {
            d[i][j] = 0;
            for (int k = 0; k < N; k++) { d[i][j] += a[i][k] * b[k][j]; }
        }
    }

    print_matrix(d, N, M);

    for (int i = 0; i < N; i++) { free(d[i]); }
    free(d);
}

void sort_a(int **a, int N, int M) {
    unsigned int chose, line;
    int tmp;
    do {
        printf("\nSelect an action:"
               "\n1 - Sort the entire array A"
               "\n2 - Sort array row A");
        printf("\nPlease enter your choice: ");
        scanf("%d", &chose);
    } while (chose != 1 && chose != 2);
    switch (chose) {
        case 1:
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M - 1; ++j)
                    for (int k = 0; k < N - 1; ++k)
                        if (a[i][k + 1] < a[i][k]) {
                            tmp = a[i][k + 1];
                            a[i][k + 1] = a[i][k];
                            a[i][k] = tmp;
                        }
            break;
        case 2:
            printf("\nSelect a row to sort (0-%d): ", N);
            scanf("%d", &line);
            for (int j = 0; j < M - 1; ++j)
                for (int k = 0; k < N - 1; ++k)
                    if (a[line][k + 1] < a[line][k]) {
                        tmp = a[line][k + 1];
                        a[line][k + 1] = a[line][k];
                        a[line][k] = tmp;
                    }
            break;
        default:
            printf("\nSomething went wrong");
            break;
    }
    print_matrix(a, N, M);
}

void sum_a_b(int **a, int **b, int N, int M) {
    int sum;

    for (int i = 0; i < N; i++) {
        sum = 0;
        for (int j = 0; j < N; j++) { sum += a[i][j]; }
        printf("\nSum of %d line of array A: %d", i, sum);
    }

    printf("\n");

    for (int j = 0; j < M; j++) {
        sum = 0;
        for (int i = 0; i < N; i++) { sum += b[i][j]; }
        printf("\nSum of %d column of array B: %d", j, sum);
    }
    printf("\n");
}