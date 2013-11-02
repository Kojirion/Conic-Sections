#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <Thor/Input/ActionMap.hpp>
#include <Thor/Input/EventSystem.hpp>
#include <SFGUI/SFGUI.hpp>
#include "Conic.hpp"
#include "PlaneControls.hpp"
#include <memory>

class Surface;

typedef thor::ActionMap<std::string> ActionMap;
typedef ActionMap::CallbackSystem CallbackSystem;
typedef thor::ActionContext<std::string> ActionContext;

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
    ActionMap actions;
    CallbackSystem system;
    Camera camera;

    Plane plane;
    PlaneControls planeControls;

    Surface* surface;
    std::vector<std::unique_ptr<Surface> > surfaces;

    Conic conic;

    void trigger(const std::string& which);

    glm::mat4 transform;

};

#endif // APPLICATION_HPP
