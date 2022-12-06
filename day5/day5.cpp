#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <set>
#include <cstring>
#include <sstream>
#include <stack>
#include <tuple>

const std::string INPUT = "day5_data.txt";
const std::string TEST_INPUT = "day5_testdata.txt";
//define instructions 

struct Instruction {
    //action is move from soruce to destination
    int source;
    int destination;
};

// a single crate is just a capital letter -> char
typedef std::vector<std::tuple<int, int, int>> Instructions;
//TODO: num_stacks is variable
const int num_stacks = 9;
typedef std::array<std::vector<std::string>, num_stacks> Stacks;

std::pair<Instructions, Stacks>  parse_input(std::string input_path){

    std::ifstream inputfile;
    inputfile.open(input_path, std::ios::in);

    if (!inputfile) { 
        std::cout << "Can't read input" << std::endl;
        exit(1);
    }

    // split file content into two big chunks separated by emptyline 
    std::vector<std::string> raw_chunk1;
    std::vector<std::string> raw_chunk2;
    std::string line;

    bool instructions_started = false;
    while (std::getline(inputfile, line)) {
        
        // separator is between crates and instructions
        if (line.empty()) {
            instructions_started = true;
            continue;
        }
        
        if (!instructions_started) {
            raw_chunk1.push_back(line);
        } else {
            raw_chunk2.push_back(line);
        }
    }

    // extract number of stacks
    int num_stacks;
    std::string numbers;
    numbers = raw_chunk1.back();
    raw_chunk1.pop_back();
    numbers.pop_back();
    num_stacks = numbers.back() - '0';

    // extract crates and put in stacks
    int row = -1; //index of stack
    int col = -1; //index of crate
    Stacks stacks;
    for(auto &line : raw_chunk1) {

        //extract crates based on number of stacks
        for(int col = 0; col < num_stacks; col++) {
            int raw_col = 1 + col *4;
            std::string crate = line.substr(raw_col, 1);
            if(crate == " ")
            {
                continue;
            }
            std::cout << crate << std::endl;
            stacks[col].push_back(crate);
        }

    }
    // reverse order is needed for LIFO ordering
    for(int col = 0; col < num_stacks; col++) {
        std::reverse(stacks[col].begin(), stacks[col].end());
    }

    // extract instructions
    Instructions instructions;
    for(auto &line : raw_chunk2) {
        std::string quantity = line.substr(line.find("move ") + 5, 2); 
        std::string source = line.substr(line.find("from ") + 5, 1);
        std::string destination = line.substr(line.find("to ") + 3, 1);
        int quantity_int = std::stoi(quantity); //[0] - '0';
        int source_int = source[0] - '0';
        int destination_int = destination[0] - '0';
        instructions.push_back(std::make_tuple(quantity_int, source_int, destination_int));
    }

    inputfile.close();
    return {instructions, stacks};
}

int main() {

    // Parse input
    //auto [instructions, stacks] = 
    Instructions instructions;
    Stacks stacks;
    std::tie(instructions, stacks) = parse_input(INPUT);

    // execute all instructions
    for(auto &instruction : instructions) {

        int quantity = std::get<0>(instruction);
        int source = std::get<1>(instruction)-1;
        int destination = std::get<2>(instruction)-1;
        
        std::cout << "move " << quantity << " from " << source+1 << " to " << destination+1 << std::endl;
        // debug output: print stacks
        int stacknum=0;
        for(auto stack : stacks){
            stacknum++;     
            std::cout << stacknum << ": ";
            for(auto crate : stack) {
                std::cout << crate << " ";
            }
            std::cout <<std::endl;
        }
        std::cout << "\n\n" << std::endl;
        
        // move crates from source to destination
        std::vector<std::string> crate;
        for(int i = 0; i < quantity; i++) {

            crate.push_back(stacks[source].back());
            stacks[source].pop_back();
        }
        //reverse order of crate
        // TODO: comment out for part 1:
        std::reverse(crate.begin(), crate.end()); 
        //insert crate into stacks[destination]
        stacks[destination].insert(stacks[destination].end(), crate.begin(), crate.end());
        
    }
    // solution = crates on top of each stack 
    for(int i = 0; i < num_stacks; i++) {
        std::cout << "Solution: " << stacks[i].back() << std::endl;
    }

    return 0;
}
