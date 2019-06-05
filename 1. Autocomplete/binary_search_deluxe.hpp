#ifndef BINARY_SEARCH_DELUXE_HPP
#define BINARY_SEARCH_DELUXE_HPP

#include "term.hpp"
#include <vector>

struct binary_search_deluxe {
public:
    binary_search_deluxe() = delete;
    binary_search_deluxe(binary_search_deluxe const &) = delete;
    static size_t first_index_of(std::vector<term> &, term, std::function<bool(const term&, const term&)> &);
    static size_t last_index_of(std::vector<term> &, term, std::function<bool(const term&, const term&)> &);
};

#endif
