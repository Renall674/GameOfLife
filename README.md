# GameOfLife
## Описание
Игра происходит на размеченной на клетки плоскости. Каждая клетка может находиться в двух состояниях: быть «живой» (заполненной) или «мёртвой» (пустой). Клетка имеет восемь соседей, окружающих её. 
## Структура:
GameOfLife:
Создать в папке проекта папки libs/SDL2/ в последнюю добавить:         
include/"папку include из SDL2 скачанного"
lib/"папку lib из SDL2 скачанного"     
cmake/"папку cmake из SDL2 скачанного" и SDL2.dll     
Создать папку(рядом с libs) scr/ в нее добавить:
Source.cpp.
Добавить в папку проекта CMakeLists.txt

## Сборка:
1)git clone https://github.com/Renall674/GameOfLife.git
2)cd "ваш путь"/GameOfLife
3)mkdir build && cd build
4)cmake ..
5)cmake --build . --config Release
6)Скопируйте SDL2.dll в папку с GameOfLife.exe
7)Запустите .exe файл в папке Release

## Запуск с параметрами:
GameOfLife.exe --width 1000 --height 800 --grid 30 --speed 50
GameOfLife.exe --help

## Управление:
Добавить/удалить клетку	- ЛКМ по клетке
Пауза/продолжить - Пробел
Очистить поле - C
Случайное заполнение - R
Шаг вперёд (на паузе) - S
