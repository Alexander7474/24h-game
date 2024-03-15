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
    int x;
    int y;
    int offsetx = 100 ;
    int offsety = 75 ;
    int random_pos_x;
    int random_pos_y;
public:
    Obstacle();
    Sprite *get_sprite();
    virtual void Draw(GLint renderModeLoc) const override;


};


class Box:public BbopDrawable
{
public:
    Box();
    virtual void Draw(GLint renderModeLoc) const override;

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

    
    
};
