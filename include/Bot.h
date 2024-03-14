#pragma once

#include <BBOP/Graphics/bbopGlobal.h>
#include <BBOP/Graphics/bbopMathClass.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <string>

#include "Car.h"

class Bot : public BbopDrawable
{
private:
  Car car;
public:
  Bot(std::string fold_name, Vector2f new_pos, float new_max_speed);

  Car* get_car();
  void update();
  virtual void Draw(GLint renderModeLoc) const override;
};
