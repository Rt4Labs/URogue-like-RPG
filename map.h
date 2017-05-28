#ifndef MAP_H
#define MAP_H

#include "cell.h"
#include "object.h"
#include <vector>
#include "object.h"
#include <map>


class Object;

class Map
{
private:
    bool is_correct_cords(int,int); // проверка корректности координат, переданных в функцию
    void remove_objects();
protected:
    std::vector< std::vector<Cell> > terrain; // Карта уровня
    std::vector<Object*> objects; // Все сушества, существующие на карте уровня
public:
    Map();
    void map_init(std::string); // загрузка конкретной локации по её названию
    void print_cell(Cell,int,int);
    void print_map(); // вывод карты на экран
    void print_objects(); // вывод объектов на экран
    bool is_free(int,int); // проверяет свободна ли клетка
    void add_object(Object*);
    bool is_softly(int,int); // проверяет проходима ли клетка
    void objects_steps(Map&); // Ход всех объектов на карте
    Object* get_object(int);
    Object* find_object(int,int);
    int get_height();
    int get_weidth(int);
    ~Map();
};

#endif // MAP_H

