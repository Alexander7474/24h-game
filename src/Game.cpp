#include "../include/Game.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

Game::Game()
  : bot(0)
{
  std::srand(time(NULL));
  for(int i = 0; i< 5 ; i++){
    float speed = 0.1f;
    float life = 100.0f;
    if(i == 0){
      speed = 0.2f;
      life = 200.0f;
    } 
    Car car("img/bleu_car", Vector2f(static_cast<float>(rand()%250),static_cast<float>(rand() %250)), 0.0f, speed, life);
    cars.push_back(car);
  }
}

void Game::Draw(GLint renderModeLoc) const
{
  map.Draw(renderModeLoc);
  for(int i = 0; i < cars.size(); i++)
    cars[i].Draw(renderModeLoc);
}

void Game::update(GLFWwindow *window)
{
  std::cout << cars[0].get_life() << std::endl; 
  // check des touches pour cars[0]
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    cars[0].accelerate();
  }
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    cars[0].decelerate();
  }
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    cars[0].go_right();
  }
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    cars[0].go_left();
  }
  for(int i = 1; i < static_cast<int>(cars.size()); i++){
    bot.play(&cars[i], &cars[0]);
    cars[i].update();
  }
  cars[0].update();
  for(int y = 0; y < static_cast<int>(cars.size()); y++){
    for(int i = 0; i < static_cast<int>(cars.size()); i++){
      if (i!=y){
        Vector2f yPos = cars[y].get_pos();
        Vector2f iPos = cars[i].get_pos();
        float yAngle = atan2(iPos.y-yPos.y, iPos.x-yPos.x);
        while (yAngle > M_PI) yAngle -= 2.0 * M_PI;
        while (yAngle <= -M_PI) yAngle += 2.0 * M_PI;
        yAngle = yAngle-cars[y].get_rotation()-(M_PI/2.0f);
        float iAngle = atan2(yPos.y-iPos.y, yPos.x-iPos.x);
        iAngle = iAngle-cars[i].get_rotation()-(M_PI/2.0f);
        while (iAngle > M_PI) iAngle -= 2.0 * M_PI;
        while (iAngle <= -M_PI) iAngle += 2.0 * M_PI;
        if(cars[y].get_life() > 0.0 && cars[i].get_life() > 0.0){
          std::cout << iAngle << " " << yAngle << std::endl;
          if(cars[y].get_sprite()->getCollisionBox()->check(cars[i].get_sprite()->getCollisionBox())&& glfwGetTime()-cars[y].get_last_hit()>1.5&& glfwGetTime()-cars[i].get_last_hit()>1.5){
            if(std::abs(yAngle) <= 1.0f){
              cars[y].set_speed(Vector2f(-cars[y].get_speed().x*1.2f,-cars[y].get_speed().y*1.2f));
              cars[y].damage(1.0f);
              cars[i].damage(15.0f);
            }
            if(std::abs(iAngle) <= 1.0f ){
              cars[i].set_speed(Vector2f(-cars[i].get_speed().x*1.2f,-cars[i].get_speed().y*1.2f));
              cars[i].damage(1.0f);
              cars[y].damage(10.0f);
            }
          }
        }
      }
    }
  }

}
