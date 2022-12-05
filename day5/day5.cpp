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
// do parsing in two steps
const int num_stacks = 3;
typedef std::array<std::vector<std::string>,3> Stacks;


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
        std::string quantity = line.substr(line.find("move ") + 5, 1); 
        std::string source = line.substr(line.find("from ") + 5, 1);
        std::string destination = line.substr(line.find("to ") + 3, 1);
        int quantity_int = quantity[0] - '0';
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
    std::tie(instructions, stacks) = parse_input(TEST_INPUT);

    return 0;
}
