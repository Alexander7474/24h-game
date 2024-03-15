#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
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

    random_pos_x = rand() % (BBOP_WINDOW_SIZE.x - offsetx*2) + offsetx;
    random_pos_y = rand() % (BBOP_WINDOW_SIZE.y - offsety*2) + offsety;
    obs.setSize(Vector2f(50,50));
    obs.setPosition(Vector2f(random_pos_x, random_pos_y));
    for(int i = 0;i<7; i++)
    {
        std::string pneu_obst = "img/map/obstacles/pneu/" + std::to_string(i) + ".png";
        Texture pneu_ob(pneu_obst.c_str());
        list_pneu.push_back(pneu_ob);
    }
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


void Obstacle::update()
{
    anime_frame ++;
    if (anime_frame >= list_pneu.size()*15) anime_frame = 0;
    obs.setTexture(list_pneu[anime_frame/15]);
}


void Map::update()
{
    for(int i = 0; i < list_obst.size(); i++)
    {
        list_obst[i].update();
    }
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


