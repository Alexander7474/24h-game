#pragma once

#include <BBOP/Graphics/bbopGlobal.h>
#include <BBOP/Graphics/bbopMathClass.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <string>

#include "Car.h"

class Bot
{
private:
  int diff_level;
public:
  Bot(int new_diff_level);

  void play(Car *car, Car *player);
};
