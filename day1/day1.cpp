#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cassert>

const std::string DAY1_INPUT = "day1_data.txt";
const std::string DAY1_TEST_INPUT = "day1_testdata.txt";

std::vector<long> parse_input(std::string input_path){

    std::vector<long> elves;
    std::ifstream inputfile;
    inputfile.open(input_path, std::ios::in);

    if (!inputfile) { 
        std::cout << "Can't read input";
        exit(1);
    }

    std::string line;
    long calorie_sum{0};
    while (std::getline(inputfile, line)) {
        
        // empty lines devide calorie readings for each elf
        if (line.empty()) {            

            elves.emplace_back(calorie_sum);
            
            calorie_sum = 0;
            continue;
        }
        calorie_sum += stoi(line);

    }
    elves.emplace_back(calorie_sum);
    inputfile.close();

    std::sort(elves.begin(), elves.end());
    return elves;
}

int main() {

    // unit tests
    std::vector<long> test = parse_input(DAY1_TEST_INPUT);

    // solution part 1
    long test_part1_solution = test.back();
    assert(test_part1_solution == 24000);

    //solution part 2
    long test_part2_solution = std::accumulate(test.end()-3, test.end(), 0.0);
    assert(test_part2_solution == 45000);

    // solution day 1
    std::vector<long> elves = parse_input(DAY1_INPUT);

    // Part 1: highest calorie
    long part1_solution = elves.back();
    std::cout << "Part 1: elf with most calories carries " << part1_solution << " calories" << std::endl;

    // Part 2: sum of the three largest calories
    long part2_solution = std::accumulate(elves.end()-3, elves.end(), 0.0);
    std::cout << "Part 2: sum of three largest calories: " << part2_solution << std::endl;
    return 0;
}

