#include <iostream>
#include <chrono>
#include <numeric>
#include <vector>

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

    cout << "Filling array with " << array_size << " random elements." << endl;

    vector<int> vec1(array_size);
    vector<int> vec2(array_size);

    for (int i = 0; i < array_size; i++) {
        
        vec1[i] = std::rand() % 10;
        vec2[i] = std::rand() % 10;
        // cout << vec1[i] << " // " << vec2[i] << endl;
    }

    cout << "Calculating scalar" << endl;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < array_size; i++) {
        vec1[i] *= vec2[i];
    }

    long int scalaire = 0;
    // ou boucle for qui ajoute tout à une variable total
    for(auto& num : vec1)
        scalaire += num;

    auto final = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(final - start);
    
    cout << "Result : " << scalaire << endl;
    cout << "Executed in " << duration.count() << "ms" << endl;

    return 0;
} 