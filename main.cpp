/////////////////////////////
//GAME SKELETON
/////////////////////////////
#include <BBOP/Graphics/bbopMathClass.h>
#include <BBOP/Graphics/sceneClass.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <irrKlang/irrKlang.h>

#include "include/Game.h"

using namespace irrklang;

int main () {
  GLFWwindow *window;
  bbopInit(720, 480, "24h game", window);

  ISoundEngine *SoundEngine = createIrrKlangDevice();
  SoundEngine->addSoundSourceFromFile("Musique/24h-pour-coder.wav", ESM_AUTO_DETECT, true);
  SoundEngine->addSoundSourceFromFile("Musique/metal.wav", ESM_AUTO_DETECT, true);
  SoundEngine->addSoundSourceFromFile("Musique/pistol.wav", ESM_AUTO_DETECT, true);
  SoundEngine->play2D("Musique/24h-pour-coder.wav", true);
  ////////////////////////////////////////
  ///Game var and obj
  ////////////////////////////////////////


  Sprite menu(Texture("img/menu/menu.png"));
  Sprite bouton_menu(Texture("img/menu/play_buton/0.png"));
  bouton_menu.setPosition(Vector2f(BBOP_WINDOW_SIZE.x/3, BBOP_WINDOW_SIZE.y/2.1));

  bool is_playing = false;
  int cpt_frame=20;
  
  Scene defaultScene;
  Font font(48, "fonts/arial.ttf");
  Game game(5,SoundEngine,font);
  ////////////////////////////////////////
  ///End var and obj
  ////////////////////////////////////////

  while(!glfwWindowShouldClose(window)){
    bbopCleanWindow(window, Vector3i(0,0,0), 1.0f);
    ///////////////////////////////////////////////
    ///Game loop start
    ///////////////////////////////////////////////

    defaultScene.Use();

    if(!is_playing)
    {
      if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      {
        bouton_menu.setTexture(Texture("img/menu/play_buton/1.png"));
        cpt_frame--;
      }
      if(cpt_frame < 20){
        cpt_frame--;
      }
      if(cpt_frame == 0){
        is_playing = true;
      }

      defaultScene.Draw(menu);
      defaultScene.Draw(bouton_menu);
    }

    else
    {
      game.update(window);
      defaultScene.Draw(game);
    }
    
    ///////////////////////////////////////////////
    ///Game loop end
    ///////////////////////////////////////////////

    bbopErrorCheck();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
