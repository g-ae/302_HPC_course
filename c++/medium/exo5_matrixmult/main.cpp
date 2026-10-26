#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    std::srand(42);

    if (argc != 2) {
        cout << "Incorrect number of parameters" << endl << "\tUsage : ./run 1000" << endl;
    }
    try {
        auto t = stoi(argv[1]);
    } catch (int e) {
        cerr << "First parameter must be an integer." << endl << "\tUsage: ./run 1000" << endl;
        return 1;
    }
    int array_size = stoi(argv[1]);

    cout << "Filling matrices with random elements." << endl;

    vector<int> mat1(array_size * array_size);
    vector<int> mat2(array_size * array_size);

    for (int i = 0; i < array_size * array_size; i++) {
        mat1[i] = std::rand() % 10;
        mat2[i] = std::rand() % 10;
    }

    cout << "Calculating product of " << array_size << " sized matrices" << endl;

    vector<int> result(array_size * array_size);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < array_size; i++) {
        for (int j = 0; j < array_size; j++) {
            int local_result = 0;
            for (int k = 0; k < array_size; k++) {
                local_result += mat1[i * array_size + j + k] * mat2[(i + k) * array_size + j];
            }
            result[i * array_size + j] = local_result;
        }
    }

    auto final = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(final - start);
    cout << "[array_size = " << array_size << "] Executed in " << duration.count() << "ms" << endl;
}