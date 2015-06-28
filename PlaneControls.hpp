#pragma once
#include <SFGUI/Widget.hpp>
#include <SFGUI/Frame.hpp>
#include <SFGUI/SpinButton.hpp>
#include <SFGUI/Box.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

class PlaneControls
{
public:
    PlaneControls();

    sfg::Widget::Ptr getWidget();

    void update();

    const glm::mat4& getTransform();

private:
    sfg::Frame::Ptr planeFrame;
    glm::mat4 transform;

    enum class Axis {
        X,
        Y,
        Z
    };

    void translate (Axis axis, const sfg::SpinButton *widget);
    void rotate    (Axis axis, const sfg::SpinButton *widget);

    int signOf(const sfg::SpinButton *widget) const;

    void translateButton(Axis axis, const sfg::Box::Ptr& layout);
    void rotateButton(Axis axis, const sfg::Box::Ptr& layout);
};
