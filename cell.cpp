#include <cell.h>
#include <ncurses.h>

Cell::Cell()
    :type(EMPTY), cost(0) {}

Cell::Cell(Type aType,int aCost)
    :type(aType), cost(aCost) {}

chtype Cell::get_icon()
{
    return icon.at(type);
}

void Cell::set_type(char ch)
{
    type=itype.at(ch);
}

Cell::Type Cell::get_type()
{
    return type;
}
