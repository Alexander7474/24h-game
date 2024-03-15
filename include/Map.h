#pragma once 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <irrKlang/irrKlang.h>
#include <vector>



class Obstacle:public BbopDrawable
{
private:
    Sprite obs;
    std::vector<Texture>list_pneu;
    int x;
    int y;
    int offsetx = 100 ;
    int offsety = 75 ;
    int random_pos_x;
    int random_pos_y;
    int anime_frame;
public:
    Obstacle();
    Sprite *get_sprite();
    virtual void Draw(GLint renderModeLoc) const override;
    void update();


};


class Map:public BbopDrawable
{
private: 
    std::vector<Obstacle>list_obst;
    Sprite map_s;
public:
    Map();
    std::vector<Obstacle>get_obst();
    virtual void Draw(GLint renderModeLoc) const override;
    void update();
    

    
    
};
