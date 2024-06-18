//Natan Warelich
#include <iostream>
#include "../include/KMP.h"
#include "../include/huffman.h"
#include "../include/filtering.h"
#include <vector>
#include <fstream>
#include <string>

void checkingFile(std::ifstream &file, std::string name){
    if(!file.is_open()){
        std::cerr << "Unable to open " << name << std::endl;
        exit(-1);
    }

    //tellg i seekg to ai
    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
        std::cerr << "The file " << name << " is empty." << std::endl;
        exit(-1);
    }
    file.seekg(0, std::ios::beg);
}
int main(int argc, char* argv[]) {
    if(argc != 3){
        std::cerr << "Usage: .\\problem2.exe [song file] [word file]" << std::endl;
        exit(-1);
    }

    Filtering filtering = *new Filtering();
    std::ifstream songfile("txt/" + std::string(argv[1]));
    checkingFile(songfile,  "songfile");

    std::string line;
    std::string song = Filtering::songfiletostring(songfile);
    songfile.close();

    std::ifstream wordfile("txt/" + std::string(argv[2]));
    checkingFile(wordfile, "wordfile");
    //--------------KMP---------------------------------
    int n = 0;
    std::vector<std::pair<std::string, std::string>> words = Filtering::wordsFileToString(wordfile, n);
    KMP kmp = *new KMP();
    int i;
    Filtering::sortByLength(words);

    kmp.pattern(song, "poli", "boli");

    for(i = 0; i < n; i++){
        kmp.pattern(song, words[i].first, words[i].second);
    }

    Filtering::sortByReplacement(words);
    for(i = 0; i < n; i++){
        kmp.pattern(song, words[i].first, words[i].second);
    }

    Filtering::sortByReplacement2(words);
    for(i = 0; i < n; i++){
        kmp.pattern(song, words[i].first, words[i].second);
    }
    wordfile.close();
    //---------------------huffman---------------------
    Huffman huffman = *new Huffman();
    std::map<char, std::string> codes;
    std::string empty;
    Node* node = huffman.creatingTree(song);
    huffman.prepareForEncryption(node, empty, codes);

    for(auto& a : codes){
        std::cout << a.first << ": " << a.second << std::endl;
    }


    std::string compressedSong = huffman.compression(codes, song);

    //--------------------------Reszta---------------------
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
             const std::string& copy = compressedSong;
             std::cout << huffman.decompression(node, copy) << std::endl;

        }
        if(decision == 3){
            filtering.saveTheSong(compressedSong);
            break;
        }

    }
    huffman.savememoryforlater(node); //zwolnienie pamięci
    return 0;
}
