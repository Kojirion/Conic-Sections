#pragma once
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Thor/Input/ActionMap.hpp>
#include <Thor/Input/EventSystem.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Label.hpp>


#include "Conic.hpp"
#include "PlaneControls.hpp"
#include "Camera.hpp"

#include <memory>

class Surface;

typedef thor::ActionMap<std::string> ActionMap;
typedef ActionMap::CallbackSystem CallbackSystem;
typedef thor::ActionContext<std::string> ActionContext;

class Application
{
public:
    Application();

    void run();

private:
    sfg::SFGUI sfgui_;
    sf::Window window;
    sfg::Desktop desktop;
    sfg::Label::Ptr planeEquation;
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
