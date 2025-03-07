#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <set>

// Read a file that lists an inference graph (INPUT) 
// writes a file that lists colours for every node of the graph (OUTPUT)
// Colors: A-Z 26 colors/registers

/*
INPUT: n comma seperated nodes ASC from 1, with m interferences (not sorted)
n <= 50
m >= 1
characters: digits, commas, end-of-lines, reject otherwise.

1. name of input file
2. name of output file
E.g. % <myprogram> input.txt output.txt

OUTPUT: n nodes with its colour e.g. 1A, 2B... ASC
Error handling: simple message and exit.

RUN:
g++ -std=c++11 -o main main.cpp
main input.txt output.txt
*/


std::vector<std::pair<int, std::vector<int>>> parseInputFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Error opening input file");
    }
    std::vector<std::pair<int, std::vector<int>>> graph; // [(node, [interference nodes...]), ...]
    std::string line;
    while (std::getline(infile, line)){
        for (char c : line) {
            if (!isdigit(c) && c != ',' && c != '\n' && c != '\r') { // Reject invalid characters
                throw std::runtime_error("Invalid character in input file");
            }
        }
        std::stringstream ss(line);
        std::string node;
        std::vector<int> nodes;
        std::getline(ss, node, ','); // First node
        int firstNode = std::stoi(node); // Convert to int
        while (std::getline(ss, node, ',')){ // Find Interference nodes
            nodes.push_back(std::stoi(node)); // Convert to int + add to interefence nodes list
        }
        graph.push_back(std::make_pair(firstNode, nodes));
    }

    infile.close();
    return graph;
}

void printGraph(const std::vector<std::pair<int, std::vector<int>>>& graph){
    for (const auto& pair : graph){
        std::cout << pair.first << ": ";
        for (int node : pair.second){
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
}

void printColours(const std::map<int, char>& colours){
    for (const auto& pair : colours){
        std::cout << pair.first << pair.second << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return 1;
    }

    // Read input and output file names
    std::string ifile = argv[1];
    std::string ofile = argv[2];

    try {
        std::vector<std::pair<int, std::vector<int>>> graph = parseInputFile(ifile);
        // printGraph(graph);
        for (auto& pair : graph){ // Sort interference nodes ASC
            std::sort(pair.second.begin(), pair.second.end());
        }
        // Sort graph by number of interference nodes, if equal, by node number
        std::sort(graph.begin(), graph.end(), [](const std::pair<int, std::vector<int>>& a, const std::pair<int, std::vector<int>>& b) {
            if (a.second.size() == b.second.size()) {
                return a.first < b.first;
            }
            return a.second.size() > b.second.size();
        });
        // printGraph(graph);

        std::map<int, char> colours;
        for (const auto& pair : graph){
            // Find used colours in interference nodes (obviously, if they have been assigned)
            std::set<char> usedColours;
            for (int node : pair.second){
                if (colours.find(node) != colours.end()){
                    usedColours.insert(colours[node]);
                }
            }
            for (char c = 'A'; c <= 'Z'; c++){ // Find first colour not used and assign it, store in map.
                if (usedColours.find(c) == usedColours.end()){
                    colours[pair.first] = c;
                    break;
                }
            }
            if (colours.find(pair.first) == colours.end()) // If no colour found, throw error:
                throw std::runtime_error("Error assigning colour to node");
        }

        // Write to ouput file, node with corresponding colour
        std::ofstream outfile(ofile);
        if (!outfile.is_open()) {
            throw std::runtime_error("Error opening output file");
        }
        for (const auto& pair : colours){
            outfile << pair.first << pair.second << std::endl;
        }
        outfile.close();
        printColours(colours);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
