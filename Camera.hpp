#pragma once
#include <SFML/System/Vector3.hpp>

struct Camera{

    float longitude;
    float latitude;
    float eyeDistance;


    Camera();

    void update();

private:

    sf::Vector3f eye;
    sf::Vector3f lookAt;
    sf::Vector3f up;





};
