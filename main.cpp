#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <Thor/Input/ActionMap.hpp>
#include <Thor/Input/EventSystem.hpp>
#include "Cone.hpp"
#include "Conic.hpp"
//#include <Thor/Vectors/VectorAlgebra3D.hpp>

struct Camera{
    sf::Vector3f eye;
    sf::Vector3f lookAt;
    sf::Vector3f up;
};

int main()
{
    const int width = 800;
    const int height = 600;

    Cone cone;
    Plane plane;

    thor::ActionMap<std::string> actions;
    thor::ActionMap<std::string>::CallbackSystem system;

    actions["close"] = thor::Action(sf::Event::Closed);
    actions["strafeRight"] = thor::Action(sf::Keyboard::Right);
    actions["strafeLeft" ] = thor::Action(sf::Keyboard::Left );
    actions["strafeUp"   ] = thor::Action(sf::Keyboard::Up   );
    actions["strafeDown" ] = thor::Action(sf::Keyboard::Down );


    sf::Window window(sf::VideoMode(width, height), "Conic sections", sf::Style::Default, sf::ContextSettings(32));
    window.setFramerateLimit(60);

    system.connect("close", std::bind(&sf::Window::close, &window));

    Camera camera{{0,0,200.}, {0,0,0}, {0,1,0}};

    typedef thor::ActionContext<std::string> ActionContext;

    system.connect("strafeRight", [&camera](ActionContext){ camera.eye.x += 10.f; });
    system.connect("strafeLeft" , [&camera](ActionContext){ camera.eye.x -= 10.f; });
    system.connect("strafeUp"   , [&camera](ActionContext){ camera.eye.y += 10.f; });
    system.connect("strafeDown" , [&camera](ActionContext){ camera.eye.y -= 10.f; });


    glEnable (GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, width / float(height), .1, 500);


    while (window.isOpen()){
        actions.update(window);
        actions.invokeCallbacks(system, &window);

        //update here
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
                  camera.lookAt.x, camera.lookAt.y, camera.lookAt.z,
                  camera.up.x, camera.up.y, camera.up.z);

        //draw here

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cone.draw();
        plane.draw();



        window.display();

    }




    return 0;
}
