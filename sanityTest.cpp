#include "lzw.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main() {
    std::string path = "sanityTests/";

    int test_count = 0;
    for (const auto &entry : fs::directory_iterator(path)) {
        test_count++;
    }
    test_count /= 2;

    for (int i = 1; i <= test_count; i++) {
        ifstream input(path+to_string(i)+".in");
        ifstream answer(path+to_string(i)+".ans");

        string operation;
        getline(input, operation);

        string data, curr;
        vector<int> compressed_data;
        if (operation == "compress") {
            while (getline(input, curr) && curr != "") {
                data += curr+'\n';
            }

            if (data != "") {
                compressed_data = compress(data);
            }

            vector<int> answer_compressed_data;
            while (true) {
                int code;
                answer >> code;
                if (answer.eof()) {
                    break;
                }
                answer_compressed_data.push_back(code);
            }

            if (compressed_data == answer_compressed_data) {
                cout << "test no. " << i << ": OK\n";
            } else {
                cout << "test no. " << i << ": WA\n";
            }
        } else if (operation == "decompress") {
            while (true) {
                int code;
                input >> code;
                if (input.eof()) {
                    break;
                }
                compressed_data.push_back(code);
            }

            if (compressed_data.size()) {
                data = decompress(compressed_data);
            }

            string answer_data;
            while (getline(answer, curr)) {
                answer_data += curr+'\n';
            }

            if (data == answer_data) {
                cout << "test no. " << i << ": OK\n";
            } else {
                cout << "test no. " << i << ": WA\n";
            }
        }
    }
}