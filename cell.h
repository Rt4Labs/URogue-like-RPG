#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <map>
#include <ncurses.h>

class Cell
{
public:
    enum Type {EMPTY = 0, GRASS = 1, FOREST = 2, WATER = 3};
private:
     Type type;
     const std::map<Type,chtype> icon = {{EMPTY, ' ' | COLOR_PAIR(0) },
                                       {GRASS, '_' | COLOR_PAIR(1) },
                                       {FOREST, '$' | COLOR_PAIR(1) },
                                       {WATER, '~' | COLOR_PAIR(2) }};
     const std::map<char,Type> itype = {{' ', EMPTY},
                                        {'_', GRASS},
                                        {'$', FOREST},
                                        {'~', WATER}};
     int cost; // цена прохода клетки
public:

     Cell();
     Cell(Type,int);
     chtype get_icon();
     void set_type(char);
     Type get_type();
};

#endif // CELL_H
