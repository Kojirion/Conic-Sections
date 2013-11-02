#include "Plane.hpp"
#include <Thor/Vectors/VectorAlgebra3D.hpp>
#include <SFML/OpenGL.hpp>
#include <limits>

Plane::Plane():
    A(-240,  240, 0),
    B( 240,  240, 0),
    C( 240, -240, 0),
    D(-240, -240, 0),
    AB(B-A),
    AD(D-A),
    cross(thor::crossProduct(AB, AD)),
    Dee(thor::dotProduct(cross, A))
{

}

bool Plane::contains(const sf::Vector3f point) const
{
    return std::abs(thor::dotProduct(point, cross) - Dee) < 10.f;
}

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

