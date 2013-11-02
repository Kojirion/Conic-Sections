#ifndef CONE_HPP
#define CONE_HPP
#include <vector>
#include <SFML/System/Vector3.hpp>

class Cone
{
public:
    Cone();

    typedef std::vector<sf::Vector3f>::const_iterator iterator;

    iterator begin() const;
    iterator end() const;

    void draw() const;

private:
    std::vector<sf::Vector3f> points;

    int height;
    int radius;
    sf::Vector3f origin;

};

#endif // CONE_HPP
