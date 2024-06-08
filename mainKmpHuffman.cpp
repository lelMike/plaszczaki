//Natan Warelich
#include <iostream>
#include "KMP.h"
#include "huffman.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>


std::string songfiletostring(std::ifstream& f){
    std::stringstream song;
    std::string line;
    while(std::getline(f,line)){
        song << line << "\n";
    }
    return song.str();
}

std::vector<std::pair<std::string, std::string>> wordsfiletostring(std::ifstream& f, int& n){
   std::string word1, word2;
   std::vector<std::pair<std::string, std::string>> words;
   while(f >> word1 >> word2){
       words.emplace_back(word1, word2); //emplace_back zamiast push_back, ponieważ emplace unika zbędnego tworzenia nowych par
       n++;
   }
   return words;
}

void saveTheSong(std::string result){
    std::ofstream finalFile("result.txt");
    if(!finalFile){
        std::cerr << "Unable to open finalFile" << std::endl;
    }
    else{
        finalFile << result;
        finalFile.close();
    }
}

int main() {
    std::ifstream songfile("song.txt");
    std::string line;

    if (!songfile.is_open()){
        std::cerr << "Unable to open songfile" << std::endl;
        return -1;
    }

    std::string song = songfiletostring(songfile);
    songfile.close();

    int n = 0;
    std::ifstream wordfile("words.txt");
    if(!wordfile.is_open()){
        std::cerr << "Unable to open wordfile" << std::endl;
        return -1;
    }
    std::vector<std::pair<std::string, std::string>> words = wordsfiletostring(wordfile, n);

    for(int i = 0; i < n; i++){
        KMP(song, words[i].first, words[i].second);
    }
    wordfile.close();
    //std::cout << song;

    std::map<char, std::string> codes;
    std::string empty;
    Node* node = creatingTree(song);
    prepareForEncryption(node, empty, codes);

    for(auto a : codes){
        std::cout << a.first << ": " << a.second << std::endl;
    }


    std::string compressedSong = compression(codes, song);


    std::cout << "Alright mr Heretic, we have sucessfully made compression, what do we do now?" << std::endl;
    while(true) {
        std::cout << "type \"1\" if you want to see what did you do." << std::endl;
        std::cout << "type \"2\" if you want to decrypt code." << std::endl;
        std::cout << "type \"3\" if you want to use 2d printer to save results. (it ends program and input results into file)" << std::endl;

        int decision;
        std::cin >> decision;
        if(decision == 1){
            std::cout << compressedSong << std::endl;
        }
        if(decision == 2){
                //tworzymy kopie gdyż będziemy pracować na referencji aby nie zuużywać, aż tyle zasobów, bo w końcu rekurencja i te sprawy
             std::string copy = compressedSong;
             std::cout << decompression(node, copy) << std::endl;

        }
        if(decision == 3){
            saveTheSong(compressedSong);
            break;
        }

    }
    savememoryforlater(node); //zwolnienie pamięci
    return 0;
}
