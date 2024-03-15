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
  
  Scene defaultScene;
  Game game(5,SoundEngine);
  ////////////////////////////////////////
  ///End var and obj
  ////////////////////////////////////////

  while(!glfwWindowShouldClose(window)){
    bbopCleanWindow(window, Vector3i(0,0,0), 1.0f);
    ///////////////////////////////////////////////
    ///Game loop start
    ///////////////////////////////////////////////

    defaultScene.Use();
    game.update(window);
    defaultScene.Draw(game);
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
