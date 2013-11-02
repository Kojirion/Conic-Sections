#include "Paraboloid.hpp"

Paraboloid::Paraboloid()
{
    float h = 240.f;
    float r = 200.f;

    for (int i = 0; i<h; ++i){
        for (int j=0; j<360; ++j){
            float angle = j*M_PI/180;
            float x = r * std::sqrt(i/h) * std::cos(angle);
            float y = i;
            float z = r * std::sqrt(i/h) * std::sin(angle);
            points.emplace_back(x,y,z);
//            y = i - h;
//            points.emplace_back(x,y,z);
        }
    }
}
