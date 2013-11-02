#include "Cone.hpp"
#include <cmath>
#include <SFML/OpenGL.hpp>

Cone::Cone()
{
    float h = 240.f;
    float r = 200.f;

    for (int i = 0; i<h; ++i){
        for (int j=0; j<360; ++j){
            float angle = j*M_PI/180;
            float x = ((h - i) / h) * r * std::cos(angle);
            float y = h - i;
            float z = ((h - i) / h) * r * std::sin(angle);
            points.emplace_back(x,y,z);
            y = i - h;
            points.emplace_back(x,y,z);
        }
    }

}

Cone::iterator Cone::begin() const
{
    return points.begin();
}

Cone::iterator Cone::end() const
{
    return points.end();
}

void Cone::draw() const
{
    glBegin(GL_POINTS);

    glColor3f(0,255,0);

    for (const auto& point : points)
        glVertex3f(point.x, point.y, point.z);

    glEnd();
}
