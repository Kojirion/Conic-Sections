#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <Thor/Input/ActionMap.hpp>
#include <Thor/Input/EventSystem.hpp>
#include <SFGUI/SFGUI.hpp>
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "Conic.hpp"
#include "Paraboloid.hpp"

struct Camera{
    sf::Vector3f eye;
    sf::Vector3f lookAt;
    sf::Vector3f up;
};

class Application
{
public:
    Application();

    void run();

private:
    sfg::SFGUI sfgui_;
    sf::Window window;
    sfg::Desktop desktop;
    //sf::Image icon;
    thor::ActionMap<std::string> actions;
    thor::ActionMap<std::string>::CallbackSystem system;
    Camera camera;

    Cone cone;
    Cylinder cylinder;
    Paraboloid paraboloid;
    Plane plane;

    Conic conic;

    void trigger(const std::string& which);

    glm::mat4 transform;

};

#endif // APPLICATION_HPP
