#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <Thor/Input/ActionMap.hpp>
#include <Thor/Input/EventSystem.hpp>
#include "math.h"
#include <cmath>
#include <iostream>

int main()
{
    const float width = 800.f;
    const float height = 600.f;

    thor::ActionMap<std::string> actions;
    thor::ActionMap<std::string>::CallbackSystem system;

    actions["close"] = thor::Action(sf::Event::Closed);
    actions["right"] = thor::Action(sf::Keyboard::Right);


    sf::Window window(sf::VideoMode(width, height), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    //window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    system.connect("close", std::bind(&sf::Window::close, &window));

    system.connect("right", [](thor::ActionContext<std::string> context){

    });

    float h = 240.f;
    float r = 200.f;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(-300, 300, -300, 300);
    gluPerspective(120, width / float(height), .1, 500);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0,0,200.,0,0,0,0,1,0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_POINTS);

    glColor3f(0,255,0);

    for (int i = 0; i<h; ++i){
        for (int j=0; j<360; ++j){
            float angle = j*M_PI/180;
            float x = ((h - i) / h) * r * std::cos(angle);
            float y = h - i;
            float z = ((h - i) / h) * r * std::sin(angle);
//            std::cout << "Height: " << i << ", "
//                      << "Angle: "  << angle << ", "
//                      << "Coords: " << x << ", " << y << ", " << z << std::endl;
            glVertex3f(x,y,z);
        }
    }




    glEnd();

    window.display();

    while (window.isOpen()){
        actions.update(window);
        actions.invokeCallbacks(system, &window);



    }




    return 0;
}
