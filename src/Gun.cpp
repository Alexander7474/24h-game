#include "../include/Car.h"
#include "../include/Gun.h"

#include <iostream>

Bullet::Bullet(Vector2f pos, float rotate)
    : bullet(Texture("img/bullet/bullet.png"))
{
    position = pos;
    angle_de_tir = rotate + M_PI;
    bullet.setPosition(position);
    bullet.setRotation(angle_de_tir);
    vitesse = 1.0f;
}

Gun::Gun()
    : base("img/gun/gun.png"), gun(Texture("img/gun/gun.png"))
{
    max_capacite = 250;
    capacite_actuelle = 250;
    rotation = 0;
    position = Vector2f(0.0f,0.0f);
    gun.setAlpha(0);
    set_position(position);
    set_rotation(rotation);
    gun.setSize(Vector2f(60.0f, 88.5f));
    gun.setOrigin(Vector2f(60.0f/2, 88.5f/2));

}

Gun::Gun(float gun_rotation, Vector2f gun_position)
  : base("img/gun/gun.png"), gun(Texture("img/gun/gun.png"))
{
    max_capacite = 250;
    capacite_actuelle = 250;
    rotation = gun_rotation;
    position = gun_position;
    gun.setAlpha(0);
    set_position(position);
    set_rotation(rotation);
    gun.setSize(Vector2f(60.0f, 88.5f));
    gun.setOrigin(Vector2f(60.0f/2, 88.5f/2));

    for(int i = 1; i < 7; i++){
        std::string filename = "img/gunshot/gunshot" + std::to_string(i) + ".png";
        std::cout << filename << std::endl;
        Texture toadd(filename.c_str());
        textures[0].push_back(toadd);
    }
    for(int i = 1; i < 7; i++){
        std::string filename = "img/reload/reload" + std::to_string(i) + ".png";
        std::cout << filename << std::endl;
        Texture toadd(filename.c_str());
        textures[1].push_back(toadd);
    }
}

void Gun::set_rotation(float car_rotation){
    rotation = car_rotation;
    gun.setRotation(rotation);
}

void Gun::set_position(Vector2f car_position){
    position = car_position;
    std::cout<<car_position.x<<" "<<car_position.y<<" "<<position.x<<" "<<position.y<< std::endl;
    gun.setPosition(position);
}

float Gun::get_rotation(){
    return(rotation);
}

Vector2f Gun::get_position(){
    return(position);
}

std::vector<Bullet> Gun::get_bullet(){
    return(balles);
}

int Gun::get_capacite_actuelle(){
    return(capacite_actuelle);
}

int Gun::get_max_capacite(){
    return(max_capacite);
}

void Gun::update(Car car){
    set_position(Vector2f(car.get_pos().x - 5.0f, car.get_pos().y + 5.0f));
    set_rotation(car.get_rotation());
    for (int i = 0; i < balles.size(); i++){
        balles[i].update();
    }
}

void Bullet::update(){
    position.x = position.x + direction.x*vitesse;
    position.y = position.y + direction.y*vitesse;
    bullet.setPosition(position);
}

void Gun::animate(int i){
    if (i == 1) gun.setTexture(textures[i][anim_state/3]);
    else gun.setTexture(textures[i][anim_state]);
    if (anim_state == 5){
        anim_state = 0;
        if (i == 1) animated = false;
        if (i == 0) shooted = false;
    }
    else  anim_state ++;
}

void Gun::reload(){ /* INCLURE DANS LE SCRIPT QUI RUN LES TOUCHES
if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
      pistol.reload();
    }
    if (pistol.animated){
      pistol.animate(1);
    }
*/
    capacite_actuelle = max_capacite;
    animated = true;
}

void Gun::shoot(){ /* INCLURE DANS LE SCRIPT QUI RUN LES TOUCHES
if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
      pistol.shoot();
    }
    if (pistol.shooted){
      pistol.animate(0);
    }
*/
    if(capacite_actuelle == 0) return;
    else{
        shooted = true;
        Bullet B(position, rotation);
        B.direction = Vector2f(cos(rotation + M_PI/2.0f), sin(rotation + M_PI/2.0f));
        std::cout << B.direction.x << " " << B.direction.y << std::endl;
        balles.push_back(B);
    }
}

void Bullet::Draw(GLint renderModeLoc) const
{
    bullet.Draw(renderModeLoc);
}

void Gun::Draw(GLint renderModeLoc) const
{
    for (int i = 0; i<balles.size(); i++){
      balles[i].Draw(renderModeLoc);
    }
    gun.Draw(renderModeLoc);
}