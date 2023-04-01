#include "lzw.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main() {
    std::string path = "performanceTests/";

    for (const auto &entry : fs::directory_iterator(path)) {
        ifstream input(entry.path());

        string operation;
        getline(input, operation);
        
        if (operation == "compress") {
            string data;
            getline(input, data);
            auto start = std::chrono::high_resolution_clock::now();
            compress(data);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

            cout << "type: " << operation << endl;
            cout << "total chars: " << data.length() << endl;
            cout << "elapsed time: " << (double)duration.count() << " ms." << endl << "-----------------------\n";
        } else {
            vector<int> data;

            int code_count = 0;
            while (true) {
                int code;
                input >> code;
                if (input.eof()) {
                    break;
                }
                code_count++;
                data.push_back(code);
            }

            auto start = std::chrono::high_resolution_clock::now();
            decompress(data);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

            cout << "type: " << operation << endl;
            cout << "total codes: " << code_count << endl;
            cout << "elapsed time: " << (double)duration.count() << " ms." << endl << "-----------------------\n";
        }
    }
}