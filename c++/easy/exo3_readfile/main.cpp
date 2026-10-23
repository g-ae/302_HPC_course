#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

void print_execution_time(std::chrono::_V2::system_clock::time_point start) {
    cout << "Executed in " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << "ms" << endl;
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    if (argc == 1) {
        cerr << "You must provide a file." << endl << "\tUsage: ./run big_text.txt" << endl;
        return 1;
    }
    if (argc > 2) {
        cout << "[WARNING] Too many arguments, only the first one will be used : " << argv[1] << endl;
    }
    auto path = argv[1];


    std::ifstream file(path);

    if (!file.is_open()) {
        cerr << "Could not open file." << endl;

        print_execution_time(start);
        return 1;
    }

    string file_text;

    for (int i = 0; i < 15; i++) {
        if (!std::getline(file, file_text)) {
            break;
        }
        cout << "[" << (i+1) << "]\t" << file_text << endl;
    }

    file.close();

    print_execution_time(start);
    return 0;
}