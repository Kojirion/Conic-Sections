#ifndef PLANE_HPP
#define PLANE_HPP
#include <glm/glm.hpp>
#include <string>

class Plane
{
public:
    Plane();

    bool contains(const glm::vec3 point) const;

    void update(const glm::mat4 &matrix);

    void draw() const;

    const std::string& getEquation() const;

private:
    glm::vec3 A, B, C, D;
    glm::vec3 AB, AD;
    glm::vec3 cross;
    float Dee;

    std::string equation;

};

#endif // PLANE_HPP
