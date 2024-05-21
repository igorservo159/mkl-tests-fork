#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_args_LAPACK(int argc, const char *BIN, int rows, int columns, const char TYPE, const char *MATRIX_TYPE, const char *OPS, const int RANDOM_SEED){
    if(!strcmp(MATRIX_TYPE, "s")){
        if(rows != columns){
            printf("To one symmetric matrix the number of rows and columns must be equal\n");
            return -2;
        }
    }
    if(TYPE != 's' && TYPE != 'd' && TYPE != 'c' && TYPE != 'z'){
            printf("Use: %s <number_rows> <number_columns> <type> <matrix_type> <ops> <seed>\n", BIN);
        printf("Options to <type>: 's', 'd', 'c', 'z'\n");
        return -5;
    }
    if(strpbrk(MATRIX_TYPE, "gst") == NULL){
        printf("Use: %s <number_rows> <number_columns> <type> <matrix_type> <ops> <seed>\n", BIN);
        printf("Options to <matrix_type>: 'g', 's', 't', 'gs', 'gt'\n");
        return -3;
    }
    if(strpbrk(OPS, "fis") == NULL){
        printf("Use: %s <number_rows> <number_columns> <type> <matrix_type> <ops> <seed>\n", BIN);
        printf("Options to <ops>: 'f', 'fi', 'fs', 'fis', 'i', 's'. Obs: to types of matrix g and s, the matrix must be factored to realize others operations\n");
        return -4;
    }

    return 0;
}

int check_args_BLAS(int argc, const char *BIN, int A_rows, int A_columns, int B_rows, int B_columns, const char *OP, const int RANDOM_SEED){

    return 0;
}

int create_float_matrix(float **matrix, int rows, int columns){
    (*matrix) = (float *) malloc(rows*columns * sizeof(float));
    if ((*matrix) == NULL) {
        printf("Allocation error");
        free(*matrix);
        return -1;
    }

    return 0;
}

int create_int_matrix(int **matrix, int rows, int columns){
    (*matrix) = (int *) malloc(rows*columns * sizeof(int));
    if ((*matrix) == NULL) {
        printf("Allocation error");
        free(*matrix);
        return -1;
    }

    return 0;
}

int auto_float_fill(float **matrix, int rows, int columns, int seed){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    srand(seed);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*matrix)[j + (i*columns)] = rand()%10;
        }
    }

    return 0;
}

int symmetric_float_fill(float **matrix, int rows, int columns, int seed){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    srand(seed);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){    
            if(j >= i){
                (*matrix)[i*rows + j] = rand()%10;
            }else{
                (*matrix)[i*rows + j] = (*matrix)[j*rows + i];
            }
        }
    }

    return 0;
}

int triangular_float_fill(float **matrix, int rows, int columns, int seed){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    srand(seed);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){    
            if(j >= i){
                (*matrix)[i*rows + j] = rand()%10;
            }else{
                (*matrix)[i*rows + j] = 0;
            }
        }
    }

    return 0;
}

int show_float_matrix(float *matrix, int rows, int columns, char *matrix_name){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    printf("Matrix %s:\n", matrix_name);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            printf("%.2f ", matrix[j + (i*columns)]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

int show_int_matrix(int *matrix, int rows, int columns, char *matrix_name){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    printf("Matrix %s:\n", matrix_name);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            printf("%d ", matrix[j + (i*columns)]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

int show_float_packed_matrix(float *matrix, char uplo, int rows, int columns, char *matrix_name){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    printf("Matrix %s:\n", matrix_name);

    int k = 0;
    switch (uplo){
        case 'U':
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    if(i > j){
                        printf("%.2f ", 0.0);
                    }else{
                        printf("%.2f ", matrix[k++]);
                    }
                }
                printf("\n");
            }
            printf("\n");
            break;

        case 'L':
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    if(i <= j){
                        printf("%.2f ", 0.0);
                    }else{
                        printf("%.2f ", matrix[k++]);
                    }
                }
                printf("\n");
            }
            printf("\n");
            break;
        
        // Ajustando para matrizes simétricas
        default:
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    if(i > j){
                        printf("%.2f ", 0.0);
                    }else{
                        printf("%.2f ", matrix[k++]);
                    }
                }
                printf("\n");
            }
            printf("\n");
            break;
    }


    return 0;
}

