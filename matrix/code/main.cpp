///----------------------------------------------------------------------------|
/// Snake-2023
///----------------------------------------------------------------------------:
#include "snake_01.h"

void tests()
{
    snake::tests();
}

///----------------------------------------------------------------------------|
/// ����.
///----------------------------------------------------------------------------:
int main()
{
    srand((unsigned)time(NULL));

    std::cout << "   Hello, I'm Snake!\n";

    tests();

    std::cout << "...programm FINISHED!\n";
    std::cin.get();
}
