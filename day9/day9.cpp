#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <bits/stdc++.h>

const std::string INPUT = "day9_data.txt";
const std::string TEST_INPUT = "day9_testdata.txt";
const std::string TEST_INPUT2 = "day9_testdata2.txt";

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

// map directions to vectors
std::unordered_map<char, Point2D> direction_map = {
    {'R', Point2D(1,0)},
    {'L', Point2D(-1,0)},
    {'U', Point2D(0,1)},
    {'D', Point2D(0,-1)}
};

Point2D rope_tail_dynamics(Point2D head, Point2D tail){

    auto vector_head_tail = head - tail;
    if(std::abs(vector_head_tail.x) <= 1 && std::abs(vector_head_tail.y) <= 1){
        return tail;
    }

    if (head.y == tail.y)
		{
			return Point2D(head.x > tail.x ? head.x - 1 : head.x + 1, tail.y );
		}
		else if (head.x == tail.x)
		{
			return Point2D( tail.x, head.y > tail.y ? head.y - 1 : head.y + 1 );
		}
		else
		{
			return Point2D
			(
				head.x > tail.x ? tail.x + 1 : tail.x - 1,
				head.y > tail.y ? tail.y + 1 : tail.y - 1
            );
		}
}

int main() {

    // Parse input
    auto instructions = parse_input(INPUT);

    //part 1:
    const int num_knots = 2;
    //part 2:
    //const int num_knots = 10;

    auto knots = std::array<Point2D, num_knots>{};
    auto& head = knots[0];
    auto& tail = knots[knots.size()-1];
    std::unordered_set<Point2D, Point2DHash> tailvisited;
    tailvisited.insert(tail);

    for(auto instruction : instructions){
        
        auto direction = instruction[0];
        int distance = std::stoi(instruction.substr(2));

        // determine the step vector for head movement
        auto step = direction_map[direction];

        // move the head distance times with step vector
        for(int j = 0; j< distance; j++){
            
            head = head + step;

            // movement of the tail knots
            for(int i = 0; i < knots.size()-1; i++){

                // rope dynamics
                knots[i+1] = rope_tail_dynamics(knots[i], knots[i+1]);
            }
            tailvisited.insert(tail);  
        }
    }

    // solution part 1 and 2
    std::cout << "visited places by tail: " << tailvisited.size() << std::endl;
    return 0;
}