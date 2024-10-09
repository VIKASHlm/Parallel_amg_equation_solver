#include "amg_solver.h"
#include <vector>

void matvec(double* A, double* x, double* y, int n) {
    for (int i = 0; i < n; ++i) {
        y[i] = 0.0;
        for (int j = 0; j < n; ++j) {
            y[i] += A[i * n + j] * x[j];
        }
    }
}

void relax(double* A, double* x, double* b, int n, int iterations) {
    for (int iter = 0; iter < iterations; ++iter) {
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (i != j) sum += A[i * n + j] * x[j];
            }
            x[i] = (b[i] - sum) / A[i * n + i];
        }
    }
}

void compute_residual(double* A, double* x, double* b, double* r, int n) {
    std::vector<double> Ax(n);
    matvec(A, x, Ax.data(), n);
    for (int i = 0; i < n; ++i) {
        r[i] = b[i] - Ax[i];
    }
}

void restriction(double* fine_res, double* coarse_res, int fine_size, int coarse_size) {
    for (int i = 0; i < coarse_size; ++i) {
        coarse_res[i] = fine_res[2 * i]; // Simple restriction
    }
}

void interpolation(double* coarse_correction, double* fine_correction, int coarse_size, int fine_size) {
    for (int i = 0; i < fine_size; ++i) {
        fine_correction[i] = coarse_correction[i / 2]; // Simple interpolation
    }
}

void AMG_solver(double* A, double* x, double* b, int n) {
    std::vector<double> r(n);
    std::vector<double> coarse_corr(n / 2);
    std::vector<double> fine_corr(n);

    for (int iter = 0; iter < 10; ++iter) {
        relax(A, x, b, n, 3);
        compute_residual(A, x, b, r.data(), n);

        restriction(r.data(), coarse_corr.data(), n, n / 2);
        AMG_solver(A, coarse_corr.data(), coarse_corr.data(), n / 2);
        interpolation(coarse_corr.data(), fine_corr.data(), n / 2, n);

        for (int i = 0; i < n; ++i) {
            x[i] += fine_corr[i];
        }
    }
}
