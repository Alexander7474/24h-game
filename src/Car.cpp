#include "../include/Car.h"
#include <BBOP/Graphics/bbopMathClass.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string>

#include <iostream>

Car::Car(std::string new_fold_name, Vector2f new_position, float new_rotation, float new_max_speed, float new_life)
  : pos(new_position),
    rotation(new_rotation),
    max_speed(new_max_speed),
    max_speed_reverse(new_max_speed/3.0f),
    fold_name(new_fold_name),
    state(0),
    deplacement(0.0f,0.0f),
    anim_state(0),
    sprite("img/bleu_car/100/0.png"),
    life(new_life),
    last_hit(glfwGetTime())
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
    std::string filename = fold_name + "/10/" + std::to_string(i) + ".png";
    std::cout << filename << std::endl;
    Texture toadd(filename.c_str());
    textures[3].push_back(toadd);
  }
  for(int i = 0; i < 1; i++){
    std::string filename = fold_name + "/0/" + std::to_string(i) + ".png";
    std::cout << filename << std::endl;
    Texture toadd(filename.c_str());
    textures[4].push_back(toadd);
  }
  sprite.setSize(Vector2f(50.0f,50.0f));
  sprite.setOrigin(Vector2f(sprite.getSize().x/2.0f,sprite.getSize().y/2.0f));
  sprite.setPosition(pos);
  sprite.setColor(Vector3i(500,500,500));
}

void Car::accelerate()
{
  if(state != 4){
    float angle = rotation+M_PI/2.0f;
    Vector2f dep(cos(angle),sin(angle));
    speed.x+=dep.x*max_speed;speed.y+=dep.y*max_speed;
  }
}

void Car::decelerate()
{
  if(state != 4){
    float angle = rotation+M_PI/2.0f;
    Vector2f dep(cos(angle),sin(angle));
    speed.x-=dep.x*max_speed_reverse;speed.y-=dep.y*max_speed_reverse;
  }
}

void Car::go_right()
{
  if(state !=4)
    rotation+=max_speed/2.0f;
}

void Car::go_left()
{
  if(state != 4)
    rotation-=max_speed/2.0f;
}

void Car::update()
{

  if(life > 50.0f){
    state = 0;
  }else if(life > 25.0f){
    state = 1;
  }else if(life > 10.0f){
    state = 2;
  }else if(life > 0.0f){
    state = 3;
  }else {
    state = 4;
  }
  speed.x*=0.95f;speed.y*=0.95f;
  anim_state++;
  sprite.move(speed);
  pos = sprite.getPosition();
  if(anim_state >= static_cast<int>(textures[state].size()*7))
    anim_state = 0;
  if(glfwGetTime()-last_hit<1.5f && sprite.getRGBFilterState()){
    sprite.setRGBFilterState(false);
  }else if(glfwGetTime()-last_hit<1.5f && !sprite.getRGBFilterState()){
    sprite.setRGBFilterState(true);
  }else {
    sprite.setRGBFilterState(false);
  }
  sprite.setTexture(textures[state][anim_state/7]);
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

void Car::set_state(int new_state)
{
  state = new_state;
}

int Car::get_state()
{
  return state;
}

Sprite* Car::get_sprite()
{
  return &sprite; 
}

void Car::move(Vector2f mv)
{
  speed.x+=mv.x;speed.y+=mv.y;
}

Vector2f Car::get_speed()
{
  return speed;
}

void Car::set_speed(Vector2f new_speed)
{
  speed = new_speed;
}

void Car::damage(float n)
{
  life-=n;
  last_hit = glfwGetTime();
}

float Car::get_life()
{
  return life;
}

double Car::get_last_hit()
{
  return last_hit;
}
