#ifndef SURFACE_HPP
#define SURFACE_HPP
#include <vector>
#include <glm/glm.hpp>

class Surface
{
public:
    Surface();

    typedef std::vector<glm::vec3>::const_iterator iterator;

    iterator begin() const;
    iterator end() const;

    void draw() const;

protected:
    std::vector<glm::vec3> points;

};

#endif // SURFACE_HPP
