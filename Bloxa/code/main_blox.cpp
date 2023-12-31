﻿/// #define SFML_STATIC /// ищи в настройках проекта ...
///----------------------------------------------------------------------------|
/// Bloxa [version:2023.11.06]
/// отключить консольное окно: -mwindows
///----------------------------------------------------------------------------:
#include "render/render.h"


///----------------------------------------------------------------------------|
/// Start.
///----------------------------------------------------------------------------:
int main()
{
    setlocale(0, "");
    srand    ((unsigned)time(NULL));

    std::wcout << L"ВЕСЬ ДЕБАГ МОЖНО ТУТ(В КОНСОЛЕ) ...\n\n";

    ///----------------------------------------|
    /// Загрузка глобальных переменных.        |
    ///----------------------------------------:
    Global::init();

    ///----------------------------------------|
    /// Рендер для задач.                      |
    ///----------------------------------------:
    std::unique_ptr<Render>  render(new Render);

    ///----------------------------------------|
    /// Задача Часы.                           |
    ///----------------------------------------:
/// obj::Test_Clock_01 clock(render->get(cam::eCAMERA::E_GAME));

    [[maybe_unused]]
    obj::Test_Axis_01  axis (render->get(cam::eCAMERA::E_RED ));
    [[maybe_unused]]
    obj::Test_Cell_01  cell (render->get(cam::eCAMERA::E_RED ));

    ///----------------------------------------|
    /// Задача Тестим Шейдеры.                 |
    ///----------------------------------------:
    [[maybe_unused]]
    obj::IObject* go_shaders =
        Test_Shaders_01::create(render->get(cam::eCAMERA::E_GAME));

    ///----------------------------------------|
    /// Задача Змейка.                         |
    ///----------------------------------------:
    [[maybe_unused]]
    obj::IObject* zmeika1 =
        Zmeika_01::create(render->get(cam::eCAMERA::E_GAME), 1);

    [[maybe_unused]]
    obj::IObject* zmeika2 =
        Zmeika_01::create(render->get(cam::eCAMERA::E_RED), 2);

    ///----------------------------------------|
    /// Добавляем задачи на рендер.            |
    ///----------------------------------------:
                            render->add    (zmeika1);

                        /// render->add    (go_shaders);
                        /// render->add    (&clock);

                        /// render->add2red(go_shaders);
                            render->add2red(zmeika2);

                        /// render->add2red(&cell );
                        /// render->add2red(&axis );



    ///----------------------------------------|
    /// Консоль тоже может быть полезна...     |
    ///----------------------------------------:
    Global::info();

    ///----------------------------------------|
    /// Запус рендера. Тут Главный цикл.       |
    ///----------------------------------------:
                             render->run();

    ///----------------------------------------|
    /// Очищаем память.                        |
    ///----------------------------------------:
    Global::del ();
}
