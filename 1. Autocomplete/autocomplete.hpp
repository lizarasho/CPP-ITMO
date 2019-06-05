#ifndef AUTOCOMPLETE_HPP
#define AUTOCOMPLETE_HPP

#include "term.hpp"
#include "binary_search_deluxe.hpp"

struct autocomplete
{
public:
    explicit autocomplete(std::vector<term>);

    std::vector<term> all_matches(std::string prefix);

    size_t number_of_matches(std::string prefix);

private:
    std::vector<term> terms_;

    std::pair<size_t, size_t> calc(std::string &prefix);
};

#endif
