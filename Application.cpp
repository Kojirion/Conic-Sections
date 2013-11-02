#include "Application.hpp"
#include <glm/gtc/matrix_transform.hpp>

Application::Application():
    window(sf::VideoMode(1366, 768), "Conic sections", sf::Style::Default, sf::ContextSettings(32)),
    camera{{0,0,200.}, {0,0,0}, {0,1,0}}
{
    actions["Close"] = thor::Action(sf::Event::Closed);
    //actions["StrafeRight"] = thor::Action(sf::Keyboard::Right);
    actions["StrafeLeft" ] = thor::Action(sf::Keyboard::Left );
    actions["StrafeUp"   ] = thor::Action(sf::Keyboard::Up   );
    actions["StrafeDown" ] = thor::Action(sf::Keyboard::Down );
    actions["Resized"    ] = thor::Action(sf::Event::Resized );
    actions["PanRight"   ] = thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::LControl);

    actions["TiltDown"   ] = thor::Action(sf::Keyboard::W);
    actions["PullUp"     ] = thor::Action(sf::Keyboard::N);
//    actions["TiltDown"   ] = thor::Action(sf::Keyboard::W);
//    actions["TiltDown"   ] = thor::Action(sf::Keyboard::W);

    //window.resetGLStates();
    window.setFramerateLimit(60);

    system.connect("Close", std::bind(&sf::Window::close, &window));

    typedef thor::ActionContext<std::string> ActionContext;

    system.connect("StrafeRight", [this](ActionContext){ camera.eye.x += 10.f; });
    system.connect("StrafeLeft" , [this](ActionContext){ camera.eye.x -= 10.f; });
    system.connect("StrafeUp"   , [this](ActionContext){ camera.eye.y += 10.f; });
    system.connect("StrafeDown" , [this](ActionContext){ camera.eye.y -= 10.f; });

    system.connect("PanRight", [this](ActionContext){ camera.lookAt.x += 10.f; });
    system.connect("PanLeft" , [this](ActionContext){ camera.lookAt.x -= 10.f; });
    system.connect("PanUp"   , [this](ActionContext){ camera.lookAt.y += 10.f; });
    system.connect("PanDown" , [this](ActionContext){ camera.lookAt.y -= 10.f; });

    system.connect("TiltDown", [this](ActionContext){ transform = glm::rotate(transform, 5.f, glm::vec3(1.f,0,0)); });
    system.connect("PullUp"  , [this](ActionContext){ transform = glm::translate(transform, glm::vec3(0, 1.f, 0)); });
//    system.connect("PanUp"   , [this](ActionContext){ camera.lookAt.y += 10.f; });
//    system.connect("PanDown" , [this](ActionContext){ camera.lookAt.y -= 10.f; });

}

void Application::run()
{
    const float width = 600.f;
    const float height = 600.f;

    sfg::Table::Ptr layout(sfg::Table::Create());
    layout->SetColumnSpacings(5.f);

    sfg::Canvas::Ptr canvas = sfg::Canvas::Create(true);
    canvas->SetRequisition({width, height});
    layout->Attach(canvas, {0,0,1,10});

    sfg::Button::Ptr button(sfg::Button::Create("Strafe Right"));
    button->GetSignal(sfg::Button::OnLeftClick).Connect(
                std::bind(&Application::trigger, this, "StrafeRight"));
    layout->Attach(button, {1,0,1,1});

    sfg::Window::Ptr canvasWindow(sfg::Window::Create(sfg::Window::BACKGROUND));
    canvasWindow->SetRequisition(static_cast<sf::Vector2f>(window.getSize()));
    canvasWindow->Add(layout);
    desktop.Add(canvasWindow);

//    system.connect("Resized", [this, &canvasWindow](thor::ActionContext<std::string>){
//        canvasWindow->SetAllocation({canvasWindow->GetAbsolutePosition(),
//                                      static_cast<sf::Vector2f>(window.getSize())});
//    });

    sf::Clock clock;

    canvas->Bind();
    glEnable (GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, width / height, .1, 500);
    canvas->Unbind();

    while (window.isOpen()){
        actions.clearEvents();

        sf::Event event;
        while (window.pollEvent(event)){
            actions.pushEvent(event);
            desktop.HandleEvent(event);
        }

        transform = glm::mat4();
        actions.invokeCallbacks(system, &window);

        //update here
        desktop.Update(clock.restart().asSeconds());

        plane.update(transform);
        conic.update(cone, plane);

        canvas->Bind();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
                  camera.lookAt.x, camera.lookAt.y, camera.lookAt.z,
                  camera.up.x, camera.up.y, camera.up.z);

        canvas->Clear();

        //draw here



        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //cone.draw();
        plane.draw();
        conic.draw();

//        canvas->Display();
//        canvas->Unbind();

        window.setActive(true);
        sfgui_.Display(window);



        window.display();

    }

}

void Application::trigger(const std::string &which)
{
    system.triggerEvent(thor::ActionContext<std::string>(&window, nullptr, which));
}
