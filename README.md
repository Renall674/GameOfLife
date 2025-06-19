# GameOfLife
## Структура:
GameOfLife:
Создать в папке проекта папки libs/SDL2/ в них добавить:         
include/"папку include из SDL2 скачанного"
lib/"папку lib из SDL2 скачанного"     
cmake/"папку cmake из SDL2 скачанного" и SDL2.dll     
Создать папку scr/ в нее добавить:
Source.cpp
Добавить в папку проекта CMakeLists.txt

## Сборка:
git clone https://git.deviks.io/Renall674/GameOfLife.git
cd "ваш путь"/GameOfLife
mkdir build && cd build
cmake ..
cmake --build . --config Release
Скопируйте SDL2.dll в папку с GameOfLife.exe
Запустите .exe файл в папке Release

## Запуск с параметрами:
GameOfLife.exe --width 1000 --height 800 --grid 30 --speed 50
GameOfLife.exe --help

## Управление:
Добавить/удалить клетку	- ЛКМ по клетке
Пауза/продолжить - Пробел
Очистить поле - C
Случайное заполнение - R
Шаг вперёд (на паузе) - S
