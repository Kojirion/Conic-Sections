#include "Plane.hpp"
#include <Thor/Vectors/VectorAlgebra3D.hpp>
#include <SFML/OpenGL.hpp>

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
    return thor::dotProduct(point, cross) == Dee; //but both floats...
}

void Plane::draw() const
{
    glBegin(GL_QUADS);

    glColor4f(255,0,0, 125);

    glVertex3f(A.x, A.y, A.z);
    glVertex3f(B.x, B.y, B.z);
    glVertex3f(C.x, C.y, C.z);
    glVertex3f(D.x, D.y, D.z);

    glEnd();
}

