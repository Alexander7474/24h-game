#include "../include/Car.h"
#include <BBOP/Graphics/bbopMathClass.h>
#include <cmath>
#include <string>

#include <iostream>

Car::Car(std::string new_fold_name, Vector2f new_position, float new_rotation, float new_max_speed)
  : pos(new_position),
    rotation(new_rotation),
    max_speed(new_max_speed),
    max_speed_reverse(new_max_speed/3.0f),
    fold_name(new_fold_name),
    state(0),
    deplacement(0.0f,0.0f),
    anim_state(0),
    sprite("img/bleu_car/100/0.png")
{
  //chargement des Texture
  for(int i = 0; i < 1; i++){
    std::string filename = fold_name + "/100/" + std::to_string(i) + ".png";
    std::cout << filename << std::endl;
    Texture toadd(filename.c_str());
    textures[0].push_back(toadd);
  }
  for(int i = 0; i < 3; i++){
    std::string filename = fold_name + "/50/" + std::to_string(i) + ".png";
    std::cout << filename << std::endl;
    Texture toadd(filename.c_str());
    textures[1].push_back(toadd);
  }
  for(int i = 0; i < 8; i++){
    std::string filename = fold_name + "/25/" + std::to_string(i) + ".png";
    std::cout << filename << std::endl;
    Texture toadd(filename.c_str());
    textures[2].push_back(toadd);
  }
  for(int i = 0; i < 3; i++){
    std::string filename = fold_name + "/0/" + std::to_string(i) + ".png";
    std::cout << filename << std::endl;
    Texture toadd(filename.c_str());
    textures[3].push_back(toadd);
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
  speed.x-=dep.x*max_speed_reverse;speed.y-=dep.y*max_speed_reverse;
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
  anim_state++;
  if(anim_state > textures[state].size())
    anim_state = 0;
  sprite.setTexture(textures[state][anim_state]);
  sprite.setPosition(pos);
  sprite.setRotation(rotation);
}

void Car::Draw(GLint renderModLoc) const
{
  sprite.Draw(renderModLoc);
}

Vector2f Car::get_pos()
{
  return pos;
}

float Car::get_rotation()
{
  return rotation;
}
