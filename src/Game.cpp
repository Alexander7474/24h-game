#include "../include/Game.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <irrKlang/ik_ISoundEngine.h>
#include <iterator>
#include <random>
#include <string>

Game::Game(int n_en, irrklang::ISoundEngine* n_sound, Font &font)
  : bot(0),
    cars_size(n_en),
    sound(n_sound),
    starter(300),
    texte("test",&font),
    triangle(3,15.0f),
    round(n_en-1)
{
  texte.setPosition(Vector2f(350.0f,200.0f));
  triangle.setRotation(M_PI/2.0f);
  triangle.setOrigin(Vector2f(50.0f,15.0f));
  std::srand(time(NULL));
  for(int i = 0; i< cars_size ; i++){
    float speed = 0.15f;
    float life = 100.0f;
    std::string carfile = "img/bleu_car";
    if(i == 0){
      speed = 0.2f;
      life = 100.0f;
      carfile = "img/red_car";
    } 
    Car car(carfile.c_str(), Vector2f(static_cast<float>(rand()%550)+100.0f,static_cast<float>(rand() %300)+100.0f), 0.0f, speed, life);
    cars.push_back(car);
    Gun gun(0.0f, car.get_pos());
    guns.push_back(gun);
  }
}

void Game::Draw(GLint renderModeLoc) const
{
  map.Draw(renderModeLoc);
  for(int i = cars_size-1; i >= 0; i--){
    cars[i].Draw(renderModeLoc);
    guns[i].Draw(renderModeLoc);
  }
  if(starter > 0){
    triangle.Draw(renderModeLoc);
    texte.Draw(renderModeLoc);
  }
  if(starter == -100){
    texte.Draw(renderModeLoc);
  }
}

int Game::update(GLFWwindow *window)
{
  if(cars[0].get_life() <= 0.0f){
    texte.setPosition(Vector2f(275.0f,200.0f));
    texte.setTexte("Game over");
    starter = -100;
    return round-1;
  }
  if(starter > 0){
    triangle.setPosition(cars[0].get_pos());
    starter--;
    std::string timer = std::to_string(starter/60);
    texte.setTexte(timer.c_str());
    return 0;
  }
  // check des touches pour cars[0]
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    cars[0].accelerate();
  }
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    cars[0].decelerate();
  }
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    cars[0].go_right();
  }
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    cars[0].go_left();
  }
  if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
    guns[0].shoot(sound);
  }
  if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
    guns[0].reload();
  }
  int total_dead = 0;
  for(int i = 1; i < cars_size; i++){
    int car1 = i;int car2 = i+1;
    if(car2 >= cars_size)
      car2 = 0;
    int cpt = 0;
    while(cars[car2].get_life() <= 0.0f){
      car2++;
      if(car2 >= cars_size)
        car2 = 0;
      if(cpt > cars_size)
        exit(0);
    }
    if(cars[i].get_life() <= 0.0f)
      total_dead++;
    bot.play(&cars[car1], &guns[car1], &cars[car2], sound);
    cars[car1].update();
    guns[car1].update(cars[car1]);
  }
  if(total_dead == cars_size-1)
    return round+1;
  cars[0].update();
  guns[0].update(cars[0]);
  for(int y = 0; y < cars_size; y++){
    for(int i = 0; i < cars_size; i++){
      if (i!=y){
        Vector2f yPos = cars[y].get_pos();
        Vector2f iPos = cars[i].get_pos();
        float yAngle = atan2(iPos.y-yPos.y, iPos.x-yPos.x);
        while (yAngle > M_PI) yAngle -= 2.0 * M_PI;
        while (yAngle <= -M_PI) yAngle += 2.0 * M_PI;
        yAngle = yAngle-cars[y].get_rotation()-(M_PI/2.0f);
        float iAngle = atan2(yPos.y-iPos.y, yPos.x-iPos.x);
        iAngle = iAngle-cars[i].get_rotation()-(M_PI/2.0f);
        while (iAngle > M_PI) iAngle -= 2.0 * M_PI;
        while (iAngle <= -M_PI) iAngle += 2.0 * M_PI;
        //std::cout << iAngle << " " << yAngle << std::endl;
        if(cars[y].get_life() > 0.0 && cars[i].get_life() > 0.0){
          if(cars[y].get_sprite()->getCollisionBox()->check(cars[i].get_sprite()->getCollisionBox())&& glfwGetTime()-cars[y].get_last_hit()>1.1&& glfwGetTime()-cars[i].get_last_hit()>1.1){
            sound->play2D("Musique/metal.wav", false);
            if(std::abs(yAngle) <= 1.0f){
              cars[y].set_speed(Vector2f(-cars[y].get_speed().x*1.2f,-cars[y].get_speed().y*1.2f));
              cars[y].damage(1.0f);
              cars[i].damage(15.0f);
            }
            if(std::abs(iAngle) <= 1.0f ){
              cars[i].set_speed(Vector2f(-cars[i].get_speed().x*1.2f,-cars[i].get_speed().y*1.2f));
              cars[i].damage(1.0f);
              cars[y].damage(10.0f);
            }
          }
        }
        for(int b = 0; b < guns[y].balles.size() ; b++){
          if(guns[y].balles[b].bullet.getCollisionBox()->checkWithRotation(cars[i].get_sprite()->getCollisionBox())){
            guns[y].balles.erase(guns[y].balles.begin()+b);
            cars[i].damage(1.0);
          }
        }
      }
    }
    if (cars[y].get_pos().x > 640.0f)
      cars[y].set_speed(Vector2f(-1.0f,0.0f));
    if(cars[y].get_pos().y > 415.0f)
      cars[y].set_speed(Vector2f(0.0f,-1.0f));
    if (cars[y].get_pos().x < 85.0f)
      cars[y].set_speed(Vector2f(1.0f,0.0f));
    if(cars[y].get_pos().y < 90.0f)
      cars[y].set_speed(Vector2f(0.0f,1.0f));
  }
  return 0;
}
