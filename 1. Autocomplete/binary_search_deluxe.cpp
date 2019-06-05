#include "binary_search_deluxe.hpp"

#include <algorithm>

size_t binary_search_deluxe::first_index_of(std::vector<term> &a, term key,
                                         std::function<bool(term const &, term const &)> & cmp)
{
    return std::lower_bound(a.begin(), a.end(), key, cmp) - a.begin();
}

size_t binary_search_deluxe::last_index_of(std::vector<term> &a, term key,
                                        std::function<bool(term const &, term const &)> & cmp)
{
    return std::upper_bound(a.begin(), a.end(), key, cmp) - a.begin() - 1;
}