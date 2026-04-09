#include </opt/homebrew/include/GLFW/glfw3.h>
#include </opt/homebrew/include/glm/glm.hpp>
#include </opt/homebrew/include/glm/gtc/matrix_transform.hpp>
#include </opt/homebrew/include/glm/gtc/type_ptr.hpp>
// #include </opt/homebrew/opt/glew/include/GL/glew.h>

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

float orbitDistance = 50.0f;

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
    void run() {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        double halfWidth = WIDTH / 2.0f, halfHeight = HEIGHT / 2.0f;
        glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0, 1.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
};
Engine engine;

struct Particle{
    vec2 position;
    int charge;
    float angle;
    Particle(vec2 position, int charge) : position(position), charge(charge){}

    void draw(int segments = 50){
        
        // for outline circle of electron
        // check tis, there is a bug where it makes a huge cirlce instead of jst outline,
        // if (charge == -1){
        //     glLineWidth(0.4f);
        //     glBegin(GL_TRIANGLE_FAN);
        //     glColor3f(0.4f,0.4f,0.4f);
        //     glVertex2f(position.x, position.y);
        //     for(int i =0; i <= segments; i++){
        //         float angle = 2.0f * value_PI * i / segments;
        //         float x = cos(angle) * orbitDistance;
        //         float y = sin(angle) * orbitDistance;
        //         glVertex2f(x + position.x, y + position.y);
        //     }
        //     glEnd();
        // }

        float r;
        if (charge == -1){
            r = 2;
            glColor3f(0.0f, 1.0f, 1.0f);
        }
        else if (charge == 1){
            r = 10;
            glColor3f(1.0f,0.0f,0.0f);
        }
        else {
            glColor3f(0.5f,0.5f,0.5f);
        }

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(position.x, position.y);
        for(int i =0; i <= segments; i++){
            float angle = 2.0f * value_PI * i / segments;
            float x = cos(angle) * r;
            float y = sin(angle) * r;
            glVertex2f(x + position.x, y + position.y);
        }
        glEnd();
    }
    void update(){
        angle += 0.1;
        position = vec2(cos(angle) * orbitDistance, sin(angle) * orbitDistance);
    }
};


struct Atom{
    vec2 pos;
    vector<Particle> particles{
        Particle(pos,1),
        Particle(pos,-1)
    };
    Atom(vec2 pos) : pos(pos){}
};

vector<Atom> atoms{
    Atom(vec2(0.0f)),
    Atom(vec2(-200.0f,0.0f))
};

int main(){
    while (!glfwWindowShouldClose(engine.window)){
        engine.run();
        // here & is imp cuz we want the same to be updated and not a copy of it
        for (Atom &a : atoms){
            for (Particle &p : a.particles){
                p.draw();
                if (p.charge == -1){
                    p.update();
                }
            }
        }
        glfwSwapBuffers(engine.window);
        glfwPollEvents();
    }
}
