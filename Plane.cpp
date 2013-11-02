#include "Plane.hpp"
#include <SFML/OpenGL.hpp>

Plane::Plane():
    A(-240,  240, 0),
    B( 240,  240, 0),
    C( 240, -240, 0),
    D(-240, -240, 0),
    AB(B-A),
    AD(D-A),
    cross(glm::cross(AB, AD)),
    Dee(glm::dot(cross, A))
{

}

bool Plane::contains(const glm::vec3 point) const
{
    return std::abs(glm::dot(point, cross) - Dee) < 10.f;
}

//void Plane::update(const sf::Transform &matrix)
//{

//}

void Plane::draw() const
{
    glBegin(GL_LINE_LOOP);

    glColor3f(255,0,0);

    glVertex3f(A.x, A.y, A.z);
    glVertex3f(B.x, B.y, B.z);
    glVertex3f(C.x, C.y, C.z);
    glVertex3f(D.x, D.y, D.z);

    glEnd();
}

