#include "PlaneControls.hpp"
#include <memory>
#include <cassert>
#include <SFGUI/Button.hpp>

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

    translateButton(Axis::X, planeTranslateLayout);
    translateButton(Axis::Y, planeTranslateLayout);
    translateButton(Axis::Z, planeTranslateLayout);

    auto planeTranslateFrame = sfg::Frame::Create("Translate");
    planeTranslateFrame->Add(planeTranslateLayout);
    planeLayout->Pack(planeTranslateFrame);

    rotateButton(Axis::X, planeRotateLayout);
    rotateButton(Axis::Y, planeRotateLayout);
    rotateButton(Axis::Z, planeRotateLayout);

    auto planeRotateFrame = sfg::Frame::Create("Rotate");
    planeRotateFrame->Add(planeRotateLayout);
    planeLayout->Pack(planeRotateFrame);

    planeFrame->Add(planeLayout);
}

sfg::Widget::Ptr PlaneControls::getWidget()
{
    return planeFrame;
}

void PlaneControls::update()
{
    transform = glm::mat4();
}

const glm::mat4 &PlaneControls::getTransform()
{
    return transform;
}

void PlaneControls::translate(PlaneControls::Axis axis, const sfg::SpinButton* widget)
{    
    assert(widget);

    int sign = signOf(widget);

    float speed = 5.f;

    switch (axis) {
    case Axis::X:
        transform = glm::translate(transform, glm::vec3(sign * speed, 0, 0));
        break;
    case Axis::Y:
        transform = glm::translate(transform, glm::vec3(0, sign * speed, 0));
        break;
    case Axis::Z:
        transform = glm::translate(transform, glm::vec3(0, 0, sign * speed));
        break;
    default:
        break;
    }
}

void PlaneControls::rotate(PlaneControls::Axis axis, const sfg::SpinButton *widget)
{
    assert(widget);

    int sign = signOf(widget);
    float angle = sign*M_PI/180.f;

    switch (axis) {
    case Axis::X:
        transform = glm::rotate(transform, angle, glm::vec3(1.f, 0, 0));
        break;
    case Axis::Y:
        transform = glm::rotate(transform, angle, glm::vec3(0, 1.f, 0));
        break;
    case Axis::Z:
        transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1.f));
        break;
    default:
        break;
    }
}

int PlaneControls::signOf(const sfg::SpinButton* widget) const
{
    if (widget->IsIncreaseStepperPressed()) return 1;
    return -1;
}

void PlaneControls::translateButton(PlaneControls::Axis axis, const sfg::Box::Ptr &layout)
{
    sfg::SpinButton::Ptr button(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    button->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&PlaneControls::translate, this, axis, button.get()));
    layout->Pack(button);
}

void PlaneControls::rotateButton(PlaneControls::Axis axis, const sfg::Box::Ptr &layout)
{
    sfg::SpinButton::Ptr button(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    button->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&PlaneControls::rotate, this, axis, button.get()));
    layout->Pack(button);
}
