#include "Surface.hpp"
#include <SFML/OpenGL.hpp>

Surface::Surface()
{
}

Surface::iterator Surface::begin() const
{
    return points.begin();
}

Surface::iterator Surface::end() const
{
    return points.end();
}


void Surface::draw() const
{
    glBegin(GL_POINTS);

    glColor3f(0,255,0);

    for (const auto& point : points)
        glVertex3f(point.x, point.y, point.z);

    glEnd();
}
