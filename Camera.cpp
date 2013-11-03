#include "Camera.hpp"
#include <cmath>
#include <SFML/OpenGL.hpp>

Camera::Camera():
    longitude(M_PI), latitude(M_PI), eyeDistance(500.f),
    lookAt(0, 0, 0), up(0, 1, 0)
{

}

void Camera::update()
{
    using namespace std;

    eye.x = eyeDistance * cos(latitude) * cos(longitude);
    eye.y = eyeDistance * sin(latitude)                 ;
    eye.z = eyeDistance * cos(latitude) * sin(longitude);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye.x, eye.y, eye.z,
              lookAt.x, lookAt.y, lookAt.z,
              up.x, up.y, up.z);
}




