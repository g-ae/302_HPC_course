#include <iostream>
#include <chrono>
using namespace std;

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    cout << "Hello World!" << endl;

    auto final = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(final - start);
    
    cout << "Executed in " << duration.count() << "μs" << endl;
    return 0;
} 