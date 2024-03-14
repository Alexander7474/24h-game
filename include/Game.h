#pragma once

#include <BBOP/Graphics/bbopGlobal.h>
#include <BBOP/Graphics/bbopMathClass.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <vector>

#include "Map.h"
#include "Car.h"
#include "Bot.h"

class Game : public BbopDrawable 
{
public:
  Game();

  void update(GLFWwindow *window);
  virtual void Draw(GLint renderModeLoc) const override;
private:
  Map map;
  Car player;
  std::vector<Bot> bots;
};
