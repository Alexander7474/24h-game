#include "../include/Car.h"
#include <BBOP/Graphics/bbopMathClass.h>
#include <cmath>
#include <string>

#include <iostream>

Car::Car(std::string new_fold_name, Vector2f new_position, float new_rotation, float new_max_speed)
  : pos(new_position),
    rotation(new_rotation),
    max_speed(new_max_speed),
    max_speed_reverse(new_max_speed),
    fold_name(new_fold_name),
    state(0),
    deplacement(0.0f,0.0f)
{
  int imgn = 100;
  for(int i = 0; i < 4 ; i++){
    if(i == 3)
      imgn = 0;
    std::string filename = fold_name + "/" + std::to_string(imgn) + "/0.png";
    std::cout << filename << std::endl;
    Sprite toadd(Texture(filename.c_str()), pos);
    toadd.setSize(Vector2f(50.0f,50.0f));
    toadd.setOrigin(Vector2f(toadd.getSize().x/2.0f,toadd.getSize().y/2.0f));
    sprites.push_back(toadd);
    imgn = imgn/2;
  }
}

void Car::accelerate()
{
  float angle = rotation+M_PI/2.0f;
  Vector2f dep(cos(angle),sin(angle));
  speed.x+=dep.x*max_speed;speed.y+=dep.y*max_speed;
  std::cout << speed.x << speed.y << std::endl;
}

void Car::decelerate()
{
  float angle = rotation+M_PI/2.0f;
  Vector2f dep(cos(angle),sin(angle));
  speed.x-=dep.x*max_speed;speed.y-=dep.y*max_speed;
  std::cout << speed.x << speed.y << std::endl;
}

void Car::go_right()
{
  rotation+=0.1f;
}

void Car::go_left()
{
  rotation-=0.1f;
}

void Car::update()
{
  speed.x*=0.95f;speed.y*=0.95f;
  sprites[state].move(speed);
  sprites[state].setRotation(rotation);
}

void Car::Draw(GLint renderModLoc) const
{
  sprites[state].Draw(renderModLoc);
}

Vector2f Car::get_pos()
{
  return pos;
}

float Car::get_rotation()
{
  return rotation;
}