int pack_float_matrix(float **A, float **AP, int rows, int columns, int n){
    if(A == NULL || AP == NULL){
        printf("One or more empty matrices");
        return -1;
    }
    if(rows != columns){
        printf("The matrix must be square");
        return -2;
    }
    if(rows != n){
        printf("Incompatible sizes");
        return -3;
    }

    // int k;
    // for(int i = 0; i < rows; i++){
    //     for(int j = 0; j < columns; j++){
    //         if(i <= j){
    //             k = j + i*(2*n - (i+1))/2;
    //             (*AP)[k] = (*A)[i*n + j];
    //         }
    //     }
    // }

    for(int i = 0, k = 0; i < n; i++){
        for(int j = i; j < n; j++){
            (*AP)[k] = (*A)[i*n + j];
            k++;
        }
    }

    return 0;
}

int packed_float_fill(float **matrix, int size, int seed){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    srand(seed);

    for(int i = 0; i < size; i++){
        (*matrix)[i] = rand()%10;
    }

    return 0;
}

int copy_float_matrix(float **dest, float **source, int size){
    if(dest == NULL || source == NULL){
        printf("One or more matrices empty\n");
        return -1;
    }

    for(int i = 0; i < size; i++){
        (*dest)[i] = (*source)[i];
    }

    return 0;
}

// double
int create_double_matrix(double **matrix, int rows, int columns){
    (*matrix) = (double *) malloc(rows*columns * sizeof(double));
    if ((*matrix) == NULL) {
        printf("Allocation error");
        free(*matrix);
        return -1;
    }

    return 0;
}

int auto_double_fill(double **matrix, int rows, int columns, int seed){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    srand(seed);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*matrix)[j + (i*columns)] = rand()%10;
        }
    }

    return 0;
}

int symmetric_double_fill(double **matrix, int rows, int columns, int seed){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    srand(seed);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){    
            if(j >= i){
                (*matrix)[i*rows + j] = rand()%10;
            }else{
                (*matrix)[i*rows + j] = (*matrix)[j*rows + i];
            }
        }
    }

    return 0;
}

int triangular_double_fill(double **matrix, int rows, int columns, int seed){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    srand(seed);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){    
            if(j >= i){
                (*matrix)[i*rows + j] = rand()%10;
            }else{
                (*matrix)[i*rows + j] = 0;
            }
        }
    }

    return 0;
}

int show_double_matrix(double *matrix, int rows, int columns, char *matrix_name){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    printf("Matrix %s:\n", matrix_name);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            printf("%.2f ", matrix[j + (i*columns)]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

int show_double_packed_matrix(double *matrix, char uplo, int rows, int columns, char *matrix_name){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    printf("Matrix %s:\n", matrix_name);

    int k = 0;
    switch (uplo){
        case 'U':
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    if(i > j){
                        printf("%.2f ", 0.0);
                    }else{
                        printf("%.2f ", matrix[k++]);
                    }
                }
                printf("\n");
            }
            printf("\n");
            break;

        case 'L':
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    if(i <= j){
                        printf("%.2f ", 0.0);
                    }else{
                        printf("%.2f ", matrix[k++]);
                    }
                }
                printf("\n");
            }
            printf("\n");
            break;
        
        // Ajustando para matrizes simétricas
        default:
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    if(i > j){
                        printf("%.2f ", 0.0);
                    }else{
                        printf("%.2f ", matrix[k++]);
                    }
                }
                printf("\n");
            }
            printf("\n");
            break;
    }


    return 0;
}

int pack_double_matrix(double **A, double **AP, int rows, int columns, int n){
    if(A == NULL || AP == NULL){
        printf("One or more empty matrices");
        return -1;
    }
    if(rows != columns){
        printf("The matrix must be square");
        return -2;
    }
    if(rows != n){
        printf("Incompatible sizes");
        return -3;
    }

    // int k;
    // for(int i = 0; i < rows; i++){
    //     for(int j = 0; j < columns; j++){
    //         if(i <= j){
    //             k = j + i*(2*n - (i+1))/2;
    //             (*AP)[k] = (*A)[i*n + j];
    //         }
    //     }
    // }

    for(int i = 0, k = 0; i < n; i++){
        for(int j = i; j < n; j++){
            (*AP)[k] = (*A)[i*n + j];
            k++;
        }
    }

    return 0;
}

int packed_double_fill(double **matrix, int size, int seed){
    if(matrix == NULL){
        printf("Empty matrix");
        return -1;
    }

    srand(seed);

    for(int i = 0; i < size; i++){
        (*matrix)[i] = rand()%10;
    }

    return 0;
}

int copy_double_matrix(double **dest, double **source, int size){
    if(dest == NULL || source == NULL){
        printf("One or more matrices empty\n");
        return -1;
    }

    for(int i = 0; i < size; i++){
        (*dest)[i] = (*source)[i];
    }

    return 0;
}