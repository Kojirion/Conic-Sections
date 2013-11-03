#include "PlaneControls.hpp"
#include <memory>
#include <cassert>

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

    sfg::SpinButton::Ptr translateXSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    translateXSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&PlaneControls::translate, this, Axis::X));
    planeTranslateLayout->Pack(translateXSpinButton);

    sfg::SpinButton::Ptr translateYSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    translateYSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&PlaneControls::translate, this, Axis::Y));
    planeTranslateLayout->Pack(translateYSpinButton);

    sfg::SpinButton::Ptr translateZSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    translateZSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&PlaneControls::translate, this, Axis::Z));
    planeTranslateLayout->Pack(translateZSpinButton);

    auto planeTranslateFrame = sfg::Frame::Create("Translate");
    planeTranslateFrame->Add(planeTranslateLayout);
    planeLayout->Pack(planeTranslateFrame);

    sfg::SpinButton::Ptr rotateXSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    rotateXSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&PlaneControls::rotate, this, Axis::X));
    planeRotateLayout->Pack(rotateXSpinButton);

    sfg::SpinButton::Ptr rotateYSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    rotateYSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&PlaneControls::rotate, this, Axis::Y));
    planeRotateLayout->Pack(rotateYSpinButton);

    sfg::SpinButton::Ptr rotateZSpinButton(sfg::SpinButton::Create(-300.f, 300.f, 1.f));
    rotateZSpinButton->GetSignal(sfg::SpinButton::OnValueChanged).Connect(
                std::bind(&PlaneControls::rotate, this, Axis::Z));
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

void PlaneControls::update()
{
    transform = glm::mat4();
}

const glm::mat4 &PlaneControls::getTransform()
{
    return transform;
}

void PlaneControls::translate(PlaneControls::Axis axis)
{
    sfg::SpinButton::Ptr widget = std::dynamic_pointer_cast<sfg::SpinButton>(sfg::Context::Get().GetActiveWidget());
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

void PlaneControls::rotate(PlaneControls::Axis axis)
{
    sfg::SpinButton::Ptr widget = std::static_pointer_cast<sfg::SpinButton>(sfg::Context::Get().GetActiveWidget());
    int sign = signOf(widget);

    switch (axis) {
    case Axis::X:
        transform = glm::rotate(transform, static_cast<float>(sign), glm::vec3(1.f, 0, 0));
        break;
    case Axis::Y:
        transform = glm::rotate(transform, static_cast<float>(sign), glm::vec3(0, 1.f, 0));
        break;
    case Axis::Z:
        transform = glm::rotate(transform, static_cast<float>(sign), glm::vec3(0, 0, 1.f));
        break;
    default:
        break;
    }
}

int PlaneControls::signOf(const sfg::SpinButton::Ptr &widget) const
{
    if (widget->IsIncreaseStepperPressed()) return 1;
    return -1;
}
