#include <iostream>
#include <ranges>
#include <string>

int main()
{
    std::string str = "hello world";

    // Use std::ranges::unique to remove consecutive duplicate characters
    auto new_end = std::ranges::unique(str);

    // Erase the characters that were removed
    str.erase(new_end, str.end());

    std::cout << str << std::endl;  // Outputs: "helo wrd"

    return 0;
}