//Natan Warelich
#ifndef PASZCZAKI_KMP_H
#define PASZCZAKI_KMP_H
#endif //PASZCZAKI_KMP_H


#include <iostream>
#include <vector>
#include <map>
#include <string>

std::vector<int> CPF(const std::string& word) {
    int m = word.length();
    std::vector<int> pi(m + 1);
    pi[1] = 0;
    int k = 0;

    for (int i = 2; i <= m; i++) {
        while (k > 0 && word[k] != word[i - 1]) {
            k = pi[k];
        }

        if (word[k] == word[i - 1]) {
            k++;
        }
        pi[i] = k;
    }
    return pi;
}

void KMP(std::string& text, std::string pattern, const std::string& fixedword){
    bool found = false;
    int n = text.length();
    int m = pattern.length();
    std::vector<int> pi = CPF(pattern);
    int q = 0;
    for(int i = 0; i < n; i++){
        while(q > 0 && pattern[q] != text[i]){
            q = pi[q];
        }
        if(pattern[q] == text[i]){
            q++;
        }
        if(q == m){
            text.replace(i -m + 1, m, fixedword);
            //std::cout << text << std::endl;
            found = true;
            q = pi[q];
        }

    }
    if(!found)
    std::cout << "wzorzec: " << pattern << " nie wystepuje" << std::endl;
}