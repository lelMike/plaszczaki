#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

//Function to create the "bad character" table
void preprocessBadCharacter(const std::string &pattern, std::unordered_map<char, int> &badChar) {
    int m = pattern.length();
    for (int i = 0; i < m; i++) {
        badChar[pattern[i]] = i; \\
    }
}

//function to create the "good suffix" table
void preprocessGoodSuffix(const std::string &pattern, std::vector<int> &suffix, std::vector<int> &shift) {
    int m = pattern.length();
    int j = m;
    int k = m + 1;

    suffix[j] = k;

    while (j > 0) {
        while (k <= m && pattern[j - 1] != pattern[k - 1]) {
            if (shift[k] == 0) {
                shift[k] = k - j; //setting the shift value if not already set
            }
            k = suffix[k]; 
        }
        j--;
        k--;
        suffix[j] = k; //sufix
    }

    k = suffix[0];
    for (j = 0; j <= m; j++) {
        if (shift[j] == 0) {
            shift[j] = k; 
        }
        if (j == k) {
            k = suffix[k]; 
        }
    }
}

//Boyer-Moore search function
std::vector<int> BoyerMooreSearch(const std::string &text, const std::string &pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> result;

    if (m == 0 || n == 0 || m > n) {
        return result; // Return an empty result if the pattern is longer than the text or either is empty
    }

    //creating the "bad character" and "good suffix" tables
    std::unordered_map<char, int> badChar;
    std::vector<int> suffix(m + 1, 0);
    std::vector<int> shift(m + 1, 0);

    preprocessBadCharacter(pattern, badChar);
    preprocessGoodSuffix(pattern, suffix, shift);

    int s = 0; //s is the shift of the pattern with respect to text
    while (s <= n - m) {
        int j = m - 1;

        //comparing textes
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            result.push_back(s); 
            s += shift[0]; 
        } else {
           
            int badCharShift = (badChar.find(text[s + j]) != badChar.end()) ? std::max(1, j - badChar[text[s + j]]) : j + 1;
            s += std::max(badCharShift, shift[j + 1]);
        }
    }

    return result; //returning the positions where the pattern was found
}

std::string readTextFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(1);
    }
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return text;
}

int main() {
    std::string text = readTextFromFile("text.txt");

    std::string pattern = readTextFromFile("pattern.txt");

    //searching for the pattern in the text using the Boyer-Moore algorithm
    std::vector<int> positions = BoyerMooreSearch(text, pattern);

    std::cout << "Pattern found at positions: ";
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    std::cout << std::endl;

    return 0;
}
