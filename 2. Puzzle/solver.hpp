#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "board.hpp"

struct solver
{
public:
    explicit solver(board const &);

    size_t moves();

    typedef std::vector<board>::iterator iterator;

    iterator begin();

    iterator end();

private:
    std::vector<board> way_;

    void update(std::vector<board> &, board &, std::pair<size_t, size_t>);

    void generate_next(std::vector<board> &, board &);

    void solve(board const &);
};

#endif
