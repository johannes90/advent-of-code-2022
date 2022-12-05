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

const std::string INPUT = "day4_data.txt";
const std::string TEST_INPUT = "day4_testdata.txt";

struct bounds{
    int lower;
    int upper;
};


std::vector<std::vector<bounds>> parse_input(std::string input_path){

    std::ifstream inputfile;
    inputfile.open(input_path, std::ios::in);

    if (!inputfile) { 
        std::cout << "Can't read input" << std::endl;
        exit(1);
    }

    std::string line;
    
    std::vector<std::vector<bounds>>  assignments;

    int upper1, lower1, upper2, lower2;
    int score = 0;
    while (std::getline(inputfile, line)) {

        std::vector<bounds> assignment;
    	std::replace(line.begin(), line.end(), '-', ' ');
        std::replace(line.begin(), line.end(), ',', ' ');

        std::istringstream linestream(line);
        // 2-4,6-8
        linestream >> lower1 >> upper1 >> lower2 >> upper2;
      
        bool part1_contains2 = (lower1<=lower2 && upper1 >= upper2); 
        bool part2_contains1 = (lower2<=lower1 && upper2 >= upper1); 

        if(part1_contains2 || part2_contains1){
            score++;
        }
        bounds b1;
        b1.lower = lower1;
        b1.upper = upper1;
        bounds b2;
        b2.lower = lower2;
        b2.upper = upper2;


        assignment.push_back(b1);
        assignment.push_back(b2);

        assignments.push_back(assignment);
    
    }

    inputfile.close();
    return assignments;
}


int main() {

    // Parse input
    std::vector<std::vector<bounds>> assignments = parse_input(INPUT);
    // Part 1
    
    // Part 2
    int score = 0;
    for(std::vector<bounds> assignment : assignments){

        int lower1 = assignment.at(0).lower;
        int upper1 = assignment.at(0).upper;

        int lower2 = assignment.at(1).lower;
        int upper2 = assignment.at(1).upper;


        bool overlap1 = lower1 >= lower2 && lower1 <= upper2;
        bool overlap2 = lower2 >= lower1 && lower2 <= upper1;

        bool overlap3 = upper1 >= lower2 && upper1 <= upper2;
        bool overlap4 = upper2 >= lower1 && upper2 <= upper1;


        if(overlap1 || overlap2 || overlap3 || overlap4)
        {
            score++;
        }

    }

    std::cout << score << std::endl; 
    return 0;
}
