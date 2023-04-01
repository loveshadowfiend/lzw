#pragma once
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

vector<int> compress(const string& input) {
    unordered_map<string, int> dictionary;
    for (int i = 0; i < 256; i++) {
        string ch(1, (char)i);
        dictionary[ch] = i;
    }

    string p = "";
    vector<int> output;
    for (char c : input) {
        string pc = p + c;
        if (dictionary.count(pc)) {
            p = pc;
        } else {
            output.push_back(dictionary[p]);
            dictionary[pc] = dictionary.size();
            p = string(1, c);
        }
    }
    output.push_back(dictionary[p]);
    return output;
}

string decompress(const vector<int>& compressed) {
    unordered_map<int, string> dictionary;
    for (int i = 0; i < 256; i++) {
        string ch(1, (char)i);
        dictionary[i] = ch;
    }

    string output = "";
    string w(1, (char)compressed[0]);
    output += w;
    for (int i = 1; i < compressed.size(); i++) {
        int k = compressed[i];
        string entry;
        if (dictionary.count(k)) {
            entry = dictionary[k];
        } else if (k == dictionary.size()) {
            entry = w + w[0];
        } else {
            throw "bad compressed";
        }

        output += entry;
        dictionary[dictionary.size()] = w + entry[0];
        w = entry;
    }

    return output;
}