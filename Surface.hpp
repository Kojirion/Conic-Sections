#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <string>

class Surface
{
public:
    Surface();

    typedef std::vector<glm::vec3>::const_iterator iterator;

    iterator begin() const;
    iterator end() const;

    void draw() const;

    std::string name;

protected:
    std::vector<glm::vec3> points;

};
