#include "board.hpp"
#include <random>

board::board() : table_({{0}}), empty_pos_({0, 0}), hamming_(0), manhattan_(0)
{};

board::board(std::vector<std::vector<int>> const &table) : table_(table)
{
    hamming_ = manhattan_ = 0;
    for (size_t i = 0; i < table.size(); i++)
    {
        for (size_t j = 0; j < table.size(); j++)
        {
            calc(i, j);
        }
    }
};

board::board(size_t const size)
{
    std::vector<int> shuffled(size * size);
    for (int i = 0; i < shuffled.size(); i++)
    {
        shuffled[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffled.begin(), shuffled.end(), g);
    table_.resize(size, std::vector<int>(size));
    hamming_ = manhattan_ = 0;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            table_[i][j] = shuffled[i * size + j];
            calc(i, j);
        }
    }
}

size_t board::size() const
{
    return table_.size();
}

int board::hamming() const
{
    return hamming_;
}

int board::manhattan() const
{
    return manhattan_;
}

bool board::is_goal() const
{
    return hamming_ == 0;
}

bool board::is_solvable() const
{
    int cnt = 0;
    for (size_t i = 0; i < size(); i++)
    {
        for (size_t j = 0; j < size(); j++)
        {
            if (table_[i][j] == 0)
            {
                continue;
            }
            for (size_t x = i; x < size(); x++)
            {
                for (size_t y = (i == x) ? j + 1 : 0; y < size(); y++)
                {
                    if (table_[x][y] == 0)
                    {
                        continue;
                    }
                    cnt += table_[x][y] < table_[i][j];
                }
            }
        }
    }
    return (cnt + empty_pos_.first + size() + 1) % 2 == 0;
}

std::string board::to_string() const
{
    std::string result;
    for (auto row : table_)
    {
        for (auto item : row)
        {
            result += item ? std::to_string(item) + " " : "_ ";
        }
        result += "\n";
    }
    return result;
}

std::pair<size_t, size_t> board::empty_pos() const
{
    return empty_pos_;
}

board board::swap(std::pair<size_t, size_t> const &a, std::pair<size_t, size_t> const &b) const
{
    auto result = table_;
    std::swap(result[a.first][a.second], result[b.first][b.second]);
    return board(result);;
}

bool board::operator==(board const &a)
{
    return this->table_ == a.table_;
}

bool board::operator!=(board const &a)
{
    return !(*this == a);
}

std::ostream &operator<<(std::ostream &os, board &a)
{
    os << a.to_string();
    return os;
}

std::vector<int> board::operator[](int index) const
{
    return table_[index];
}

void board::calc(size_t i, size_t j)
{
    if (table_[i][j] == 0)
    {
        empty_pos_ = {i, j};
        return;
    }
    hamming_ += table_[i][j] != i * size() + j + 1;
    size_t row = (table_[i][j] - 1) / size();
    size_t col = (table_[i][j] - 1) % size();
    manhattan_ += abs(int(row - i)) + abs(int(col - j));
}