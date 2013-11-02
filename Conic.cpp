#include "Conic.hpp"
#include <SFML/OpenGL.hpp>

Conic::Conic()
{
}

void Conic::update(const Cone &cone, const Plane &plane)
{
    points.clear();

    for (const auto& point : cone){
        if (plane.contains(point))
            points.emplace_back(point);
    }


}

void Conic::draw() const
{
    glPointSize(6.f);

    glBegin(GL_POINTS);

    glColor3f(204, 102, 0);

    for (const auto& point : points)
        glVertex3f(point.x, point.y, point.z);

    glEnd();

    glPointSize(1.f);
}
