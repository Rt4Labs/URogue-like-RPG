#include "map.h"
#include "hero.h"
#include "enemy.h"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void create_someone(Map* m)
{
    Enemy* e = new Enemy;
    m->add_object(e);
}

int main()
{
    //ncurses stuff
    initscr(); // Initialize ncurses
    noecho(); // Don't echo keypress
    curs_set(0); // Invisible cursor
    keypad(stdscr,true);
    start_color();

    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);

    srand(time(NULL));

    Map* m = new Map;
    Hero* h = new Hero(1,1,100,10);
    m->add_object(h);

    for(int i=0;i<5;i++)
    {
        create_someone(m);
    }

    while(true)
    {
        m->print_map();
        m->print_objects();
        m->objects_steps(*m);
    }

    delete h;
    delete m;

    getch();
    endwin(); // End ncurses

    return EXIT_SUCCESS;
}
