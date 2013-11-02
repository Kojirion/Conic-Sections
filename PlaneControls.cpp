#include "PlaneControls.hpp"

PlaneControls::PlaneControls():
    planeFrame(sfg::Frame::Create("Plane"))
{
    auto planeLayout = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.f);
    auto planeTranslateLayout = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    auto planeRotateLayout = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);


    sfg::Button::Ptr resetButton(sfg::Button::Create("Reset"));
//    resetButton->GetSignal(sfg::Button::OnLeftClick).Connect(
//                std::bind(&Application::trigger, this, "Reset"));
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
        int sign = signOf(rotateXSpinButton);

        transform = glm::rotate(transform, static_cast<float>(sign), glm::vec3(1.f,0,0));
    });
    planeRotateLayout->Pack(rotateXSpinButton);

    sfg::SpinButton::Ptr rotateYSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    rotateYSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect([this, &rotateYSpinButton, speed](){
        int sign = signOf(rotateYSpinButton);

        transform = glm::rotate(transform, static_cast<float>(sign), glm::vec3(0, 1.f, 0));
    });
    planeRotateLayout->Pack(rotateYSpinButton);

    sfg::SpinButton::Ptr rotateZSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    rotateZSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect([this, &rotateZSpinButton, speed](){
        int sign = signOf(rotateZSpinButton);

        transform = glm::rotate(transform, static_cast<float>(sign), glm::vec3(0, 0, 1.f));
    });
    planeRotateLayout->Pack(rotateZSpinButton);

    auto planeRotateFrame = sfg::Frame::Create("Rotate");
    planeRotateFrame->Add(planeRotateLayout);
    planeLayout->Pack(planeRotateFrame);

    planeFrame->Add(planeLayout);
}

sfg::Widget::Ptr PlaneControls::getWidget()
{
    return planeFrame;
}

const glm::mat4 &PlaneControls::getTransform()
{
    return transform;
}

int PlaneControls::signOf(const sfg::SpinButton::Ptr &widget) const
{
    if (widget->IsIncreaseStepperPressed()) return 1;
    return -1;
}
