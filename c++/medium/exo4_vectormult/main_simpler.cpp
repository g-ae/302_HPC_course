#include <iostream>
#include <chrono>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    std::srand(42);

    if (argc != 2) {
        cerr << "Incorrect number of parameters" << endl << "\tUsage: ./run 1000" << endl;
        return 1;
    }
    try {
        auto t = stoi(argv[1]);
    } catch (int e) {
        cerr << "First parameter must be an integer." << endl << "\tUsage: ./run 1000" << endl;
        return 1;
    }
    int array_size = stoi(argv[1]);


    long int scalaire = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (long int i = 0; i < array_size; i++) {
        scalaire += (std::rand() % 10) * (std::rand() % 10);
    }

    auto final = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(final - start);
    
    cout << "Result : " << scalaire << endl;
    cout << "Executed in " << duration.count() << "ms" << endl;

    return 0;
}