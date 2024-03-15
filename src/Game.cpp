#include "../include/Game.h"
#include <GLFW/glfw3.h>
#include <iostream>

Game::Game()
  : player("img/bleu_car", Vector2f(100.0f,100.0f), 0.0f, 0.2f),
    bot(0)
{
  Car bot("img/bleu_car", Vector2f(250.0f,250.0f), 0.0f, 0.2f);
  bots.push_back(bot);
}

void Game::Draw(GLint renderModeLoc) const
{
  map.Draw(renderModeLoc);
  player.Draw(renderModeLoc);
  for(int i = 0; i < bots.size(); i++)
    bots[i].Draw(renderModeLoc);
}

void Game::update(GLFWwindow *window)
{
  std::cout << player.get_life() << std::endl; 
  // check des touches pour player
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    player.accelerate();
  }
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    player.decelerate();
  }
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    player.go_right();
  }
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    player.go_left();
  }
  for(int i = 0; i < bots.size(); i++){
    Vector2f carPos = bots[i].get_pos();
    Vector2f playerPos = player.get_pos();
    float botAngle = atan2(playerPos.y-carPos.y, playerPos.x-carPos.x);
    while (botAngle > M_PI) botAngle -= 2.0 * M_PI;
    while (botAngle <= -M_PI) botAngle += 2.0 * M_PI;
    botAngle = botAngle-bots[i].get_rotation()-(M_PI/2.0f);
    float playerAngle = atan2(playerPos.y-carPos.y, playerPos.x-carPos.x);
    playerAngle = playerAngle-player.get_rotation()+(M_PI/2.0f);
    while (playerAngle > M_PI) playerAngle -= 2.0 * M_PI;
    while (playerAngle <= -M_PI) playerAngle += 2.0 * M_PI;
    if(player.get_sprite()->getCollisionBox()->check(bots[i].get_sprite()->getCollisionBox())&& glfwGetTime()-player.get_last_hit()>1.5&& glfwGetTime()-bots[i].get_last_hit()>1.5){
      std::cout << std::abs(playerAngle) << "  " << std::abs(botAngle) << std::endl;
      if(std::abs(playerAngle) <= 1.0f){
        player.set_speed(Vector2f(-player.get_speed().x,-player.get_speed().y));
        bots[i].damage(15.0f);
      }
      if(std::abs(botAngle) <= 1.0f ){
        bots[i].set_speed(Vector2f(-bots[i].get_speed().x*1.2f,-bots[i].get_speed().y*1.2f));
        player.damage(10.0f);
      }
    }
  }
  for(int i = 0; i < bots.size(); i++){
    bot.play(&bots[i], &player);
    bots[i].update();
  }
  player.update();
}
