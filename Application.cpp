#include "Application.hpp"
#include <glm/gtc/matrix_transform.hpp>

Application::Application():
    window(sf::VideoMode(1366, 768), "Conic sections", sf::Style::Close, sf::ContextSettings(32)),
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

    system.connect("TiltDown", [this](ActionContext){ transform = glm::rotate(transform, -1.f, glm::vec3(1.f,0,0)); });
    system.connect("PullUp"  , [this](ActionContext){ transform = glm::translate(transform, glm::vec3(0, 1.f, 0)); });

    system.connect("Reset"   , [this](ActionContext){ plane = Plane(); });
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

    auto planeLayout = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    auto planeTranslateLayout = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    auto planeRotateLayout = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);


    sfg::Button::Ptr resetButton(sfg::Button::Create("Reset"));
    resetButton->GetSignal(sfg::Button::OnLeftClick).Connect(
                std::bind(&Application::trigger, this, "Reset"));
    planeLayout->Pack(resetButton);

    float speed = 5.f;

    sfg::SpinButton::Ptr translateXSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    translateXSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect([this, &translateXSpinButton, speed](){
        int sign;
        if (translateXSpinButton->IsIncreaseStepperPressed()) sign = 1;
        else sign = -1;

        transform = glm::translate(transform, glm::vec3(0, sign * speed, 0));
    });
    planeTranslateLayout->Pack(translateXSpinButton);

    sfg::SpinButton::Ptr translateYSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    translateYSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect([this, &translateYSpinButton, speed](){
        int sign;
        if (translateYSpinButton->IsIncreaseStepperPressed()) sign = 1;
        else sign = -1;

        transform = glm::translate(transform, glm::vec3(sign * speed, 0, 0));
    });
    planeTranslateLayout->Pack(translateYSpinButton);

    sfg::SpinButton::Ptr translateZSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    translateZSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect([this, &translateZSpinButton, speed](){
        int sign;
        if (translateZSpinButton->IsIncreaseStepperPressed()) sign = 1;
        else sign = -1;

        transform = glm::translate(transform, glm::vec3(0, 0, sign * speed));
    });
    planeTranslateLayout->Pack(translateZSpinButton);

    auto planeTranslateFrame = sfg::Frame::Create("Translate");
    planeTranslateFrame->Add(planeTranslateLayout);
    planeLayout->Pack(planeTranslateFrame);

    sfg::SpinButton::Ptr rotateXSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    rotateXSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect([this, &rotateXSpinButton, speed](){
        int sign;
        if (rotateXSpinButton->IsIncreaseStepperPressed()) sign = 1;
        else sign = -1;

        transform = glm::rotate(transform, static_cast<float>(sign), glm::vec3(1.f,0,0));
    });
    planeRotateLayout->Pack(rotateXSpinButton);

    sfg::SpinButton::Ptr rotateYSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    rotateYSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect([this, &rotateYSpinButton, speed](){
        int sign;
        if (rotateYSpinButton->IsIncreaseStepperPressed()) sign = 1;
        else sign = -1;

        transform = glm::rotate(transform, static_cast<float>(sign), glm::vec3(0, 1.f, 0));
    });
    planeRotateLayout->Pack(rotateYSpinButton);

    sfg::SpinButton::Ptr rotateZSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    rotateZSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect([this, &rotateZSpinButton, speed](){
        int sign;
        if (rotateZSpinButton->IsIncreaseStepperPressed()) sign = 1;
        else sign = -1;

        transform = glm::rotate(transform, static_cast<float>(sign), glm::vec3(0, 0, 1.f));
    });
    planeRotateLayout->Pack(rotateZSpinButton);

    auto planeRotateFrame = sfg::Frame::Create("Rotate");
    planeRotateFrame->Add(planeRotateLayout);
    planeLayout->Pack(planeRotateFrame);

    auto planeFrame = sfg::Frame::Create("Plane");
    planeFrame->Add(planeLayout);
    layout->Attach(planeFrame, {1,0,1,1});

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

        cone.draw();
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
