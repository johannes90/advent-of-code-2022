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

const std::string INPUT = "day8_data.txt";
const std::string TEST_INPUT = "day8_testdata.txt";

std::vector<std::vector<int>> input_to_vector_int(const std::string& filename) {
    std::vector<std::vector<int>> result;

    std::ifstream input(filename);
    if (!input) {
        std::cerr << "Error: Could not open file '" << filename << "' for reading.\n";
        return result;
    }

    std::string line;
    while (std::getline(input, line)) {
        std::vector<int> row;

        for (char c : line) {
        row.push_back(std::stoi(std::string(1, c)));
        }

        result.push_back(row);
    }

    return result;
}

// return a vector of strings 
std::vector<std::string> splitString(const std::string& input, const std::string& delimiter)
{
    std::vector<std::string> result;
    std::size_t pos = 0;
    std::size_t found;

    while ((found = input.find(delimiter, pos)) != std::string::npos) {
        result.push_back(input.substr(pos, found - pos));
        pos = found + delimiter.length();
    }
    result.push_back(input.substr(pos));

    return result;
}

int main() {

    // Parse input
    auto grid = input_to_vector_int(INPUT);
    
    // count number of trees that are visible from outside the grid
    auto n_rows = grid.size();
    auto n_cols = grid[0].size();
    
    auto visible_at_start = 2*(n_rows + n_cols) - 4;
    auto visible_inside = 0;

    int below_greater{0};
    int above_greater{0};
    int left_greater{0};
    int right_greater{0};


    int scenic_score{0};
    // we ommit the edges of the grid
    for (size_t row = 1; row < n_rows - 1; ++row) {
        for (size_t col = 1; col < n_cols - 1; ++col) {
            
            auto current_tree = grid[row][col];

            //check if the tree is visible from outside the grid
            std::vector<int> row_left;
            std::vector<int> row_right;
            std::vector<int> col_above;
            std::vector<int> col_below;

            for(int i = 0; i < row; ++i){
                col_above.push_back(grid[i][col]);
            }
            for(int j = 0; j < col; ++j){
                row_left.push_back(grid[row][j]);
            }
            for(int i = row+1; i < n_rows; ++i){
                col_below.push_back(grid[i][col]);
            }
            for(int j = col+1; j < n_cols; ++j){
                row_right.push_back(grid[row][j]);
            }

            auto directions = {row_left, row_right, col_above, col_below};
            for(auto direction : directions ){
                
                // check if the current tree is larger than all trees in the direction (part 1)
                bool isLarger = std::none_of(direction.begin(), direction.end(), [current_tree](int x) { return current_tree <= x; });
                if(isLarger){
                    visible_inside++;
                    break;
                }
            }
            
            // Part 2: how many trees are visible (not larger) from current tree  
            auto above_trees = 0;
            for(int i = row - 1; i >= 0; i--){
                auto other_tree = grid[i][col];
                above_trees++;
                if (other_tree >= current_tree){
                    break;
                }
            }
            auto below_trees = 0;
            for(int i = row+1; i < n_rows; ++i){

                auto other_tree = grid[i][col];
                below_trees++;
                if (other_tree >= current_tree){
                    break;
                }
            }
            auto left_trees = 0;
            for(int j = col-1; j >= 0; j--){

                auto other_tree = grid[row][j];
                left_trees++;

                if (other_tree >= current_tree){
                    break;
                }
            }
            auto right_trees = 0;
            for(int j = col+1; j < n_cols; ++j){

                auto other_tree = grid[row][j];
                right_trees++;

                if (other_tree >= current_tree){
                    break;
                }
            }
            int new_scenic_score = above_trees * below_trees * left_trees * right_trees;
            if (scenic_score < new_scenic_score){
                scenic_score = new_scenic_score;
            }
        }
    }

    std::cout << "solution part 1 (number visible trees):  " <<  visible_inside + visible_at_start <<std::endl;
    std::cout << "solution part 2 (highest scenic score):  " <<  scenic_score <<std::endl;

    return 0;
}


