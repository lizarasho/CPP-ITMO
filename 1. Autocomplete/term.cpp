#include "term.hpp"

term::term(std::string const str, int const weight) : str_(str), weight_(weight)
{};

std::string term::to_string() const
{
    return std::to_string(weight_) + ' ' + str_;
}

std::ostream &operator<<(std::ostream &os, term const &a)
{
    os << a.to_string();
    return os;
}

bool term::operator==(term const &a)
{
    return this->weight_ == a.weight_ && this->str_ == a.str_;
}

bool term::operator<(term const &a)
{
    if (weight_ == a.weight_)
        return str_ < a.str_;
    return weight_ < a.weight_;
};

bool term::operator<=(term const &a)
{
    return *this < a || *this == a;
}

bool term::operator>=(term const &a)
{
    return !(*this < a);
}

bool term::operator!=(term const & a)
{
    return !(*this == a);
}

bool term::operator>(term const &a)
{
    return !(*this <= a);
}

std::function<bool(const term &, const term &)> term::by_reverse_weight_order()
{
    return [](term const &a, term const &b)
    {
        return a.weight_ > b.weight_;
    };
}

std::function<bool(const term &, const term &)> term::by_prefix_order(size_t r)
{
    return [r](term const &x, term const &y)
    {
        return x.str_.substr(0, r) < y.str_.substr(0, r);
    };
}