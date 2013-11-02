#ifndef CONE_HPP
#define CONE_HPP
#include <vector>
#include <glm/glm.hpp>

class Cone
{
public:
    Cone();

    typedef std::vector<glm::vec3>::const_iterator iterator;

    iterator begin() const;
    iterator end() const;

    void draw() const;

private:
    std::vector<glm::vec3> points;

    int height;
    int radius;
    glm::vec3 origin;

};

#endif // CONE_HPP
