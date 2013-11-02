#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <Thor/Input/ActionMap.hpp>
#include <Thor/Input/EventSystem.hpp>
#include "Cone.hpp"

int main()
{
    const int width = 800;
    const int height = 600;

    Cone cone;

    thor::ActionMap<std::string> actions;
    thor::ActionMap<std::string>::CallbackSystem system;

    actions["close"] = thor::Action(sf::Event::Closed);
    actions["right"] = thor::Action(sf::Keyboard::Right);


    sf::Window window(sf::VideoMode(width, height), "Conic sections", sf::Style::Default, sf::ContextSettings(32));
    window.setFramerateLimit(60);

    system.connect("close", std::bind(&sf::Window::close, &window));

    system.connect("right", [](thor::ActionContext<std::string> context){

    });


    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(-300, 300, -300, 300);
    gluPerspective(120, width / float(height), .1, 500);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0,0,200.,0,0,0,0,1,0);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    while (window.isOpen()){
        actions.update(window);
        actions.invokeCallbacks(system, &window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cone.draw();



        window.display();

    }




    return 0;
}
