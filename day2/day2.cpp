#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <set>
#include <map>

const std::string DAY2_INPUT = "day2_data.txt";
const std::string DAY2_TEST_INPUT = "day2_testdata.txt";

std::map<std::string, int> rules_a = {{"A Y", 8}, {"B Z", 9}, {"C X", 7}, // win round
                                     {"A X", 4}, {"B Y", 5}, {"C Z", 6}, // draw round
                                     {"A Z", 3}, {"B X", 1}, {"C Y", 2}  // loose round 
}; 

std::map<std::string, int> rules_b = {{"A Z", 8}, {"B Z", 9}, {"C Z", 7}, // win round
                                     {"A Y", 4}, {"B Y", 5}, {"C Y", 6}, // draw round
                                     {"A X", 3}, {"B X", 1}, {"C X", 2}  // loose round 
}; 

std::vector<std::string> parse_input(std::string input_path){

    std::vector<std::string> rounds;
    std::ifstream inputfile;
    inputfile.open(input_path, std::ios::in);

    if (!inputfile) { 
        std::cout << "Can't read input";
        exit(1);
    }

    std::string line;
    while (std::getline(inputfile, line)) {
        rounds.emplace_back(line);
    }

    inputfile.close();
    return rounds;
}

long play_rock_paper_scissors(std::vector<std::string> rounds, std::map<std::string, int> rules){

    long score = 0;
    for(std::string const& round: rounds) {
        
        // given the current rules, map round -> score 
        score += rules[round];
    }

    return score;
}

int main() {

    // Parse input
    std::vector<std::string> test_rounds = parse_input(DAY2_TEST_INPUT);
    std::vector<std::string> rounds = parse_input(DAY2_INPUT);
    
    // unit tests
    long score_part1_test = play_rock_paper_scissors(test_rounds, rules_a);
    assert(score_part1_test == 15);
    long score_part2_test = play_rock_paper_scissors(test_rounds, rules_b);
    assert(score_part2_test == 12);

    // Part 1:
    long score_part1 = play_rock_paper_scissors(rounds, rules_a);
    std::cout << "score part 1: " << score_part1 << std::endl;

    // Part 2:
    long score_part2 = play_rock_paper_scissors(rounds, rules_b);
    std::cout << "score part 2: " << score_part2 << std::endl;
    return 0;
}