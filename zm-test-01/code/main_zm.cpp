#define SFML_STATIC
///----------------------------------------------------------------------------|
/// Подготовка к змейке.
///----------------------------------------------------------------------------:
#include "zm_test_01.h"
#include "zm_test_02.h"
#include "zm_test_03.h"

void tests()
{
/// std::unique_ptr<Zm_test_01> run(new Zm_test_01);

/// labitinth::BestMordaEver::test();
/// sprites2 ::Loader       ::test();
/// sprites2 ::Renderspites ::test();
/// sprites2 ::Runner       ::test();

/// snake    ::tests();

    sprites3 ::Runner       ::test();
}

///----------------------------------------------------------------------------|
/// Start.
///----------------------------------------------------------------------------:
int main()
{   srand((unsigned)time(NULL));

    std::cout << "PROGRAMM START ...\n\n";

    tests();

    std::cout << "\nProgramm FINISHED!\n";
}
