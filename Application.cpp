#include "Application.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Cone.hpp"
#include "Cylinder.hpp"
#include "Paraboloid.hpp"

Application::Application():
    window(sf::VideoMode(800, 600), "Snowstorm", sf::Style::Close, sf::ContextSettings(32)),
    planeEquation(sfg::Label::Create())
{
    surfaces.emplace_back(new Cone);
    surfaces.emplace_back(new Cylinder);
    surfaces.emplace_back(new Paraboloid);

    surface = surfaces[2].get();

    actions["Close"]   = thor::Action(sf::Event::Closed      );
    actions["Right"]   = thor::Action(sf::Keyboard::Right    );
    actions["Left" ]   = thor::Action(sf::Keyboard::Left     );
    actions["Up"   ]   = thor::Action(sf::Keyboard::Up       );
    actions["Down" ]   = thor::Action(sf::Keyboard::Down     );
    actions["ZoomIn"]  = thor::Action(sf::Keyboard::Add      );
    actions["ZoomOut"] = thor::Action(sf::Keyboard::Subtract );
    actions["Resized"] = thor::Action(sf::Event::Resized     );
    //actions["PanRight"   ] = thor::Action(sf::Keyboard::Right) && thor::Action(sf::Keyboard::LControl);

    actions["TiltDown"   ] = thor::Action(sf::Keyboard::W);
    actions["PullUp"     ] = thor::Action(sf::Keyboard::N);
//    actions["TiltDown"   ] = thor::Action(sf::Keyboard::W);
//    actions["TiltDown"   ] = thor::Action(sf::Keyboard::W);

    //window.resetGLStates();
    window.setFramerateLimit(60);

    system.connect("Close", std::bind(&sf::Window::close, &window));

    system.connect("Right"   , [this](ActionContext){ camera.longitude -= M_PI/180; });
    system.connect("Left"    , [this](ActionContext){ camera.longitude += M_PI/180; });
    system.connect("Up"      , [this](ActionContext){ camera.latitude  -= M_PI/180; });
    system.connect("Down"    , [this](ActionContext){ camera.latitude  += M_PI/180; });
    system.connect("ZoomIn"  , [this](ActionContext){ camera.eyeDistance  -= 10.f ; });
    system.connect("ZoomOut" , [this](ActionContext){ camera.eyeDistance  += 10.f ; });


    system.connect("Reset"   , [this](ActionContext){ plane = Plane(); });
//    system.connect("PanUp"   , [this](ActionContext){ camera.lookAt.y += 10.f; });
//    system.connect("PanDown" , [this](ActionContext){ camera.lookAt.y -= 10.f; });

}

void Application::run()
{
    const float width = 400.f;
    const float height = 400.f;

    sfg::Table::Ptr layout(sfg::Table::Create());
    layout->SetColumnSpacings(5.f);

    sfg::Canvas::Ptr canvas = sfg::Canvas::Create(true);
    canvas->SetRequisition({width, height});
    layout->Attach(canvas, {0,0,1,10});


    layout->Attach(planeControls.getWidget(), {1,0,1,1});

    layout->Attach(planeEquation, {1,1,1,1});

    sfg::Window::Ptr canvasWindow(sfg::Window::Create(sfg::Window::BACKGROUND));
    canvasWindow->SetRequisition(static_cast<sf::Vector2f>(window.getSize()));
    canvasWindow->Add(layout);
    desktop.Add(canvasWindow);

//    system.connect("Resized", [this, &canvasWindow, &canvas](thor::ActionContext<std::string>){
//        canvasWindow->SetAllocation({canvasWindow->GetAbsolutePosition(),
//                                      static_cast<sf::Vector2f>(window.getSize())});

//        canvas->Bind();
//        auto size = canvas->GetRequisition();
//        glViewport(0, 0, size.x, size.y);
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        gluPerspective(120, size.x / static_cast<float>(size.y), .1, 500);
//        canvas->Unbind();
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
        desktop.Update(1.f);

        plane.update(planeControls.getTransform());
        planeControls.update();
        planeEquation->SetText(plane.getEquation());
        conic.update(*surface, plane);

        canvas->Bind();

        camera.update();

        canvas->Clear();

        //draw here



        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        surface->draw();
        plane.draw();
        conic.draw();

        canvas->Display();
        canvas->Unbind();

        window.setActive(true);
        sfgui_.Display(window);



        window.display();

    }

}

void Application::trigger(const std::string &which)
{
    system.triggerEvent(thor::ActionContext<std::string>(&window, nullptr, which));
}
