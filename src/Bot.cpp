#include "../include/Bot.h"
#include <BBOP/Graphics/bbopMathClass.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <irrKlang/ik_ISoundEngine.h>

Bot::Bot(int new_diff_level)
  : diff_level(new_diff_level)
{
  
}

void Bot::play(Car *car, Gun *gun, Car *player, irrklang::ISoundEngine* sound)
{
  Vector2f carPos = car->get_pos();
  Vector2f playerPos = player->get_pos();
  float angle = atan2(playerPos.y-carPos.y, playerPos.x-carPos.x);
  angle = angle-car->get_rotation()-(M_PI/2.0f);
  while (angle > M_PI) angle -= 2.0 * M_PI;
  while (angle <= -M_PI) angle += 2.0 * M_PI;
  if(angle < 0.0f)
    car->go_left();
  if(angle >= 0.0f)
    car->go_right();
  if(glfwGetTime()-car->get_last_hit()>1.1){
    int r = rand()%4;
    switch(r){
      case 0:
        car->accelerate();car->accelerate();
        break;
      case 1:
        car->accelerate();
        break;
    }
  }else{
    int r = rand()%2;
    switch(r){
      case 0:
        car->accelerate();car->accelerate();
        break;
      case 1:
        car->decelerate();
        break;
     }
  }
  float dist = sqrt(pow(playerPos.x-carPos.x, 2)+pow(playerPos.y-carPos.y, 2));
  if(dist > 200.0 && car->get_life() > 0.0f){
    int r = rand()%3;
    if(r==2)
      gun->shoot(sound);
  }
}
