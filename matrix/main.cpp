#include <iostream>
#include <vector>

///-----------------------|
/// Ячейка матрицы.       |
///-----------------------:
struct Cell
{
    int status = int('.');
};

///-----------------------|
/// Для удобства.         |
///-----------------------:
using massiv_t = std::vector<Cell    >;
using matrix_t = std::vector<massiv_t>;

///-----------------------|
/// Процедура печати.     |
///-----------------------:
std::ostream& operator<<(std::ostream& o, const matrix_t& m)
{   for    (const auto& r : m)
    {   o << "   ";
        for(const auto& e : r)
        {   o << char(e.status);
        }   o << '\n';
    }       o << '\n';
    return  o;
}

///-----------------------|
/// Добавим стенки.       |
///-----------------------:
void add_walls(matrix_t& m)
{
    for(auto& e : m.front()) e.status = int('#');

    m.back() = m.front();

    for(auto& r : m)
    {   r.front().status = int('#'); r.back() = r.front();
    }
}

///-----------------------|
/// Тест.                 |
///-----------------------:
int main()
{
    std::cout << "...Hello world!\n";

    ///-------------------|
    /// Матрица 10 x 20.  |
    ///-------------------:
    matrix_t matrix(10, massiv_t(20));

    ///-------------------|
    /// Добавим стенки.   |
    ///-------------------:
    add_walls     (matrix);

    ///-------------------|
    /// Вывод на печать.  |
    ///-------------------:
    std::cout <<   matrix ;
}
