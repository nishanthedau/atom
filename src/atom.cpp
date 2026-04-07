#include </opt/homebrew/include/GLFW/glfw3.h>
#include </opt/homebrew/include/glm/glm.hpp>
#include </opt/homebrew/include/glm/gtc/matrix_transform.hpp>
#include </opt/homebrew/include/glm/gtc/type_ptr.hpp>
#include </opt/homebrew/opt/glew/include/GL/glew.h>

// #include<GL/glew.h>
// #include<GLFW/glfw3.h>
// #include<glm/glm.hpp>
// #include<glm/gtc/matrix_transform.hpp>
// #include<glm/gtc/type_ptr.hpp>

#include<vector>
#include <iostream>
#include<cmath>
#include <cstdlib>
#include <ctime>

#ifndef value_PI
#define value_PI 3.14159265358979323846
#endif

using namespace glm;
using namespace std;

struct Engine {

    GLFWwindow* window;
    int WIDTH = 800, HEIGHT = 600;

    Engine(){
        if (!glfwInit()){
            cerr << "lmao, failed to initialize it man" << endl;
            exit(EXIT_FAILURE);
        }

        window = glfwCreateWindow(WIDTH, HEIGHT, "simulating atoms", nullptr, nullptr);
        if (!window){
            cerr << "lmao, you even failed in here man" << endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);
        glViewport(0, 0, WIDTH, HEIGHT);
    }
};

Engine engine;

int main(){
    while (!glfwWindowShouldClose(engine.window)){

        glfwSwapBuffers(engine.window);
        glfwPollEvents();
    }
}
