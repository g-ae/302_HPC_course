#include <iostream>
#include <fstream>
#include <mpi.h>
#include <cmath>
#include <chrono>

using namespace std;

int print_error(string error, int return_code=1) {
    if (error != ""){
        cerr << error << endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    return return_code;
}

int main(int argc, char* argv[]) {
    int rank, nproc;
    int n, tag, num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    std::srand(42);

    int root_rank = 0;

    int array_size;

    if (argc != 2) return print_error(root_rank == rank ? "Incorrect number of parameters\n\tUsage: ./run 1000" : "");
    try {
        array_size = stoi(argv[1]);
    } catch (int e) {
        return print_error(root_rank == rank ? "First parameter must be an integer.\n\tUsage: ./run 1000" : "");
    }

    if (array_size % nproc != 0) return print_error(root_rank == rank ? "Array size must be multiple of " + nproc : "");
    int chunk_size = array_size / nproc;
    int* chunk1 = new int[chunk_size]{};
    int* chunk2 = new int[chunk_size]{};
    
    if (rank == root_rank) {
        
        cout << "Filling array with " << array_size << " random elements." << endl;
        
        int* vec1 = new int[array_size]{};
        int* vec2 = new int[array_size]{};
        
        for (int i = 0; i < array_size; i++) {
            vec1[i] = std::rand() % 10;
            vec2[i] = std::rand() % 10;
        }
        MPI_Scatter(vec1, chunk_size, MPI_INT, chunk1, chunk_size, MPI_INT, root_rank, MPI_COMM_WORLD);
        MPI_Scatter(vec2, chunk_size, MPI_INT, chunk2, chunk_size, MPI_INT, root_rank, MPI_COMM_WORLD);
        delete[] vec1;
        delete[] vec2;
    } else {
        MPI_Scatter(NULL, chunk_size, MPI_INT, chunk1, chunk_size, MPI_INT, root_rank, MPI_COMM_WORLD);
        MPI_Scatter(NULL, chunk_size, MPI_INT, chunk2, chunk_size, MPI_INT, root_rank, MPI_COMM_WORLD);
    }

    // lancement du chrono avant de commencer le calcul
    MPI_Barrier(MPI_COMM_WORLD);
    auto start = std::chrono::high_resolution_clock::now();

    long int scalaire = 0;

    for (int i = 0; i < chunk_size; i++) {
        scalaire += chunk1[i] * chunk2[i];
    }

    long int reduce_sum;
    MPI_Reduce(&scalaire, &reduce_sum, 1, MPI_LONG, MPI_SUM, root_rank, MPI_COMM_WORLD);

    auto final = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(final - start);
    
    if (rank == root_rank) {
        cout << "Time for nproc=" << nproc << " : " << duration.count() << "ms." << endl;
        cout << "With result = " << reduce_sum << endl;
    }

    delete[] chunk1;
    delete[] chunk2;
    MPI_Finalize();
    return 0;
}