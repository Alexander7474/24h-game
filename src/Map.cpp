#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <irrKlang/irrKlang.h>
#include <vector>

#include "../include/Map.h"

Obstacle::Obstacle()
    : obs(Texture("img/map/obstacle/obs.png"))
{
    
}


Sprite *Obstacle::get_sprite() 
{
    return &obs;
}

Map::Map()
  : map_s(Texture("img/map/map.png"))
{
    std::srand(time(NULL));
    int random_number = rand() % 20 + 1; 
    for (int i = 0; i < random_number; i++)
    {
        Obstacle ob;
        list_obst.push_back(ob);
    }

    map_s.setSize(Vector2f(BBOP_WINDOW_SIZE.x, BBOP_WINDOW_SIZE.y));

}

void Obstacle::Draw(GLint renderModeLoc) const
{
    obs.Draw(renderModeLoc);
}

void Map::Draw(GLint renderModeLoc) const
{
    map_s.Draw(renderModeLoc);
    for(int i = 0; i < list_obst.size(); i++)
    {
        list_obst[i].Draw(renderModeLoc);
    }
}

