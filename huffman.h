//Natan Warelich
#ifndef PASZCZAKI_HUFFMAN_H
#define PASZCZAKI_HUFFMAN_H

#endif //PASZCZAKI_HUFFMAN_H

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <functional>

struct Node{
    char letter;
    int value;
    Node* left;
    Node* right;
    std::string valueToGetTo; //to jest nasz bit
};

struct Node* newNode(int value, char letter)
{
    Node* n = new Node;
    n->value = value;
    n->letter = letter;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

void mapfill(std::vector<std::pair<char, int>>& w, std::string s){
    for(int i = 0; i < s.length(); i++){
        //ai

        auto it = std::find_if(w.begin(), w.end(), [&](const std::pair<char, int>& element) {
            return element.first == s[i];
        });
        //jedyny znak jaki nie chcemy to EOF, nawet nie wiem czy wystąpi, napisałem dla "bezpieczeństwa"
        if (it == w.end() && s[i] != EOF) {
            w.emplace_back(s[i], 1);
        } else {
            it->second++;
        }
    }
}

Node* creatingTree(const std::string& song) {
    std::vector<std::pair<char, int>> wordcount;
    mapfill(wordcount, song);

    auto compareNodes = [](Node* a, Node* b) {
        return a->value > b->value;
    };

    std::priority_queue<Node*, std::vector<Node*>, decltype(compareNodes)> queue(compareNodes);


    for (const auto& pair : wordcount) {
        queue.push(newNode(pair.second, pair.first));
    }


    while (queue.size() > 1) {
        Node* left = queue.top();
        queue.pop();
        Node* right = queue.top();
        queue.pop();

        left->valueToGetTo = '0';
        right->valueToGetTo = '1';
        Node* parent = newNode(left->value + right->value, '\0');
        parent->left = left;
        parent->right = right;


        queue.push(parent);
    }


    return queue.top();
}

void prepareForEncryption(Node* root, std::string code, std::map<char, std::string>& codes) {
    if (root == nullptr) {
        return;
    }

    if (root->letter != '\0') {
        code += root->valueToGetTo;
        codes[root->letter] = code;
    }

    prepareForEncryption(root->left, code + root->valueToGetTo, codes);
    prepareForEncryption(root->right, code + root->valueToGetTo, codes);
}

std::string compression(std::map<char, std::string> codes, std::string song){
    std::string compressedSong;

    for(int i = 0; i < song.length(); i++){
        compressedSong += codes[song[i]];
    }

    return compressedSong;
}

std::string decompression(Node* root, const std::string& compressedSong) {
    std::string originalSong;
    const Node* current = root;

    for (char bit : compressedSong) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            originalSong += current->letter;
            current = root;
        }
    }

    return originalSong;
}

void savememoryforlater(Node* root){

    if (root == nullptr) {
        return;
    }

    savememoryforlater(root->left);
    savememoryforlater(root->right);

    delete root;
}

/* tutaj pragnę zaznaczyć, iż pomysł z zrobieniem kolejki liści był przez ai tak wyglądał pierwotnie mój
    *
    * std::deque<std::pair<char, int>> deq(wordcount.begin(), wordcount.end());
   std::sort(deq.begin(), deq.end(), cmp);

   /*for(auto a : deq){
        std::cout << a.first << ": " << a.second << std::endl;
   }*/

/*objaśnienie: mniejsza złożoność będzie w przypadku dodawania do osobnej struktury naszych
 * informacji o wskaźnikach drzewa a niżeli ponowne dodawanie do kolejki, a następnie sortowanie
std::queue<Node*> location;
std::pair<char, int> tmp;


while(!deq.empty()){
    Node *node;
    node = newNode(0, '\0');
    if(!location.empty()) {
        if (deq.front().second > location.front()->value) {

        }
    }
    else{
        tmp = deq.front();
        deq.pop_front();
        node->value = tmp.second + deq.front().second;
        Node* left = newNode(tmp.second, tmp.first);
        Node* right = newNode(deq.front().first, deq.front().second);
        node->left = left;
        node->right = right;


    }
} */

