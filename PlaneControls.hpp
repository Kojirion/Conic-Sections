#ifndef PLANECONTROLS_HPP
#define PLANECONTROLS_HPP
#include <SFGUI/SFGUI.hpp>
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

    void translate (Axis axis);
    void rotate    (Axis axis);

    int signOf(const sfg::SpinButton::Ptr& widget) const;
};

#endif // PLANECONTROLS_HPP
