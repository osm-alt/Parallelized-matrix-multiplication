// C program to multiply two matrices

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

// Edit MACROs here, according to your Matrix Dimensions for
// mat1[R1][C1] and mat2[R2][C2]
#define R1 100 // number of rows in Matrix-1
#define C1 50  // number of columns in Matrix-1
#define R2 50  // number of rows in Matrix-2
#define C2 100 // number of columns in Matrix-

#define num_threads 8

int rslt[R1][C2];
int elements_per_thread = (int)ceil((R1 * C2) / (float)num_threads);
int mat1[R1][C1];
int mat2[R2][C2];

void *calculate(void *threadID)
{
    long id = (long)threadID;
    for (int i = 0; i < elements_per_thread; i++)
    {
        int row = (id * elements_per_thread + i) / C2;
        int col = (id * elements_per_thread + i) % C2;

        if (row >= R1)
        {
            break;
        }
        rslt[row][col] = 0;

        for (int k = 0; k < R2; k++)
        {
            rslt[row][col] += mat1[row][k] * mat2[k][col];
        }
    }
}

void mulMat(int mat1[][C1], int mat2[][C2])
{
    pthread_t thread[num_threads];

    for (long i = 0; i < num_threads; i++)
    {
        if (pthread_create(&thread[i], NULL, calculate, (void *)i) != 0)
        {
            perror("Pthread_create fails");
        }
    }

    for (int i = 0; i < num_threads; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            perror("Pthread_join fails");
        }
    }

    printf("Multiplication of given two matrices is:\n");
    for (int i = 0; i < R1; i++)
    {
        for (int j = 0; j < C2; j++)
        {
            printf("%d\t", rslt[i][j]);
        }
        printf("\n");
    }
}

// Driver code
int main()
{
    clock_t t1 = clock();
    // R1 = 4, C1 = 4 and R2 = 4, C2 = 4 (Update these
    // values in MACROs)
    // int mat_1[R1][C1] = {{1, 1},
    //                      {2, 2}};

    // for (int i = 0; i < R1; i++)
    // {
    //     for (int j = 0; j < C1; j++)
    //     {
    //         mat1[i][j] = mat_1[i][j];
    //     }
    // }

    // int mat_2[R2][C2] = {{1, 1},
    //                      {2, 2}};

    // for (int i = 0; i < R2; i++)
    // {
    //     for (int j = 0; j < C2; j++)
    //     {
    //         mat2[i][j] = mat_2[i][j];
    //     }
    // }

    for (int i = 0; i < R1; i++)
    {
        for (int j = 0; j < C1; j++)
        {
            mat1[i][j] = 2;
        }
    }

    for (int i = 0; i < R2; i++)
    {
        for (int j = 0; j < C2; j++)
        {
            mat2[i][j] = 2;
        }
    }

    if (C1 != R2)
    {
        printf("The number of columns in Matrix-1 must be "
               "equal to the number of rows in "
               "Matrix-2\n");
        printf("Please update MACROs value according to "
               "your array dimension in "
               "#define section\n");

        exit(EXIT_FAILURE);
    }

    // Function call
    mulMat(mat1, mat2);

    clock_t t2 = clock();
    printf("Elapsed time = % 5.3f seconds\n", (float)(t2 - t1) / CLOCKS_PER_SEC);

    return 0;
}
