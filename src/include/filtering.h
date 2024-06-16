//Natan Warelich
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#ifndef PASZCZAKI_FILTERING_H
#define PASZCZAKI_FILTERING_H

#endif //PASZCZAKI_FILTERING_H

class Filtering{
public:
     static std::string songfiletostring(std::ifstream& f){
        std::stringstream song;
        std::string line;
        while(std::getline(f,line)){
            song << line << "\n";
        }
        return song.str();
    }
    /*tutaj nastaje dylemat albowiem:
     * co jeśli bedziemy podstawiać za podsłowa naszych dodanych słów
     * czytaj zamieniamy rower na kajak, i potem kaj na raj
     * w przypadku odwrotnej kolejności nie będziemy mieli zamierzonego efektu
     * rozwiązanie na pierwszy rzut oka jest takie aby:
     *      posortować wielkościowo (zakładamy odważnie iż nasi trzeciowymiarowcy są zbyt leniwy aby zmieniać długości wyrazów)
     * jednakże to będzie dalej wywoływać konflikt w przypadku znaków tej samej długości
     * więc konkluzja moja jest następująca, aby mieć jeszcze tablicę posortowaną tak że:
     * a.first > a.second
     *
     * więc nasuwa się pytanie jak to zrobić?
     * przesortowanie tej samej tablicy dla paru przypadków
     * */
    static std::vector<std::pair<std::string, std::string>> wordsFileToString(std::ifstream& f, int& n){
        std::string word1, word2;
        std::vector<std::pair<std::string, std::string>> words;
        while(f >> word1 >> word2){
            words.emplace_back(word1, word2); //emplace_back zamiast push_back, ponieważ emplace unika zbędnego tworzenia nowych par
            n++;
        }
        return words;
    }

    //te dwa filtrujące ai
    static void sortByLength(std::vector<std::pair<std::string, std::string>>& words) {
        std::sort(words.begin(), words.end(), [](const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
            return a.first.length() > b.first.length();
        });
    }

    static void sortByReplacement(std::vector<std::pair<std::string, std::string>>& words) {
        std::sort(words.begin(), words.end(), [](const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
            return a.first > b.second;
        });
    }
    static void sortByReplacement2(std::vector<std::pair<std::string, std::string>>& words) {
        std::sort(words.begin(), words.end(), [](const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
            return a.first < b.second;
        });
    }

    static void saveTheSong(std::string result){
        std::ofstream finalFile("build/result.txt");
        if(!finalFile){
            std::cerr << "Unable to open finalFile" << std::endl;
        }
        else{
            finalFile << result;
            finalFile.close();
        }
    }


};