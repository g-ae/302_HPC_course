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

    int root_rank = 0;
    string line;
    char* buffer = nullptr;
    int len;
    
    if (rank == root_rank) {
        cout << "Number of processors: " << nproc << endl;
        std::ifstream file("data.txt");
        
        if (!file.is_open()) print_error("Could not open file data.txt.");
        
        if (!std::getline(file, line)) print_error("File doesn't have a single line.");
        
        len = line.size();
    }
    
    MPI_Bcast(&len, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
    buffer = new char[len]{};
    
    if (rank == root_rank) {
        for(int i = 0; i < line.size(); i++) {
            buffer[i] = line[i];
        }
    }
    MPI_Bcast(buffer, len, MPI_CHAR, root_rank, MPI_COMM_WORLD);
    cout << "Processor " << rank << " received: " << string(buffer) << endl;

    MPI_Finalize();
    return 0;
}