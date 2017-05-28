#include "map.h"
#include <fstream>
#include <cassert>

using namespace std;

Map::Map()
{
    map_init("main");
}

void Map::map_init(string location_name)
{
    ifstream fin("../Roguelike/Locations/"+location_name+".map");

    assert(fin.is_open());

    int x; // размеры карты
    int y;
    fin >> x >> y;

    for(int i=0;i<x;i++)
    {
        terrain.push_back( vector<Cell>(y) );
        for(int j=0;j<y;j++)
        {
            char ch;
            fin >> ch;

            terrain[i][j].set_type(ch); // задаёт значение массива по символу
        }
    }
}

void Map::print_cell(Cell cell,int x,int y)
{
    mvaddch(x,y,cell.get_icon());
}

void Map::print_map()
{
    for(unsigned int i=0;i<terrain.size();i++)
    {
        for(unsigned int j=0;j<terrain.at(i).size();j++)
        {
            print_cell(terrain[i][j],i,j);
        }
    }
}

bool Map::is_free(int x, int y)
{
    if(is_correct_cords(x,y))
    {
        for(unsigned int i=0;i<objects.size();i++)
        {
            if(x == objects.at(i)->get_x() && y == objects.at(i)->get_y())
            {
                return FALSE;
            }
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void Map::add_object(Object* o)
{
    objects.push_back(o);
}

bool Map::is_softly(int x, int y)
{
    if(is_correct_cords(x,y))
    {
        switch(terrain[x][y].get_type())
        {
        case Cell::EMPTY:
            return FALSE;
            break;
        case Cell::GRASS:
            return TRUE;
            break;
        case Cell::FOREST:
            return TRUE;
            break;
        case Cell::WATER:
            return FALSE;
            break;
        default:
            return FALSE;
            break;
        }
    }
    else
    {
        return FALSE;
    }
}

bool Map::is_correct_cords(int x, int y)
{
    if(x<0 || x>=terrain.size() || y>=terrain.at(x).size() || y<0 )
    {
        return FALSE;
    }
    return TRUE;
}

Map::~Map()
{
    objects.erase(objects.cbegin(),objects.cend());
}

void Map::objects_steps(Map& map)
{
    remove_objects();
    for(unsigned int i=0;i<objects.size();i++)
    {
        objects.at(i)->step(map);
    }
}

Object* Map::find_object(int x, int y)
{
    for(unsigned int i=0;i<objects.size();i++)
    {
        if(objects.at(i)->get_x() == x && objects.at(i)->get_y() == y)
        {
            return objects.at(i);
        }
    }
}

void Map::remove_objects()
{
    for(unsigned int i=0;i<objects.size();i++)
    {
        if(objects.at(i)->get_hp() <= 0)
        {
            objects.erase(objects.begin()+i);
        }
    }
}

void Map::print_objects()
{
    unsigned int i=0;
    while(i<objects.size())
    {
        objects.at(i)->print();
        i++;
    }
}

int Map::get_height()
{
    return terrain.size();
}

int Map::get_weidth(int i)
{
    return terrain.at(i).size();
}

Object* Map::get_object(int i)
{
    return objects.at(i);
}
