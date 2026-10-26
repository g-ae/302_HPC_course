#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <cmath>

using namespace std;

bool ends_with(const string& s, const string& suffix) {
    return s.size() >= suffix.size() &&
           s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

int main(int argc, char* argv[]) {
    string path = "Pictures/";

    auto start = std::chrono::high_resolution_clock::now();

    // https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        string path_string = entry.path().string();
        if (!ends_with(path_string, "_RGB.txt"))
            continue;

        std::ifstream file(path_string);
        
        if (!file.is_open()) {
            cerr << "Could not open file " << path_string << "." << endl;
            continue;
        }

        string file_text;
        int file_size = 0;
        long int r = 0;
        long int g = 0;
        long int b = 0;


        for (int i = 0; i < 15; i++) {
            if (!std::getline(file, file_text)) {
                break;
            }
            file_size += 1;

            stringstream ss(file_text);

            string token;

            int j = 0;

            while (std::getline(ss, token, ',')) {
                if (j == 0) r += stoi(token);
                if (j == 1) g += stoi(token);
                if (j == 2) b += stoi(token);

                j += 1;
            }
        }

        g = round(g / file_size);
        r = round(r / file_size);
        b = round(b / file_size);

        cout << "Moyenne pour fichier " << path_string << ": r=" << r << ", g=" << g << ", b=" << b << endl; 
    }

    auto final = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(final - start);
    cout << "Executed in " << duration.count() << "ms" << endl;
}