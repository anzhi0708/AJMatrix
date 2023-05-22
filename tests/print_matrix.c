#define AJMATRIX_IMPLEMENTATION
#include "../src/matrix.h"
#include <assert.h>


int main() {

	size_t N_ROWS = 3;
	size_t N_COLS = 4;
	float data[] = {
		1.f, 2.f, 3.f, 5.f,
		2.f, 7.f, 6.f, 4.f,
		1.f, 8.f, 10.f, 9.f
	};
	Matrix m1 = Matrix_New(N_ROWS, N_COLS, data);
	Matrix m2 = Matrix_New(N_COLS, N_ROWS, data);
	assert(Matrix_IsValid(&m1));
	Matrix_Print(&m1);
	Matrix_Print(&m2);
	Matrix m3 = Matrix_Dot(&m1, &m2);
	Matrix_Print(&m3);
	puts("");
	puts("\n-----\nMatrix 1, Row 2:");
	Matrix v1 = Matrix_RowAsMatrix(&m1, 2);
	Matrix_Print(&v1);
	puts("\n----\nMatrix 2, Col 2:");
	Matrix v2 = Matrix_ColAsMatrix(&m2, 2);
	Matrix_Print(&v2);
	puts("\n----\nMatrix 3, Col 2:");
	Matrix v3 = Matrix_ColAsMatrix(&m3, 2);
	Matrix_Print(&v3);
	return 0;
}
