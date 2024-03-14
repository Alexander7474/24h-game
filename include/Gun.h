#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <cmath>

class Bullet : public BbopDrawable
{
    public:
        Vector2f position;
        float angle_de_tir;
        Vector2f direction;
        float vitesse;
        Sprite bullet;
        Bullet();
        void deplacement();
        void update();
        ~Bullet();
};

class Gun : public BbopDrawable
{
    private:
        int max_capacite;
        int capacite_actuelle;
        float rotation;
        Vector2f position;
        bool shoot;
    
    public:
        Gun();
        Gun(float, Vector2f);
        std::vector<Texture> textures[2];
        std::vector<Bullet> balles;
        Texture base;
        Sprite gun;
        void tirer();
        void recharger();
        void set_rotation(float);
        void set_position(Vector2f);
        float get_rotation();
        Vector2f get_position();
        void update();
        int anim_state = 0;

        void Draw(GLint renderModLoc) const override;

        ~Gun();
};