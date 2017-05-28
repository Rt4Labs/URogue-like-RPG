#include "hero.h"
#include "map.h"
#include "enemy.h"
#include <ncurses.h>

using namespace std;

Hero::Hero()
    :Movable(HERO), hp(100), damage(10) {}

Hero::Hero(int x,int y, int aHp, int aDamage)
    :Movable(HERO,x,y), hp(aHp), damage(aDamage) {}

Movable::Direction Hero::get_dir_by_smth()
{
    switch(getch())
    {
    case KEY_UP:
        return UP;
    case KEY_DOWN:
        return DOWN;
    case KEY_RIGHT:
        return RIGHT;
    case KEY_LEFT:
        return LEFT;
    default:
        return NONE;
    }
}

void Hero::step(Map& map)
{
    move(map,get_cords_by_dir(get_dir_by_smth()));
}


void Hero::check(Map& map,pair<int,int> cords)
{
    Object* object = map.find_object(cords.first,cords.second);
    if(object->get_type() == ENEMY)
    {
        fight(object);
    }
}

void Hero::fight(Object* enemy)
{
    dynamic_cast<Enemy*> (enemy)->get_damage(damage);
}

void Hero::get_damage(int damage)
{
    hp -= damage;

    if(hp <= 0)
    {
        clear();
        printw("You dead. Game Over! ;(");
        getch();
        exit(EXIT_SUCCESS);
    }
}

int Hero::get_hp()
{
    return hp;
}

Hero::~Hero()
{
}
