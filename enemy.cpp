#include "enemy.h"
#include "hero.h"
#include "map.h"
#include <fstream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>


using namespace std;

Enemy::Enemy()
    :Movable(ENEMY,rand() % 20,rand() % 40)
{
    vector<string> names = {"Orc"};
    create(names.at(0/*rand() % names.size()-1*/));
}

void Enemy::create(string aName)
{
    ifstream fin("../Roguelike/Enemies/"+aName+".enemy");

    assert(fin.is_open());

    fin >> name;

    char ch;
    fin >> ch;
    icon = ch | COLOR_PAIR(4);

    fin >> hp;
    fin >> damage;
}

void Enemy::print()
{
    mvaddch(x,y,icon);
}

Movable::Direction Enemy::get_dir_by_smth()
{
    int i = rand() % 4;
    switch(i)
    {
    case 0:
        return UP;
    case 1:
        return DOWN;
    case 2:
        return RIGHT;
    case 3:
        return LEFT;
    default:
        return NONE;
    }
}

void Enemy::step(Map& map)
{
    int hero_x = map.get_object(0)->get_x();
    int hero_y = map.get_object(0)->get_y();
    if(sqrt( pow(hero_x-x,2) + pow(hero_y-y,2) ) <= 5) // Если расстояние между героем и врагом <= n
    {
        move(map,get_way(map,pair<int,int>(hero_x,hero_y) ));
    }
    else
    {
        move(map,get_cords_by_dir(get_dir_by_smth()));
    }
}

void Enemy::check(Map& map,pair<int,int> cords)
{
    Object* object = map.find_object(cords.first,cords.second);
    if(object->get_type() == HERO)
    {
        fight(object);
    }
}

void Enemy::fight(Object* hero)
{
    dynamic_cast<Hero*>(hero)->get_damage(damage);
}

void Enemy::get_damage(int damage)
{
    hp-=damage;
}

int Enemy::get_hp()
{
    return hp;
}
