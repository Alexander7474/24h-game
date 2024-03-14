#include "../include/Bot.h"
#include <BBOP/Graphics/bbopMathClass.h>

Bot::Bot(std::string fold_name, Vector2f new_pos, float new_max_speed)
  : car(fold_name, new_pos, 0.0f, 0.5f)
{

}

void Bot::update()
{}

void Bot::Draw(GLint renderModeLoc) const
{
  car.Draw(renderModeLoc);
}
