#include "../include/Bot.h"
#include <BBOP/Graphics/bbopMathClass.h>
#include <GLFW/glfw3.h>
#include <cmath>
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
  if(glfwGetTime()-car->get_last_hit()>1.1)
    car->accelerate();
  else
   car->decelerate();
  float dist = sqrt(pow(playerPos.x-carPos.x, 2)+pow(playerPos.y-carPos.y, 2));
  if(dist > 200.0 && car->get_life() > 0.0f)
    gun->shoot(sound);
}
