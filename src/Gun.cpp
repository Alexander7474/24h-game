#include "../include/Car.h"
#include "../include/Gun.h"

Bullet::Bullet()
    : bullet(Texture("img/bullet/bullet.png"))
{
    vitesse = 5.0f;
    // set update
    // A AMELIORER
}

Gun::Gun()
    : base("img/gun/gun.png"), gun(Texture("img/gun/gun.png"))
{
    max_capacite = 250;
    capacite_actuelle = 250;
    rotation = 0;
    position = Vector2f(0.0f,0.0f);
    shoot = false;
    gun.setAlpha(0);
    set_position(position);
    set_rotation(rotation);
    gun.setSize(Vector2f(40.0f, 59.0f));
    gun.setOrigin(Vector2f(20.0f, 59.0f/2));

}

Gun::Gun(float gun_rotation, Vector2f gun_position)
  : base("img/gun/gun.png"), gun(Texture("img/gun/gun.png"))
{
    max_capacite = 250;
    capacite_actuelle = 250;
    rotation = gun_rotation;
    position = gun_position;
    shoot = false;
    gun.setAlpha(0);
    set_position(position);
    set_rotation(rotation);
    gun.setSize(Vector2f(40.0f, 59.0f));
    gun.setOrigin(Vector2f(20.0f, 59.0f/2));

    for(int i = 0; i < 6; i++){
        std::string filename = "/img/gunshot/gunshot" + std::to_string(i) + ".png";
        std::cout << filename << std::endl;
        Texture toadd(filename.c_str());
        textures[0].push_back(toadd);
    }
    for(int i = 0; i < 6; i++){
        std::string filename = "/img/reload/reload" + std::to_string(i) + ".png";
        std::cout << filename << std::endl;
        Texture toadd(filename.c_str());
        textures[1].push_back(toadd);
    }
}

void Bullet::deplacement(){
    bullet.move(Vector2f(vitesse, vitesse));
    position.x = position.x + vitesse;
    position.y = position.y + vitesse;
}

void Gun::tirer(){
/*
    while ([nom du Gun].anim_state < 6){
        [nom du Gun].tirer();
        [nom de la Scene].Draw([nom du Gun]);
    }
*/
    if (capacite_actuelle == 0) {
        recharger();        
    }
    else if (!shoot) {
        capacite_actuelle--; 
        balles[max_capacite-capacite_actuelle].angle_de_tir = rotation;
        balles[max_capacite-capacite_actuelle].position = position;
        balles[max_capacite-capacite_actuelle].bullet.setPosition(position);
        balles[max_capacite-capacite_actuelle].bullet.setRotation(rotation);
        shoot = true;
    }
    if (anim_state < 6 && shoot) {
        gun.setTexture(textures[0][anim_state]);
        if (anim_state == 2){
            for (int i = 0; i < (max_capacite-capacite_actuelle); i++){
                balles[i].angle_de_tir = get_rotation() + M_PI/2.0f;
                balles[i].direction = Vector2f(cos(balles[i].angle_de_tir), sin(balles[i].angle_de_tir));
                balles[i].update();
            }
        }
        anim_state++;
    }
    else{
        anim_state = 0;
        gun.setTexture(base);
        shoot = false;
        return;
    }
    
}

void Gun::recharger(){
    // animation rechargement
    if (anim_state < 6){
        anim_state++;
        gun.setTexture(textures[1][anim_state]);
    }
    else{
        gun.setTexture(base);
        capacite_actuelle = max_capacite;
        anim_state = 0;
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

void Gun::update(Car car){
    set_position(car.get_pos());
    set_rotation(car.get_rotation());
    for (int i = 0; i < (max_capacite - capacite_actuelle); i++){
        balles[i].update();
    }
}

void Bullet::update(){
    deplacement();
}

void Bullet::Draw(GLint renderModeLoc) const
{
    bullet.Draw(renderModeLoc);
}

void Gun::Draw(GLint renderModeLoc) const
{
  gun.Draw(renderModeLoc);
}