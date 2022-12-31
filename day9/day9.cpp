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
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <bits/stdc++.h>

const std::string INPUT = "day9_data.txt";
const std::string TEST_INPUT = "day9_testdata.txt";

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

class Point2D{

    public:
    int x;
    int y;

    Point2D(){
        this->x = 0;
        this->y = 0;
    }
    Point2D(int x, int y){
        this->x = x;
        this->y = y;
    }
    // overload the equality operator (unordered set needs it)
    bool operator==(const Point2D& other) const
    {
        return x == other.x && y == other.y;
    }


    Point2D operator-(const Point2D& other) const{
        return Point2D(this->x - other.x, this->y - other.y);
    }
    Point2D operator+(const Point2D& other) const{
        return Point2D(this->x + other.x, this->y + other.y);
    }
    Point2D distance(const Point2D& other) const{
        return Point2D(std::abs(this->x - other.x), std::abs(this->y - other.y));
    }

    Point2D operator*(int multiplier) const{
        return Point2D(multiplier * this->x, multiplier * this->y);
    }

    //friend Point2D operator*(int multiplier, const Point2D) const{
    //    return point*multiplier;
    //}


};

// we need a hash function for the Point2D class
class Point2DHash
{
public:
    std::size_t operator()(const Point2D& p) const
    {
        // hash the x and y values separately and combine them using
        // a bitwise XOR operation
        std::size_t h1 = std::hash<int>()(p.x);
        std::size_t h2 = std::hash<int>()(p.y);
        return h1 ^ (h2 << 1);
    }
};

int main() {

    // Parse input
    auto instructions = parse_input(TEST_INPUT);

    // the snake starts at (0,0)
    Point2D head = Point2D(0,0);
    Point2D tail = Point2D(0,0);
    std::unordered_set<Point2D, Point2DHash> tailvisited;
    tailvisited.insert(tail);

    for(auto instruction : instructions){
        
        auto direction = instruction[0];
        int distance = std::stoi(instruction.substr(2));

        auto step_dir = Point2D(0,0);
        auto step = Point2D(0,0);
        switch(direction){
            case 'R':
                step_dir = Point2D(1,0);
                step = step_dir * distance;
                break;
            case 'L':
                step_dir = Point2D(-1,0);
                step = step_dir * distance;
                break;
            case 'U':
                step_dir = Point2D(0,1);
                step = step_dir * distance;
                break;
            case 'D':
                step_dir = Point2D(0,-1);
                step = step_dir * distance;
                break;
        }

        // move the head
        head = head + step;

        // if th head i on an adjacent square to the tail do nothing
        auto head_tail_diff = head.distance(tail);
        if(head_tail_diff.x <= 1 && head_tail_diff.y <= 1){
            continue;
        }
        else
        {
            // move the tail
            tail = head - step_dir;
        }

        // save new visited tail position
        tailvisited.insert(tail);

    }




   
    auto solution_part1 = tailvisited.size();
    auto solution_part2 = 0;
    std::cout << "solution part 1 (number visible trees):  " << solution_part1 << std::endl;
    std::cout << "solution part 2 (highest scenic score):  " << solution_part2 << std::endl;

    return 0;
}


