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
public:
    Obstacle();
    Sprite *get_sprite();
    virtual void Draw(GLint renderModeLoc) const override;


};



class Map:public BbopDrawable
{
private: 
    std::vector<Obstacle>list_obst;
    Sprite map_s;
public:
    Map();
    virtual void Draw(GLint renderModeLoc) const override;

    
    
};
