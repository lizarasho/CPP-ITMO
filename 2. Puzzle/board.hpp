#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

struct board
{
public:
    board();

    board(board const &) = default;

    explicit board(std::vector<std::vector<int>> const &table);

    explicit board(size_t const);

    size_t size() const;

    int hamming() const;

    int manhattan() const;

    bool is_goal() const;

    bool is_solvable() const;

    std::string to_string() const;

    std::pair<size_t, size_t> empty_pos() const;

    board swap(std::pair<size_t, size_t> const &, std::pair<size_t, size_t> const &) const;

    bool operator==(board const &);

    bool operator!=(board const &);

    friend std::ostream &operator<<(std::ostream &, board &);

    std::vector<int> operator[](int) const;

    board &operator=(board const &) = default;

private:
    std::vector<std::vector<int>> table_;
    int hamming_;
    int manhattan_;
    std::pair<size_t, size_t> empty_pos_;

    void calc(size_t i, size_t j);
};

#endif
