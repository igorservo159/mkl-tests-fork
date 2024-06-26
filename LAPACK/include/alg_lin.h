#ifndef ALGLIN_H
#define ALGLIN_H

#include <mkl.h>

int check_args_LAPACK(const char *BIN, int rows, int columns, const char TYPE, const char *MATRIX_TYPE, const char *OPS);

int create_float_matrix(float **matrix, int rows, int columns);
int auto_float_fill(float **matrix, int rows, int columns, int seed);
int auto_float_static_fill(float *matrix, int rows, int columns, int seed);
int symmetric_float_fill(float **matrix, int rows, int columns, int seed);
int triangular_float_fill(float **matrix, int rows, int columns, int seed);
int show_float_matrix(float *matrix, int rows, int columns, char *matrix_name);
int show_int_matrix(int *matrix, int rows, int columns, char *matrix_name);
int show_float_packed_matrix(float *matrix, char uplo, int rows, int columns, char *matrix_name);
int pack_float_matrix(float **A, float **AP, int rows, int columns, int n);
int packed_float_fill(float **matrix, int size, int seed);
int copy_float_matrix(float **dest, float **source, int size);
void transpose_float_general_matrix(float **matrix, int rows, int columns);

int create_double_matrix(double **matrix, int rows, int columns);
int auto_double_fill(double **matrix, int rows, int columns, int seed);
int auto_double_static_fill(double *matrix, int rows, int columns, int seed);
int symmetric_double_fill(double **matrix, int rows, int columns, int seed);
int triangular_double_fill(double **matrix, int rows, int columns, int seed);
int show_double_matrix(double *matrix, int rows, int columns, char *matrix_name);
int show_double_packed_matrix(double *matrix, char uplo, int rows, int columns, char *matrix_name);
int pack_double_matrix(double **A, double **AP, int rows, int columns, int n);
int packed_double_fill(double **matrix, int size, int seed);
int copy_double_matrix(double **dest, double **source, int size);
void transpose_double_general_matrix(double **matrix, int rows, int columns);

int create_complex_float_matrix(lapack_complex_float **matrix, int rows, int columns);
int auto_complex_float_fill(lapack_complex_float **matrix, int rows, int columns, int seed);
int auto_complex_float_static_fill(lapack_complex_float *matrix, int rows, int columns, int seed);
int symmetric_complex_float_fill(lapack_complex_float **matrix, int rows, int columns, int seed);
int triangular_complex_float_fill(lapack_complex_float **matrix, int rows, int columns, int seed);
int show_complex_float_matrix(lapack_complex_float *matrix, int rows, int columns, char *matrix_name);
int show_complex_float_packed_matrix(lapack_complex_float *matrix, char uplo, int rows, int columns, char *matrix_name);
int pack_complex_float_matrix(lapack_complex_float **A, lapack_complex_float **AP, int rows, int columns, int n);
int packed_complex_float_fill(lapack_complex_float **matrix, int size, int seed);
int copy_complex_float_matrix(lapack_complex_float **dest, lapack_complex_float **source, int size);
void transpose_complex_float_general_matrix(lapack_complex_float **matrix, int rows, int columns);

int create_complex_double_matrix(lapack_complex_double **matrix, int rows, int columns);
int auto_complex_double_fill(lapack_complex_double **matrix, int rows, int columns, int seed);
int auto_complex_double_static_fill(lapack_complex_double *matrix, int rows, int columns, int seed);
int symmetric_complex_double_fill(lapack_complex_double **matrix, int rows, int columns, int seed);
int triangular_complex_double_fill(lapack_complex_double **matrix, int rows, int columns, int seed);
int show_complex_double_matrix(lapack_complex_double *matrix, int rows, int columns, char *matrix_name);
int show_complex_double_packed_matrix(lapack_complex_double *matrix, char uplo, int rows, int columns, char *matrix_name);
int pack_complex_double_matrix(lapack_complex_double **A, lapack_complex_double **AP, int rows, int columns, int n);
int packed_complex_double_fill(lapack_complex_double **matrix, int size, int seed);
int copy_complex_double_matrix(lapack_complex_double **dest, lapack_complex_double **source, int size);
void transpose_complex_double_general_matrix(lapack_complex_double **matrix, int rows, int columns);

#endif
