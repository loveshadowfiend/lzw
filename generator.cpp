#include "lzw.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

using namespace std;

string chars{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?"};
random_device rd;
mt19937 generator(rd());

string rand_str(int length) {
    string output;
    output.reserve(length);

    while (length > 0) {
        auto randNumb = generator();
        while (randNumb > 93 && length--) {
            output.push_back(chars[randNumb % 93]);
            randNumb /= 93;
        }
    }

    return output;
}

int main() {    
    string operation;
    cout << "compress/decompress: ";
    cin >> operation;
    if (operation != "compress" && operation != "decompress") {
        cout << "wrong input\n";
        return 0;
    }

    string path = "performanceTests/"+rand_str(8);
    ofstream output(path);
    output << operation << endl;

    int n;
    cout << "enter the length of the string: ";
    cin >> n;
    string rand_string = rand_str(n);

    if (operation == "compress") {
        output << rand_string << endl;
    } else {
        vector<int> compressed_data = compress(rand_string);

        for (auto i : compressed_data) {
            output << i << ' ';
        }
    }
}