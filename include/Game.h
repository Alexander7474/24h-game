#pragma once

#include <BBOP/Graphics/bbopGlobal.h>
#include <BBOP/Graphics/bbopMathClass.h>
#include <BBOP/Graphics/fontsClass.h>
#include <BBOP/Graphics/shapeClass.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <irrKlang/ik_ISoundEngine.h>
#include <vector>

#include "Map.h"
#include "Car.h"
#include "Bot.h"
#include "Gun.h"

class Game : public BbopDrawable 
{
public:
  Game(int n_en, irrklang::ISoundEngine* n_sound, Font &font);

  int update(GLFWwindow *window);
  virtual void Draw(GLint renderModeLoc) const override;
private:
  Map map;
  Bot bot;
  std::vector<Car> cars;
  std::vector<Gun> guns;
  int cars_size;
  irrklang::ISoundEngine * sound;
  int starter;
  TexteBox texte;
  CircleShape triangle;
  int round;
};
