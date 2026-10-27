#include <iostream>
#include <mpi.h>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    int rank, nproc;
    int n, tag, num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    int root_rank = 0;
    long int array_size = std::pow(nproc, 4);
    int chunk_size = array_size / nproc;
    int* chunk = new int[chunk_size];

    if (rank == root_rank) {
        cout << "Number of processors: " << nproc << endl;
        cout << "Création du tableau d'entiers aléatoires." << endl;
        int* data = new int[array_size]{};  // tableau vide de taille divisible par nproc
        
        std::srand(42);
        for (int i = 0; i < array_size; i++) {
            data[i] = std::rand() % 100;
        }

        MPI_Scatter(data, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, root_rank, MPI_COMM_WORLD);
    } else {
        MPI_Scatter(NULL, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, root_rank, MPI_COMM_WORLD);
    }
    
    long int total = 0;

    for (int i = 0; i < chunk_size; i++) total += chunk[i];

    cout << "Process " << rank << " value = " << total << endl;

    long int reduce_sum;
    MPI_Reduce(&total, &reduce_sum, 1, MPI_LONG, MPI_SUM, root_rank, MPI_COMM_WORLD);

    long int allreduce_sum;
    MPI_Allreduce(&total, &allreduce_sum, 1, MPI_LONG, MPI_SUM, MPI_COMM_WORLD);

    if (rank == root_rank) {
        cout << "Reduce sum : " << reduce_sum << endl;
        cout << "Allreduce sum : " << allreduce_sum << endl;
    }

    MPI_Finalize();
    return 0;
}