#include "Application.hpp"

Application::Application():
    window(sf::VideoMode(800, 600), "Conic sections", sf::Style::Default, sf::ContextSettings(32)),
    camera{{0,0,200.}, {0,0,0}, {0,1,0}}
{
    actions["close"] = thor::Action(sf::Event::Closed);
    actions["strafeRight"] = thor::Action(sf::Keyboard::Right);
    actions["strafeLeft" ] = thor::Action(sf::Keyboard::Left );
    actions["strafeUp"   ] = thor::Action(sf::Keyboard::Up   );
    actions["strafeDown" ] = thor::Action(sf::Keyboard::Down );

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
    const float width = 200.f;
    const float height = 200.f;

    sfg::Canvas::Ptr canvas = sfg::Canvas::Create(true);
    canvas->SetRequisition({width, height});
    sfg::Window::Ptr canvasWindow(sfg::Window::Create());
    canvasWindow->Add(canvas);
    desktop.Add(canvasWindow);

    sf::Clock clock;



    canvas->Bind();
    glEnable (GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, width / height, .1, 500);
    canvas->Unbind();

    canvas->GetSignal(sfg::Canvas::OnSizeAllocate).Connect([&canvas](){

    });


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
