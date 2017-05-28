#include <object.h>
#include <ncurses.h>
#include <iostream>

Object::Object()
    :otype(NONE), x(-1), y(-1) {}

Object::Object(Type type, int aX, int aY)
    :otype(type), x(aX), y(aY) {}

int Object::get_x()
{
    return x;
}

int Object::get_y()
{
    return y;
}

Object::Type Object::get_type()
{
    return otype;
}

void Object::print()
{
    mvaddch(x,y,symbol.at(otype));
}

void Object::step(Map& map)
{

}

