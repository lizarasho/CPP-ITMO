#include "solver.hpp"
#include <queue>
#include <map>
#include <set>

solver::solver(board const &a)
{
    solve(a);
};

size_t solver::moves()
{
    return way_.size() - 1;
}

solver::iterator solver::begin()
{
    return way_.begin();
}

solver::iterator solver::end()
{
    return way_.end();
}

void solver::update(std::vector<board> &next, board &current,
                    std::pair<size_t, size_t> next_ind)
{
    auto cur_ind = current.empty_pos();
    auto next_board = current.swap(cur_ind, next_ind);
    next.push_back(next_board);
}

void solver::generate_next(std::vector<board> &next, board &current)
{
    auto empty_pos = current.empty_pos();
    if (empty_pos.first > 0)
        update(next, current, {empty_pos.first - 1, empty_pos.second});
    if (empty_pos.first + 1 < current.size())
        update(next, current, {empty_pos.first + 1, empty_pos.second});
    if (empty_pos.second > 0)
        update(next, current, {empty_pos.first, empty_pos.second - 1});
    if (empty_pos.second + 1 < current.size())
        update(next, current, {empty_pos.first, empty_pos.second + 1});
}

void solver::solve(board const &start)
{
    if (!start.is_solvable())
        return;

    auto cmp1 = [](board const &a, board const &b)
    {
        for (size_t i = 0; i < a.size(); i++)
        {
            for (size_t j = 0; j < a.size(); j++)
            {
                if (a[i][j] != b[i][j])
                {
                    return a[i][j] < b[i][j];
                }
            }
        }
        return false;
    };
    auto cmp2 = [](board left, board right)
    {
        return left.hamming() + left.manhattan() > right.hamming() + right.manhattan();
    };

    std::priority_queue<board, std::vector<board>, decltype(cmp2)> Q(cmp2);
    std::map<board, board, decltype(cmp1)> parent(cmp1);
    Q.push({start});
    std::map<board, int, decltype(cmp1)> g(cmp1);
    g.insert({start, 0});
    std::set<board, decltype(cmp1)> used(cmp1);

    while (!Q.empty())
    {
        auto current = Q.top();
        if (current.is_goal())
            break;
        Q.pop();
        used.insert(current);
        std::vector<board> next;
        generate_next(next, current);
        for (const auto &v : next)
        {
            int score = g[current] + v.hamming() + v.manhattan();
            if (used.count(v) && score >= g[v])
                continue;
            
            parent[v] = current;
            g[v] = score;

            if (!used.count(v))
                Q.push(v);
        }
    }
    if (Q.top().is_goal())
    {
        way_.push_back(Q.top());
        while (way_.back() != start)
            way_.push_back(parent[way_.back()]);
        std::reverse(way_.begin(), way_.end());
    }
}