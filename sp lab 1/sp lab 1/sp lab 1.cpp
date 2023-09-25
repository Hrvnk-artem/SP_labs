#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cctype> 

using namespace std;

const int MAX_WORD_LENGTH = 30;

int main() {
    ifstream file("E:\\uni projects\\labs\\sp lab 1\\text.txt");
    if (!file.is_open()) {
        cerr << "The file wasn't open" << endl;
        return 1;
    }

    unordered_map<string, int> wordCount;

    string word;
    while (file >> word) {
        for (char& c : word) {
            c = tolower(c);
        }

        bool isWord = true;
        for (char c : word) {
            if (!isalpha(c)) {
                isWord = false;
                break;
            }
        }

        if (isWord) {
            if (wordCount.find(word) != wordCount.end()) {
                wordCount[word]++;
            }
            else {
                wordCount[word] = 1;
            }
        }
    }

    file.close();

    for (const auto& entry : wordCount) {
        if (entry.second >= 2) { 
            cout << entry.first << ": " << entry.second << endl;
        }
    }

    return 0;
}
