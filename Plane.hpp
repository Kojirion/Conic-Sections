#ifndef PLANE_HPP
#define PLANE_HPP
#include <SFML/System/Vector3.hpp>

class Plane
{
public:
    Plane();

    bool contains(const sf::Vector3f point) const;

    void draw() const;

private:
    sf::Vector3f A, B, C, D;
    sf::Vector3f AB, AD;
    sf::Vector3f cross;
    float Dee;

};

#endif // PLANE_HPP
