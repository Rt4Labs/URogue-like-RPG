#ifndef ENEMY_H
#define ENEMY_H

#include "movable.h"
#include <iostream>
#include <string>
#include <queue>
#include <vector>

using std::vector;
using std::queue;
using std::pair;

class Enemy : public Movable
{
    // Поиск пути \/
    struct point
    {
        int cost;
        pair<int,int> last; // Точка из которой пришли
    };
    pair<int,int> get_way(Map,pair<int,int>); // Вызов поиска пути
    vector<vector<point>> get_terrain_map(Map); // Создание карты с ценами прохода для алгоритма
    pair<int,int> find_way(vector<vector<point>>, queue<pair<int,int>>&, pair<int,int>, pair<int,int>);
    void check_area(vector<vector<point>>&, queue<pair<int,int>>&); // Проверка по направлениям
    void check_point(vector<vector<point>>&,queue<pair<int,int>>&,pair<int,int>);
    bool whether_checked(vector<vector<point>>&,int,int); // Проверка выхода за границы карты + проверяли ли уже эту точку
    pair<int,int> restore_way(vector<vector<point>>&,pair<int,int>,pair<int,int>); // Восстановление пути
    //---------------

    std::string name;
    chtype icon;
    int hp;
    int damage;
public:
    Enemy();
    void create(std::string);
    void print();
    void step(Map&);
    void fight(Object*);
    void check(Map&, pair<int, int>);
    void get_damage(int);
    int get_hp();
    Direction get_dir_by_smth();
};

#endif // ENEMY_H
