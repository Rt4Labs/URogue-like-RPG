#include "enemy.h"
#include "map.h"

using namespace std;

pair <int,int> Enemy::restore_way(vector<vector<point>>& map,pair<int,int> start,pair<int,int> now)
{
    if(map[now.first][now.second].last==start)
    {
        return now;
    }
    else
    {
        return restore_way(map,start,map[now.first][now.second].last);
    }
}

bool Enemy::whether_checked(vector<vector<point>>& map, int x,int y)
{
    if( (x > -1 && x < map.size() ) && ( y >-1 && y < map.at(x).size() && map[x][y].cost == 0) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void Enemy::check_point(vector<vector<point>>& map,queue<pair<int,int>> & testable_points,pair<int,int> now)
{
    int x = now.first;
    int y = now.second;

    if(whether_checked(map,x,y))
    {
        pair<int,int> last(testable_points.front());
        map[x][y].cost=map[x][y].cost+1;
        map[x][y].last=last;
        testable_points.push(now);
    }
}

void Enemy::check_area(vector<vector<point>>& map,queue<pair<int,int>> & testable_points)
{
    int x = testable_points.front().first;
    int y = testable_points.front().second;
    check_point(map,testable_points,pair<int,int>(x+1,y));
    check_point(map,testable_points,pair<int,int>(x-1,y));
    check_point(map,testable_points,pair<int,int>(x,y+1));
    check_point(map,testable_points,pair<int,int>(x,y-1));
}



pair<int,int> Enemy::find_way(vector<vector<point>> map,queue<pair<int,int>>& testable_points,pair<int,int> start,pair<int,int> finish)
{
    pair<int,int> now(testable_points.front());

    if(now.first == finish.first && now.second == finish.second)
    {
        return restore_way(map,start,now);
    }
    else
    {
        check_area(map,testable_points);
        testable_points.pop();
        return find_way(map,testable_points,start,finish);
    }
}

vector<vector<Enemy::point>> Enemy::get_terrain_map(Map m)
{
    vector<vector<point>> terrain_map;

    for(int i=0;i<m.get_height();i++)
    {
        terrain_map.push_back( vector<point>(m.get_weidth(i)) );
        for(int j=0;j<m.get_weidth(i);j++)
        {
            if(m.is_softly(i,j))
            {
                terrain_map[i][j].cost=0;
            }
            else
            {
                terrain_map[i][j].cost=-1;
            }
        }
    }

    terrain_map[x][y].cost=1;

    return terrain_map;
}

pair<int,int> Enemy::get_way(Map m,pair<int,int> finish)
{
    queue<pair<int,int>> testable_points;
    testable_points.push(pair<int,int> (x,y)); // Добавление точки начала обхода

    return find_way(get_terrain_map(m),testable_points,testable_points.front(),finish);
}
