#include <iostream>
#include <fstream>
#include <mpi.h>
#include <cmath>

using namespace std;

int print_error(string error, int return_code=1) {
    cerr << error << endl;
    MPI_Abort(MPI_COMM_WORLD, 1);
    return return_code;
}

int main(int argc, char* argv[]) {
    int rank, nproc;
    int n, tag, num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    std::srand(42 + rank);

    int root_rank = 0;
    int* nums = new int[1000000]{};

    // Initialisation des colonnes
    for (int i = 0; i < 1000000; i++) {
        nums[i] = std::rand();
    }

    // Trouver maximum
    int max_id = 0;
    int max_num = nums[0];

    for (int i = 1; i < 1000000; i++) {
        if (nums[i] > max_num) {
            max_id = i;
            max_num = nums[i];
        }
    }

    int* maximums;

    if (rank == root_rank)
        maximums = new int[nproc];

    MPI_Gather(&max_num, 1, MPI_INT, maximums, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
    
    if (rank == root_rank) {
        for (int i = 0; i < nproc; i++) {
            cout << "Rank: " << i << ", maximum is:\t" << maximums[i] << endl;
        }
    }
    
    MPI_Finalize();
    return 0;
}