#include "autocomplete.hpp"

autocomplete::autocomplete(std::vector<term> terms) : terms_(terms)
{}

std::pair<size_t, size_t> autocomplete::calc(std::string &prefix)
{
    auto prefix_cmp = term::by_prefix_order(prefix.size());
    term t = term(prefix, 0);
    sort(terms_.begin(), terms_.end(), prefix_cmp);
    size_t first_ind = binary_search_deluxe::first_index_of(terms_, t, prefix_cmp);
    size_t last_ind = binary_search_deluxe::last_index_of(terms_, t, prefix_cmp);
    return {first_ind, last_ind};
}

std::vector<term> autocomplete::all_matches(std::string prefix)
{
    auto[first_ind, last_ind] = calc(prefix);
    std::vector<term> result(terms_.begin() + first_ind, terms_.begin() + last_ind + 1);
    sort(result.begin(), result.end(), term::by_reverse_weight_order());
    return result;
}

size_t autocomplete::number_of_matches(std::string prefix)
{
    auto[first_ind, last_ind] = calc(prefix);
    return last_ind - first_ind + 1;
}