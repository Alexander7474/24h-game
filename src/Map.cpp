#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <irrKlang/irrKlang.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "../include/Map.h"

static bool initialized = false;

Obstacle::Obstacle()
    : obs(Texture("img/map/obstacles/0.png"))
{
    if (!initialized) {
        std::srand(time(NULL));
        initialized = true;
    }
    std::string find_obs = "img/map/obstacles/"+ std::to_string(rand()%5) + ".png";
    obs.setTexture(Texture(find_obs.c_str()));
    random_pos_x = rand() % (BBOP_WINDOW_SIZE.x - offsetx*2) + offsetx;
    random_pos_y = rand() % (BBOP_WINDOW_SIZE.y - offsety*2) + offsety;
    obs.setSize(Vector2f(50,50));
    std::cout << find_obs << std::endl;
    obs.setPosition(Vector2f(random_pos_x, random_pos_y));
}


Sprite *Obstacle::get_sprite() 
{
    return &obs;
} 

Map::Map()
  : map_s(Texture("img/map/map.png"))
{
    int random_number = rand() % 5 + 5; 
    for (int i = 0; i < random_number; i++)
    {
        Obstacle ob;
        list_obst.push_back(ob);
    }

    map_s.setSize(Vector2f(BBOP_WINDOW_SIZE.x, BBOP_WINDOW_SIZE.y));




}

std::vector<Obstacle> Map::get_obst()
{
    return list_obst;
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


