cmake_minimum_required(VERSION 3.10)
project(AMGSolver)

# Enable C++11 standard
set(CMAKE_CXX_STANDARD 11)

# Find MPI
find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)

# Add the serial solver executable
add_executable(AMGSolverSerial amg_solver_serial.cpp amg_solver.cpp)

# Add the parallel solver executable
add_executable(AMGSolverParallel amg_solver_parallel.cpp amg_solver.cpp)

# Link MPI and OpenMP to the parallel solver
target_link_libraries(AMGSolverParallel MPI::MPI_C OpenMP::OpenMP_CXX)
