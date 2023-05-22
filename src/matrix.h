#ifndef AJMATRIX_H
#define AJMATRIX_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_size_t.h>

typedef struct Matrix Matrix;

struct Matrix {
  size_t nrows;
  size_t ncols;
  float *data;
};

float Vector_DotProduct(float *, float *, size_t);
Matrix Matrix_Alloc(size_t, size_t);
void Matrix_Init(Matrix *, float *);
Matrix Matrix_New(size_t, size_t, float *);
bool Matrix_CheckExact(Matrix *);
bool Matrix_IsValid(Matrix *);
float *Matrix_At(Matrix *, size_t, size_t);
float *Matrix_Row(Matrix *, size_t);
float *Matrix_Col(Matrix *, size_t);
Matrix Matrix_RowAsMatrix(Matrix *, size_t);
Matrix Matrix_ColAsMatrix(Matrix *, size_t);
int Matrix_Print(Matrix *);
Matrix Matrix_Dot(Matrix *, Matrix *);

#ifdef AJMATRIX_IMPLEMENTATION
#define MALLOC malloc

float Vector_DotProduct(float *v1, float *v2, size_t length) {
  assert(v1 != NULL && v2 != NULL);
  float result = 0.f;
  for (size_t i = 0; i < length; ++i) {
    result = result + v1[i] * v2[i];
  }
  return result;
}

Matrix Matrix_Alloc(size_t _rows, size_t _cols) {
  assert(_rows > 0 && _cols > 0);
  float *new_mem = (float *)MALLOC(sizeof(float) * (_rows * _cols));
  Matrix result = {.nrows = _rows, .ncols = _cols, .data = new_mem};
  return result;
}

void Matrix_Init(Matrix *mat, float *_data) { mat->data = _data; }

Matrix Matrix_New(size_t ROWS, size_t COLS, float *DATA) {
  Matrix result = Matrix_Alloc(ROWS, COLS);
  Matrix_Init(&result, DATA);
  return result;
}

bool Matrix_CheckExact(Matrix *m) {
  if (m == NULL)
    return false;
  return true;
}

bool Matrix_IsValid(Matrix *m) {
  if (Matrix_CheckExact(m))

  {
    if (m->data != NULL && m->ncols > 0 && m->nrows > 0)
      return true;
  }
  return false;
}

float *Matrix_At(Matrix *m, size_t _row, size_t _col) {
  return &(m->data[(m->ncols) * _row + _col]);
}

float *Matrix_Row(Matrix *m, size_t nth_row) {
  size_t length = m->ncols;
  float *result = MALLOC(sizeof(*result) * length);
  for (size_t i = 0; i < length; ++i) {
    result[i] = *Matrix_At(m, nth_row, i);
  }
  return result;
}

Matrix Matrix_RowAsMatrix(Matrix *m, size_t nth_row) {
  float *data = Matrix_Row(m, nth_row);
  Matrix result;
  result.ncols = m->ncols;
  result.nrows = 1;
  result.data = data;
  return result;
}

float *Matrix_Col(Matrix *m, size_t nth_col) {
  size_t length = m->nrows;
  float *result = MALLOC(sizeof(*result) * length);
  for (size_t i = 0; i < length; ++i) {
    result[i] = *Matrix_At(m, i, nth_col);
  }
  return result;
}

Matrix Matrix_ColAsMatrix(Matrix *m, size_t nth_col) {
  float *data = Matrix_Col(m, nth_col);
  Matrix result;
  result.ncols = 1;
  result.nrows = m->nrows;
  result.data = data;
  return result;
}

int Matrix_Print(Matrix *m) {
  printf("Matrix (%zux%zu) {\n", m->nrows, m->ncols);
  for (size_t nth_row = 0; nth_row < m->nrows; ++nth_row) {
    printf("\t");
    for (size_t nth_col = 0; nth_col < m->ncols; ++nth_col) {
      printf("%f ", *Matrix_At(m, nth_row, nth_col));
    }
    printf("\n");
  }
  puts("}");
  return 0;
}

Matrix Matrix_Dot(Matrix *m1, Matrix *m2) {
  assert(Matrix_IsValid(m1) && Matrix_IsValid(m2));
  assert(m1->ncols == m2->nrows);
  Matrix result = Matrix_Alloc(m1->nrows, m2->ncols);
  for (size_t nth_row = 0; nth_row < result.nrows; ++nth_row) {
    for (size_t nth_col = 0; nth_col < result.ncols; ++nth_col) {
      for (size_t it = 0; it < m1->ncols; ++it) {
		  *Matrix_At(&result, nth_row, nth_col) = Vector_DotProduct(Matrix_Row(m1, nth_row), Matrix_Col(m2, nth_col), m1->ncols);
      }
    }
  }
  return result;
}
#endif

#endif // AJMATRIX_H
