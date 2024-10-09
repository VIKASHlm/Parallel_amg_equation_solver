#include "amg_solver.h"
#include <iostream>

int main() {
    int n = 4; // Matrix size (small example)

    // Example matrix A (4x4) and vectors b and x
    double A[] = { 4, 1, 2, 0,
                   1, 3, 0, 1,
                   2, 0, 4, 1,
                   0, 1, 1, 3 };

    double b[] = { 1, 2, 3, 4 };
    double x[] = { 0, 0, 0, 0 }; // Initial guess

    std::cout << "Solving Ax = b using serial AMG solver." << std::endl;
    AMG_solver(A, x, b, n);

    std::cout << "Solution x: ";
    for (int i = 0; i < n; ++i) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
