#include "randomized_queue.hpp"
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
    int k = argc > 1 ? std::stoi(std::string(argv[1])) : 0;

    randomized_queue<std::string> queue;
    std::string current;

    while (std::getline(std::cin, current))
        queue.enqueue(current);

    auto it = queue.begin();
    for (size_t i = 0; i < k; i++, it++)
        std::cout << *it << '\n';

    return 0;
}