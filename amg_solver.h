#ifndef AMG_SOLVER_H
#define AMG_SOLVER_H

// Function declarations
void matvec(double* A, double* x, double* y, int n);
void relax(double* A, double* x, double* b, int n, int iterations);
void compute_residual(double* A, double* x, double* b, double* r, int n);
void restriction(double* fine_res, double* coarse_res, int fine_size, int coarse_size);
void interpolation(double* coarse_correction, double* fine_correction, int coarse_size, int fine_size);
void AMG_solver(double* A, double* x, double* b, int n);

#endif // AMG_SOLVER_H
