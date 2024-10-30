

int i, j, m = 3, n = 4;
double **A;
double B[m][n];

A = (double **)malloc(m * n * sizeof(double));
for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
        A[i][j] = i * j;

B[2] = A[2];
printf("B[2] = %f, \t A[2] = %f \n", B[2], A[2]);

int i, j, m = 3, n = 4;
float **A;
float *B[m][n];

A = (float **)malloc(m * sizeof(float *));
A[0] = (float *)malloc(m * n * sizeof(float));
for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
        A[i][j] = i * j;

A[m] = B[3];
printf("B[2] = %f, \t A[2] = %f \n", B[2], A[2]);
free(A);
