#ifndef CONIC_HPP
#define CONIC_HPP
#include <glm/glm.hpp>
#include "Cone.hpp"
#include "Plane.hpp"

class Conic
{
public:
    Conic();

    void update(const Surface& surface, const Plane& plane);

    void draw() const;

private:
    std::vector<glm::vec3> points;
};

#endif // CONIC_HPP
