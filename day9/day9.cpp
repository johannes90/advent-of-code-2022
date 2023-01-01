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

class Vector2d{

    public:
    int x;
    int y;

    public:
    Vector2d(){
        this->x = 0;
        this->y = 0;
    }
    Vector2d(int x, int y){
        this->x = x;
        this->y = y;
    }

    bool operator==(const Vector2d& other) const
    {
        return x == other.x && y == other.y;
    }
    
    Vector2d operator-(const Vector2d& other) const{
        return Vector2d(this->x - other.x, this->y - other.y);
    }
    
    Vector2d operator+(const Vector2d& other) const{
        return Vector2d(this->x + other.x, this->y + other.y);
    }

};

// we need a hash function for the Vector2d class
class Vector2dHash
{
public:
    std::size_t operator()(const Vector2d& p) const
    {
        // hash the x and y values separately and combine them using
        // a bitwise XOR operation
        std::size_t h1 = std::hash<int>()(p.x);
        std::size_t h2 = std::hash<int>()(p.y);
        return h1 ^ (h2 << 1);
    }
};

// map directions to vectors
std::unordered_map<char, Vector2d> direction_map = {
    {'R', Vector2d(1,0)},
    {'L', Vector2d(-1,0)},
    {'U', Vector2d(0,1)},
    {'D', Vector2d(0,-1)}
};

Vector2d rope_tail_dynamics(Vector2d head, Vector2d tail){

    auto vector_head_tail = head - tail;
    if(std::abs(vector_head_tail.x) <= 1 && std::abs(vector_head_tail.y) <= 1){
        return tail;
    }

    if (head.y == tail.y)
		{
			return Vector2d(head.x > tail.x ? head.x - 1 : head.x + 1, tail.y );
		}
		else if (head.x == tail.x)
		{
			return Vector2d( tail.x, head.y > tail.y ? head.y - 1 : head.y + 1 );
		}
		else
		{
			return Vector2d
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

    auto knots = std::array<Vector2d, num_knots>{};
    auto& head = knots[0];
    auto& tail = knots[knots.size()-1];
    std::unordered_set<Vector2d, Vector2dHash> tailvisited;
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