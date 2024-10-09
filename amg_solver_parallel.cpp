#include "amg_solver.h"
#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        std::cout << "Running parallel AMG solver with " << size << " MPI processes." << std::endl;
    }

    int n = 4; // Matrix size (small example)

    // Example matrix A (4x4) and vectors b and x
    double A[] = { 4, 1, 2, 0,
                   1, 3, 0, 1,
                   2, 0, 4, 1,
                   0, 1, 1, 3 };

    double b[] = { 1, 2, 3, 4 };
    double x[4] = { 0, 0, 0, 0 }; // Initial guess

    // Split workload across MPI processes
    int local_n = n / size; // Local size for each process
    std::vector<double> local_A(local_n * n);
    std::vector<double> local_x(local_n);
    std::vector<double> local_b(local_n);

    // Scatter data to all processes
    MPI_Scatter(A, local_n * n, MPI_DOUBLE, local_A.data(), local_n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, local_n, MPI_DOUBLE, local_b.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Call the AMG solver
    AMG_solver(local_A.data(), local_x.data(), local_b.data(), local_n);

    // Gather results from all processes
    MPI_Gather(local_x.data(), local_n, MPI_DOUBLE, x, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "Final solution x:" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << x[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize(); // Finalize the MPI environment
    return 0;
}
