#ifndef PLANECONTROLS_HPP
#define PLANECONTROLS_HPP
#include <SFGUI/SFGUI.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PlaneControls
{
public:
    PlaneControls();

    sfg::Widget::Ptr getWidget();

    const glm::mat4& getTransform();

private:
    sfg::Frame::Ptr planeFrame;
    glm::mat4 transform;

    int signOf(const sfg::SpinButton::Ptr& widget) const;
};

#endif // PLANECONTROLS_HPP
