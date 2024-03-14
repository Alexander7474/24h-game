#include "../include/Gun.h"

Bullet::Bullet()
    : bullet(Texture("img/bullet/bullet.png"))
{
    vitesse = 5.0f;
    // deplacement cosinus de l'angle * vitesse
}

Gun::Gun()
    : base("img/gun/gun.png"), gun(Texture("img/gun/gun.png"))
{
    max_capacite = 250;
    rotation = 0;
    position = Vector2f(0.0f,0.0f);
    gun.setAlpha(0);
    set_position(position);
    set_rotation(rotation);
    gun.setSize(Vector2f(40.0f, 59.0f));

}

Gun::Gun(float gun_rotation, Vector2f gun_position)
  : base("img/gun/gun.png"), gun(Texture("img/gun/gun.png"))
{
    max_capacite = 250;
    rotation = gun_rotation;
    position = gun_position;
    gun.setAlpha(0);
    set_position(position);
    set_rotation(rotation);
    gun.setSize(Vector2f(40.0f, 59.0f));

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
}

void Gun::tirer(){ // a appeler dans une boucle :
/*
    while ([nom du Gun].anim_state < 6){
        [nom du Gun].tirer();
        [nom de la Scene].Draw([nom du Gun]);
    }
*/
    if (capacite_actuelle == 0) recharger();
    else if (!shoot) {
        capacite_actuelle--; 
        balles[max_capacite-capacite_actuelle].angle_de_tir = rotation;
        balles[max_capacite-capacite_actuelle].position = position;
        shoot = true;
    }
    if (anim_state < 6 && shoot) {
        gun.setTexture(textures[0][anim_state]);
        anim_state++;
        if (anim_state == 2){
            for (int i = 0; i < (max_capacite-capacite_actuelle); i++){
                balles[i].update();
            }
        }
    }
    else{
        anim_state = 0;
        gun.setTexture(base);
        shoot = false;
        exit(1);
    }

    /*
    angle_de_tir = g.get_rotation() + M_PI/2.0f;
    Vector2f dep(cos(angle_de_tir), sin(angle_de_tir));
    direction = dep; // a faire directement dans Gun
    */
    
}

void Gun::recharger(){ // a appeler dans une boucle :
/*
    while ([nom du Gun].anim_state < 6){
        [nom du Gun].recharger();
        [nom de la Scene].Draw([nom du Gun]);
    }
*/
    capacite_actuelle = max_capacite;
    // animation rechargement
    if (anim_state < 6) {
        anim_state++;
        gun.setTexture(textures[1][anim_state]);
    }
    else{
        anim_state = 0;
        gun.setTexture(base);
        exit(1);
    }
}

void Gun::set_rotation(float gun_rotation){
    rotation = gun_rotation;
    gun.setRotation(rotation);
}

void Gun::set_position(Vector2f gun_position){
    position = gun_position;
    gun.setPosition(position);
}

float Gun::get_rotation(){
    return(rotation);
}

Vector2f Gun::get_position(){
    return(position);
}

void Gun::update(){
    set_position(position);
    set_rotation(rotation);
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

Gun::~Gun(){}

Bullet::~Bullet(){}