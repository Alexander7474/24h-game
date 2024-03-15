#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <cmath>
#include <irrKlang/ik_ISoundEngine.h>
#include "Car.h"

class Bullet : public BbopDrawable
{
    public:
        Vector2f position;
        float angle_de_tir;
        Vector2f direction;
        float vitesse;
        Sprite bullet;
        Bullet();
        Bullet(Vector2f, float, Vector2f);
        void update();

        void Draw(GLint renderModeLoc) const override;
};

class Gun : public BbopDrawable
{
    private:
        int max_capacite;
        int capacite_actuelle;
        float rotation;
        Vector2f position;
        double last_shoot;
    
    public:
        Gun();
        Gun(float, Vector2f);
        std::vector<Texture> textures[2];
        std::vector<Bullet> balles;
        Texture base;
        Sprite gun;
        void set_rotation(float);
        void set_position(Vector2f);
        float get_rotation();
        Vector2f get_position();
        int get_capacite_actuelle();
        int get_max_capacite();
        std::vector<Bullet> get_bullet();
        void update(Car);
        void animate(int);
        bool animated;
        bool shooted;
        void reload();
        void shoot(irrklang::ISoundEngine* sound);
        int anim_state = 0;

        void Draw(GLint renderModeLoc) const override;
};
