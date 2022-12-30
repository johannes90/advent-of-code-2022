#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <numeric>
#include <set>
#include <cstring>
#include <sstream>
#include <ranges>
#include <algorithm>



const std::string INPUT = "day6_data.txt";
const std::string TEST_INPUT = "day6_testdata.txt";

std::vector<std::string> parse_input(std::string input_path){

    std::ifstream inputfile;
    inputfile.open(input_path, std::ios::in);

    if (!inputfile) { 
        std::cout << "Can't read input" << std::endl;
        exit(1);
    }

    std::string line;
    auto lines = std::vector<std::string>{};
    
    while (std::getline(inputfile, line)) {
        lines.emplace_back(line);
    }


    inputfile.close();
    return lines;
}


int main() {

    // Parse input
    auto input = parse_input(INPUT);
    const auto& line = input[0];
    
    // Part 1
    constexpr int desiredHeaderSize = 14;
    auto headerEndIndex = -1;
    for (auto i = 0; i < line.size() - desiredHeaderSize; ++i)
    {
        auto header = line.substr(i, desiredHeaderSize);
        std::ranges::sort(header);
        
        auto [first, last] = std::ranges::unique(header);
        header.erase(first, last);
        
        if (header.size() == desiredHeaderSize)
        {
            headerEndIndex = i + desiredHeaderSize;
            break;
        }
    }

    std::cout << "Header end index: " << headerEndIndex << std::endl;
    
    
    return 0;
}