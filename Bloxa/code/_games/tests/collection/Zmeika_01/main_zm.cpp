/// #define SFML_STATIC
///----------------------------------------------------------------------------|
/// Подготовка к змейке.
///----------------------------------------------------------------------------:
#include "!start.h"

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

namespace Zmeika_01
{
    obj::IObject* create(const sf::View& v, size_t N)
    {
        switch(N)
        {
            case 1: return new sprites3::Renderspites(v, snake::config1);
            case 2: return new sprites3::Renderspites(v, snake::config2);
        }

        return nullptr;
    }
}

///----------------------------------------------------------------------------|
/// Start.
///----------------------------------------------------------------------------:
int Zmeika_01_main()
{   srand((unsigned)time(NULL));

    std::cout << "PROGRAMM START ...\n\n";

    tests();

    std::cout << "\nProgramm FINISHED!\n";

    return 0;
}
