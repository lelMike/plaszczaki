#include <iostream>
#include <string>
#include <filesystem>
#include <cstring>
#include "../include/WorkerRelations.h"
#include "../include/GraphHandler.h"

int main(int argc, char* argv[]) {

    if (argc == 1 || std::strcmp(argv[1], "debug") == 0) {
        std::string input1;
        std::string input2;

        while(true) {
            std::cout << "Enter 'end' to exit, or the Worker text file name: " << std::endl; std::cin >> input1;
            std::transform(input1.begin(), input1.end(), input1.begin(), ::tolower);
            if (input1 == "end") {
                std::cout << "Program ended." << std::endl;
                return 0;
            }
            std::cout << "Coordinate text file name: " << std::endl; std::cin >> input2;
            std::transform(input2.begin(), input2.end(), input2.begin(), ::tolower);
            if (input2 == "end") {
                std::cout << "Program ended." << std::endl;
                return 0;
            }

            WorkerRelations workerRelations;

            if (workerRelations.parseTxt("txt/" + input1)) {
                std::cerr << "File error" << std::endl;
                return 1;
            }
            std::vector<std::pair<Worker, Worker>> result = workerRelations.hopcroftKarp();
            GraphHandler graphHandler;
            if (graphHandler.readInput("txt/" + input2)) {
                std::cerr << "File error" << std::endl;
                return 1;
            }
            graphHandler.calculateBorder();
            graphHandler.printGraph(true);
            float maxFlow;
            if (argc == 1) {
                maxFlow = graphHandler.calculateMaxFlow(workerRelations.getPairCount(), false);
            }
            else {
                graphHandler.printBorder();
                maxFlow = graphHandler.calculateMaxFlow(workerRelations.getPairCount(), true);
            }
            std::cout << "The max amount of pairs: " << workerRelations.getPairCount() << std::endl;
            std::cout << "The max flow for the given data is: " << maxFlow << std::endl;
            std::cout << "The amount of days it would take for the workers to build the wall is: " << graphHandler.getPerimeter() / maxFlow << std::endl << std::endl;
        }
    }
    else if (std::strcmp(argv[1], "test") == 0) {
        int i = 1;
        std::string filePath1 = "txt/p1_c1.txt";
        std::string filePath2 = "txt/p1_w1.txt";

        while(std::filesystem::exists(filePath1) && std::filesystem::exists(filePath2)) {
            WorkerRelations workerRelations;
            GraphHandler graphHandler;
            if (workerRelations.parseTxt(filePath2)) {
                std::cerr << "Test " << i << ": Worker file error" << std::endl;
                return 1;
            }
            std::vector<std::pair<Worker, Worker>> result = workerRelations.hopcroftKarp();
            if (graphHandler.readInput(filePath1)) {
                std::cerr << "Test " << i << ": Coordinates file error" << std::endl;
                return 1;
            }
            graphHandler.calculateBorder();
            float maxFlow = graphHandler.calculateMaxFlow(workerRelations.getPairCount(), false);
            std::cout << "Test " << i++ << ": " << "Max flow: " << maxFlow << " Amount of days: " << graphHandler.getPerimeter() / maxFlow << std::endl;
            filePath1 = "txt/p" + std::to_string(i) + "_c" + std::to_string(i) + ".txt";
            filePath2 = "txt/p" + std::to_string(i) + "_w" + std::to_string(i) + ".txt";
        }
    }
    else {
        std::cout << argv[1] << std::endl;
        std::cerr << "Usage: " << argv[0] << " [|debug|test]\n";
        return 1;
    }

    return 0;
}