//Natan Warelich
#ifndef PASZCZAKI_KMP_H
#define PASZCZAKI_KMP_H
#endif //PASZCZAKI_KMP_H


#include <iostream>
#include <vector>
#include <map>
#include <string>

class KMP {
    // znajdywanie wzorca
private: std::vector<int> CPF(const std::string &word) {
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

int errorChecking(std::string &text, std::string &pattern, const std::string &fixedword){
    if(text == pattern){
        std::cout << "text is equal to pattern, replacing now" << std::endl;
        text.replace(0, text.length(), fixedword);
        return 1;
    }
    if(pattern.length() > text.length()){
        std::cerr << "pattern is longer than text" << std::endl;
        return 2;
    }
    if(pattern == fixedword){
        std::cout << "there is no point of replacing pattern with new word since they are the same" << std::endl;
    }
    return 0;

}
public:
    void pattern(std::string &text, std::string pattern, const std::string &fixedword) {
        if (errorChecking(text, pattern, fixedword) == 0) {

            bool found = false;
            int n = text.length();
            int m = pattern.length();
            std::vector<int> pi = CPF(pattern);
            int q = 0;

            /*ta pętla jest stosunkowo prosta:
            * szukamy sytuacji w której znak z patternu pasuje do tekstu
            * potem sprawdzamy czy znaleźliśmy to czego szukamy,
            * następnie wchodzimy do while i tam jeżeli znak nie pasuje to dajemy q wartość tablicy prefixów:
            * q = pi[q] aby wiedzieć o ile mamy przeskoczyć sprawdzanie
            * */

            for (int i = 0; i < n; i++) {
                while (q > 0 && pattern[q] != text[i]) {
                    q = pi[q];
                }
                if (pattern[q] == text[i]) {
                    q++;
                }
                if (q == m) {
                    text.replace(i - m + 1, m, fixedword);
                    //std::cout << text << std::endl;
                    found = true;
                    q = pi[q];
                }

            }
            if (!found)
                std::cout << "wzorzec: " << pattern << " nie wystepuje" << std::endl;
        }
    }

};