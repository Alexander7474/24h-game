#include "../include/Car.h"
#include <BBOP/Graphics/bbopMathClass.h>
#include <string>

#include <iostream>

Car::Car(std::string new_fold_name, Vector2f new_position, float new_rotation, float new_max_speed)
  : fold_name(new_fold_name),
    pos(new_position),
    rotation(new_rotation),
    max_speed(new_max_speed),
    max_speed_reverse(new_max_speed),
    state(0)
{
  int imgn = 100;
  for(int i = 0; i < 4 ; i++){
    if(i == 3)
      imgn = 0;
    std::string filename = fold_name + "/" + std::to_string(imgn) + "/0.png";
    std::cout << filename << std::endl;
    Sprite toadd(Texture(filename.c_str()), pos);
    toadd.setSize(Vector2f(50.0f,50.0f));
    toadd.setOrigin(Vector2f(toadd.getSize().x/2.0f,toadd.getSize().y/2.0f));
    sprites.push_back(toadd);
    imgn = imgn/2;
  }
}

void Car::Draw(GLint renderModLoc) const
{
  sprites[state].Draw(renderModLoc);
}
