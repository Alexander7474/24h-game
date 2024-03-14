#include "../include/Game.h"
#include <GLFW/glfw3.h>

Game::Game()
  : player("img/bleu_car", Vector2f(100.0f,100.0f), 0.0f, 0.5f)
{
  Bot bot("img/bleu_car", Vector2f(250.0f,250.0f), 0.5f);
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
  player.update();
}
