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

int main () {
  GLFWwindow *window;
  bbopInit(720, 480, "24h game", window);
  ////////////////////////////////////////
  ///Game var and obj
  ////////////////////////////////////////
  
  Scene defaultScene;
  Game game;
  ////////////////////////////////////////
  ///End var and obj
  ////////////////////////////////////////

  while(!glfwWindowShouldClose(window)){
    bbopCleanWindow(window, Vector3i(0,0,0), 1.0f);
    ///////////////////////////////////////////////
    ///Game loop start
    ///////////////////////////////////////////////

    defaultScene.Use();
    game.update();
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
