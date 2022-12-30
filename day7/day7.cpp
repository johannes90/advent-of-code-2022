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

const std::string INPUT = "day7_data.txt";
const std::string TEST_INPUT = "day7_testdata.txt";

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

class File{
    private:
        std::string path_; // path = path_of_dir/filename
        int size_{0};

    public:
        File() = default;
        File(std::string path, int size){
            this->path_ = path;
            this->size_ = size;
        }
        int get_size(){ return this->size_; }
};

class Directory{ 

    private:
        std::string path_;
        std::unordered_set<std::string> subdirectories_; //paths of directories
        std::unordered_set<std::string> files_; //paths of files
        int size_{0};

    public:
        Directory() = default;
        Directory(std::string path){
            this->path_ = path;
        }
        void add_subdirectory(std::string subdirectory){
            this->subdirectories_.insert(subdirectory);
        }
        void add_file(std::string file){
            this->files_.insert(file);
        }
        std::unordered_set<std::string> get_files(){ 
            return this->files_;
        }
        std::unordered_set<std::string> get_subdirectories(){ 
            return this->subdirectories_; 
        }
        std::string get_path(){ 
            return this->path_; 
        }
        int get_size(){ 
            return this->size_; 
        }
        void add_size(int size){ 
            this->size_ += size; 
        }

        static void calculate_total_size(Directory &dir, std::unordered_map<std::string, Directory>& all_dirs)
        {
        
            for (const auto& path : dir.get_subdirectories())
            {
                calculate_total_size(all_dirs.at(path), all_dirs);
                dir.add_size(all_dirs.at(path).get_size());
            }
        }

};

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

typedef std::unordered_map<std::string, Directory> Directories;
typedef std::unordered_map<std::string, File> Files;

std::pair<Directories, Files> parse_filesystem(std::vector<std::string> input)
{   
    // the path to a file or directory is a unique identifier
    Directories all_dirs; 
    Files all_files; 

    all_dirs["/"] = Directory("/"); // root directory


    // use vector to easily keep track last directories in case we go up
    std::vector<std::string> pwd = {"/"};

    // Part 1: find all of the directories with a total size of at most 100000
    // calculate the sum of those directories

    // parse_filesystem (assume we start at root directory "/")
    for (const auto& line : input)
    {
        auto tokens = splitString(line, " ");   
        if (tokens[0] == "$")
        {
            if (tokens[1] == "ls"){ continue; } // ls is followed by files, dirs
            else
            {   
                assert(tokens[1] == "cd");
                const auto& target = tokens[2];
                if (target == "/")
                {   
                    // "/" means go to root directory -> pwd = "/" 
                    pwd.clear();
                    pwd.emplace_back("/");
                }
                else if (target == "..")
                {   
                    // ".." means go up one directory
                    pwd.pop_back();
                }
                else
                {   
                    // go down to target
                    pwd.emplace_back(pwd.back() + target + "/");
                }
            }
        }
        else
        // listed files and dirs
        {
            auto& parentDir = all_dirs.at(pwd.back());
            if (tokens[0] == "dir")
            // directory
            {   
                auto path = pwd.back() + tokens[1] + "/";
                if (!all_dirs.contains(path))
                {
                    all_dirs[path] = Directory{ path };
                }
                parentDir.add_subdirectory(path);
            }
            else
            // file
            {   
                std::string filename = tokens[1];
                int filesize = std::stoi(tokens[0]);
                std::string path = pwd.back() + filename;
                if (!all_files.contains(path))
                {
                    all_files[path] = File(path, filesize); 
                }
                parentDir.add_file(path);
                parentDir.add_size(filesize);
            }
        }
	}

    return std::make_pair(all_dirs, all_files);

}


int main() {

    // Parse input
    auto input = parse_input(INPUT);

    auto [all_dirs, all_files] = parse_filesystem(input);

    // calculate size of all directories
    all_dirs["/"].calculate_total_size(all_dirs["/"], all_dirs);

    // Part 1: find all of the directories with a total size of at most 100000
    // calculate the sum of those directories
    int sum = 0;
    for (const auto& dir : all_dirs)
    {
        auto directory = dir.second;
        if (directory.get_size() <= 100000)
        {
            sum += directory.get_size();
        }
    }

    std::cout << "solution part1: (sum aof all dirs<= 100000) " << sum << std::endl;
    

    // part 2: find smallest directory that would free up enough space
    auto total_disc_space = 70000000;
    auto update_space = 30000000;

    auto used_disc_space = all_dirs["/"].get_size();
    auto free_space = total_disc_space - used_disc_space;
    
    auto free_up_space = update_space - free_space;


    // find smallest directory that would free up enough space
    int min_size = INT_MAX;
    std::string min_path;
    for (const auto& dir : all_dirs)
    {
        auto directory = dir.second;
        if (directory.get_size() >= free_up_space && directory.get_size() < min_size)
        {
            min_size = directory.get_size();
            min_path = directory.get_path();
        }
    }

    return 0;
}


