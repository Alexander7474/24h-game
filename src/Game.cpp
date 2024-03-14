#include "../include/Game.h"

Game::Game()
  : car("img/bleu_car", Vector2f(100.0f,100.0f), 0.0f, 0.5f)
{
  Bot bot("img/bleu_car", Vector2f(250.0f,250.0f), 0.5f);
  bots.push_back(bot);
}

void Game::Draw(GLint renderModeLoc) const
{
  map.Draw(renderModeLoc);
  car.Draw(renderModeLoc);
  for(int i = 0; i < bots.size(); i++)
    bots[i].Draw(renderModeLoc);
}

void Game::update()
{
  
}
