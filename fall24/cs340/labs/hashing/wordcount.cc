#include "wordcount.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>

WordCount::WordCount(int sz) {
    tableSize = sz;
    hashTable.resize(sz);
}

int WordCount::hash(string s) {
    return hashFunction(s) % tableSize;
}

int WordCount::count(string word) {
    int key = hash(word);

    if (hashTable[key].size() != 0) {
        for (auto it = hashTable[key].begin(); it != hashTable[key].end(); ++it) {
            if (it->first == word) {
                return it->second;
            }
        }
    }

    return 0;
}

void WordCount::add(string word) {
    int key = hash(word);

    if (hashTable[key].size() == 0) {
        hashTable[key].push_back({word,1});
        return;
    }
    auto pos = std::find_if(hashTable[key].begin(), hashTable[key].end(), [&](const auto& a){
            return a.first == word;
        });
    if (pos == hashTable[key].end()) {
        hashTable[key].push_back({word,1});
    }
    else {
        pos->second++;
    }

}
        

void WordCount::print() {
    std::vector<std::pair<string, int>> words;
    for (auto entry: hashTable)
        for (auto pair: entry)
            words.push_back(pair);
    sort(words.begin(), words.end());
    for (auto pair: words)
        std::cout << pair.first << ": " << pair.second << std::endl;
}

void printFileWordCount(string filename, int tableSize) {
    WordCount T(tableSize);

    std::ifstream input_file(filename);

    std::string word;
    while (input_file >> word) {
        std::transform(word.begin(), word.end(), word.begin(), [](char &ch){
                        return std::tolower(ch);
                });
        word.erase(std::remove_if(word.begin(),word.end(), [](auto &ch) {
                        return std::ispunct(ch);
                    }),word.end());
        T.add(word);

    }
    T.print();

}








