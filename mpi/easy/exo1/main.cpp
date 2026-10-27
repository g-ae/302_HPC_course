#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
    int menum, nproc;
    int n, tag, num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &menum);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    if (menum == 0) {
        cout << "Number of processors: " << nproc << endl;
    }

    int error_value = MPI_Barrier(MPI_COMM_WORLD);

    if (error_value && menum == 0) {
        cout << "Error:" << error_value << endl;
    }

    cout << "Processor " << menum << " - Hello world" << endl;

    MPI_Finalize();
    return 0;
}