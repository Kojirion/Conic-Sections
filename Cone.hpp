#ifndef CONE_HPP
#define CONE_HPP
#include <vector>
#include <SFML/System/Vector3.hpp>

class Cone
{
public:
    Cone();

    void draw() const;

private:
    std::vector<sf::Vector3f> points;

};

#endif // CONE_HPP
