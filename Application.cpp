#include "Application.hpp"

Application::Application():
    window(sf::VideoMode(1366, 768), "Conic sections", sf::Style::Default, sf::ContextSettings(32)),
    camera{{0,0,200.}, {0,0,0}, {0,1,0}}
{
    actions["close"] = thor::Action(sf::Event::Closed);
    actions["strafeRight"] = thor::Action(sf::Keyboard::Right);
    actions["strafeLeft" ] = thor::Action(sf::Keyboard::Left );
    actions["strafeUp"   ] = thor::Action(sf::Keyboard::Up   );
    actions["strafeDown" ] = thor::Action(sf::Keyboard::Down );
    actions["resized"    ] = thor::Action(sf::Event::Resized );

    //window.resetGLStates();
    window.setFramerateLimit(60);

    system.connect("close", std::bind(&sf::Window::close, &window));

    typedef thor::ActionContext<std::string> ActionContext;

    system.connect("strafeRight", [this](ActionContext){ camera.eye.x += 10.f; });
    system.connect("strafeLeft" , [this](ActionContext){ camera.eye.x -= 10.f; });
    system.connect("strafeUp"   , [this](ActionContext){ camera.eye.y += 10.f; });
    system.connect("strafeDown" , [this](ActionContext){ camera.eye.y -= 10.f; });

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
                std::bind(&Application::trigger, this, "strafeRight"));
    layout->Attach(button, {1,0,1,1});

    sfg::Window::Ptr canvasWindow(sfg::Window::Create(sfg::Window::BACKGROUND));
    canvasWindow->SetRequisition(static_cast<sf::Vector2f>(window.getSize()));
    canvasWindow->Add(layout);
    desktop.Add(canvasWindow);

//    system.connect("resized", [this, &canvasWindow](thor::ActionContext<std::string>){
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

        actions.invokeCallbacks(system, &window);

        //update here
        desktop.Update(clock.restart().asSeconds());

        canvas->Bind();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
                  camera.lookAt.x, camera.lookAt.y, camera.lookAt.z,
                  camera.up.x, camera.up.y, camera.up.z);

        canvas->Clear();

        //draw here



        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cone.draw();
        plane.draw();

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
