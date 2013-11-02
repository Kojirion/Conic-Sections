#ifndef PLANE_HPP
#define PLANE_HPP
#include <glm/glm.hpp>

class Plane
{
public:
    Plane();

    bool contains(const glm::vec3 point) const;

    //void update(const sf::Transform& matrix);

    void draw() const;

private:
    glm::vec3 A, B, C, D;
    glm::vec3 AB, AD;
    glm::vec3 cross;
    float Dee;

};

#endif // PLANE_HPP
