#ifndef TERM_HPP
#define TERM_HPP

#include <ostream>
#include <string>

struct term
{
public:
    term(term const &) = default;

    explicit term(std::string, int);

    std::string to_string() const;

    friend std::ostream &operator<<(std::ostream &, term const &);

    bool operator<(term const &);

    bool operator<=(term const &);

    bool operator>(term const &);

    bool operator>=(term const &);

    bool operator==(term const &);

    bool operator!=(term const &);

    term &operator=(term const &) = default;

    static std::function<bool(const term &, const term &) > by_reverse_weight_order();

    static std::function<bool(const term &, const term &)> by_prefix_order(size_t r);

private:
    std::string str_;
    int weight_;
};

#endif