#include <iostream>
#include <chrono>
#include <string> 
#include <fstream>
using namespace std;
using namespace std::chrono;

int main() {
    cout << "Donnez un nombre : ";
    int n;
    cin >> n;

    auto start_bn = high_resolution_clock::now();

    std::ofstream bn("output_backslash_n.txt");

    for (int i = 1; i <= 100000; i++) {
        bn << std::to_string(n * i) << "\n";
    }

    bn.close();

    auto final_bn = high_resolution_clock::now();
    auto duration_bn = duration_cast<milliseconds>(final_bn - start_bn);

    cout << "Test avec \\n :\t " << duration_bn.count() << "ms" << endl;
    

    auto start_endl = high_resolution_clock::now();
    std::ofstream out_endl("output_endl.txt");
    for (int i = 1; i <= 100000; i++) {
        out_endl << std::to_string(n * i) << endl;
    }
    out_endl.close();

    auto final_endl = high_resolution_clock::now();
    auto duration_endl = duration_cast<milliseconds>(final_endl - start_endl);

    cout << "Test avec endl : " << duration_endl.count() << "ms" << endl;

    return 0;
}