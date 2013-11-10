#include "Conic.hpp"
#include <SFML/OpenGL.hpp>
#include <algorithm>
#include <functional>

Conic::Conic()
{
}

void Conic::update(const Surface &surface, const Plane &plane)
{
    points.clear();

    std::copy_if(surface.begin(), surface.end(), std::back_inserter(points),
                 std::bind(&Plane::contains, &plane, std::placeholders::_1));

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
