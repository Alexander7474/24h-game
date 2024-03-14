/////////////////////////////
//GAME SKELETON
/////////////////////////////
#include <BBOP/Graphics/sceneClass.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <BBOP/Graphics.h>
#include <irrKlang/irrKlang.h>

#include "include/Car.h"

int main () {
  GLFWwindow *window;
  bbopInit(1920, 1080, "24h game", window);
  ////////////////////////////////////////
  ///Game var and obj
  ////////////////////////////////////////
  
  Scene defaultScene;

  Car test("img/", Vector2f(0.0f,0.0f), 0.0f, 50.0f);
  

  ////////////////////////////////////////
  ///End var and obj
  ////////////////////////////////////////

  while(glfwWindowShouldClose(window)){
    bbopCleanWindow(window, Vector3i(0,0,0), 1.0f);
    ///////////////////////////////////////////////
    ///Game loop start
    ///////////////////////////////////////////////

    defaultScene.Use();
    defaultScene.Draw(test);

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
