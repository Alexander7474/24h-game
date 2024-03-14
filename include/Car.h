#pragma once

#include <BBOP/Graphics/bbopMathClass.h>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>

class Car : public BbopDrawable
{
public:
  Car(std::string new_fold_name, Vector2f new_pos, float new_rotation, float new_max_speed);

  void accelerate();
  void decelerate();
  void go_left();
  void go_right();
  Vector2f get_pos();
  float get_rotation();

  void Draw(GLint renderModLoc) const override;
  void update();
private: 
  std::vector<Sprite> sprites;
  Vector2f pos;
  float rotation;
  Vector2f speed;
  float max_speed;
  float max_speed_reverse;
  std::string fold_name;
  int state;
  Vector2f deplacement;
};
