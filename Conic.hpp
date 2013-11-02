#ifndef CONIC_HPP
#define CONIC_HPP
#include <SFML/System/Vector3.hpp>
#include "Cone.hpp"
#include "Plane.hpp"

class Conic
{
public:
    Conic();

    void update(const Cone& cone, const Plane& plane);

private:
};

#endif // CONIC_HPP
