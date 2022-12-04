#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <set>
#include <cstring>


const std::string INPUT = "day3_data.txt";
const std::string TEST_INPUT = "day3_testdata.txt";

int compute_priority(char item){
    const std::string lookup = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    return (lookup.find(item) + 1); 
}

std::vector<std::string> parse_input(std::string input_path){

    std::ifstream inputfile;
    inputfile.open(input_path, std::ios::in);

    if (!inputfile) { 
        std::cout << "Can't read input" << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inputfile, line)) {
        lines.emplace_back(line);
    }

    inputfile.close();
    return lines;
}

std::set<char> string_to_set(std::string in_string){

    std::set<char> s;
    char char_array[in_string.size()];
    strcpy(char_array, in_string.c_str());
    for(char c : char_array)
    {
        s.insert(c);
    }
    return s;
}

int compute_part1(std::vector<std::string> contents){

    int score = 0;
    for(const std::string& content : contents){

        // split content into two parts and stransform to set
        int n_half = content.size()/2;
        std::set<char> part1_set = string_to_set(content.substr(0, n_half));
        std::set<char> part2_set = string_to_set(content.substr(n_half, n_half));

        // build intersection of the parts
        std::set<char> intersect;
        std::set_intersection(part1_set.begin(), part1_set.end(), part2_set.begin(), part2_set.end(),
                 std::inserter(intersect, intersect.begin()));

        // we assume only one element intersects
        score += compute_priority(*intersect.begin());
    }

    return score;
}

int compute_part2(std::vector<std::string> contents){

    int score = 0;
    int cnt = 1;
    for(std::vector<std::string>::iterator it = contents.begin(); it != contents.end(); it++){
        
        // TODO: to this with for loop directly
        if(cnt%3 != 0){
            cnt++;
            continue;
        }

        std::set ruck1 = string_to_set(*it);
        std::set ruck2 = string_to_set(*std::next(it, -1));
        std::set ruck3 = string_to_set(*std::next(it, -2));

        // compute intersection
        std::set<char> intersect;
        std::set<char> intersect2;
        set_intersection(ruck1.begin(), ruck1.end(), ruck2.begin(), ruck2.end(),
                        std::inserter(intersect, intersect.begin()));
        
        set_intersection(intersect.begin(), intersect.end(), ruck3.begin(), ruck3.end(),
                        std::inserter(intersect2, intersect2.begin()));

        score += compute_priority(*intersect2.begin());

        cnt++;
    }
    return score;
}

int main() {

    // Parse input
    std::vector<std::string> contents = parse_input(INPUT);

    // Part 1
    std::cout << "solution part 1:" << compute_part1(contents) << std::endl;
    
    // Part 2
    std::cout << "solution part 2:" << compute_part2(contents) << std::endl;

    return 0;
}