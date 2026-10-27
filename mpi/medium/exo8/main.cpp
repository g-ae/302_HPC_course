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

    string scaling = argv[1];
    int array_size;

    // Gestion d'erreurs
    if (argc != 3) return print_error(root_rank == rank ? "Incorrect number of parameters\n\tUsage: ./run 1000" : "");
    try {
        array_size = stoi(argv[2]);

        // weak scaling means that array_size is per proc
        if (scaling == "weak") array_size *= nproc;
    } catch (int e) {
        return print_error(root_rank == rank ? "First parameter must be an integer.\n\tUsage: ./run 1000" : "");
    }
    if (scaling != "weak" && scaling != "strong") return print_error(rank == root_rank ? "First parameter must either be 'weak' or 'strong'" : "");
    if (scaling == "strong" && array_size % nproc != 0) return print_error(root_rank == rank ? "Array size must be multiple of " + nproc : "");

    // 
    int chunk_size = array_size / nproc;
    int* chunk1 = new int[chunk_size];
    int* chunk2 = new int[chunk_size];
    int* vec1 = nullptr;
    int* vec2 = nullptr;
    
    if (rank == root_rank) {
        
        cout << "Filling array with " << array_size << " random elements." << endl;
        
        vec1 = new int[array_size];
        vec2 = new int[array_size];
        
        for (int i = 0; i < array_size; i++) {
            vec1[i] = std::rand() % 10;
            vec2[i] = std::rand() % 10;
        }
    }
    MPI_Scatter(vec1, chunk_size, MPI_INT, chunk1, chunk_size, MPI_INT, root_rank, MPI_COMM_WORLD);
    MPI_Scatter(vec2, chunk_size, MPI_INT, chunk2, chunk_size, MPI_INT, root_rank, MPI_COMM_WORLD);
    
    // lancement du chrono avant de commencer le calcul
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == root_rank) cout << "Starting compute" << endl;
    auto start = MPI_Wtime();

    long int scalaire = 0;

    for (int i = 0; i < chunk_size; i++) {
        scalaire += chunk1[i] * chunk2[i];
    }

    long int reduce_sum;
    auto duration = (MPI_Wtime() - start) * 1000;   // en ms
    MPI_Reduce(&scalaire, &reduce_sum, 1, MPI_LONG, MPI_SUM, root_rank, MPI_COMM_WORLD);
    double biggest_time;
    MPI_Reduce(&duration, &biggest_time, 1, MPI_DOUBLE, MPI_MAX, root_rank, MPI_COMM_WORLD);


    if (rank == root_rank) {
        cout << "Vector size: " << array_size << ", scaling: " << scaling << endl;
        cout << "Time for nproc=" << nproc << " : " << biggest_time << "ms" << endl;
        cout << "With result = " << reduce_sum << endl;
    }

    delete[] chunk1;
    delete[] chunk2;
    delete[] vec1;
    delete[] vec2;
    MPI_Finalize();
    return 0;
}