#include "Plane.hpp"
#include <SFML/OpenGL.hpp>
#include <boost/spirit/include/karma.hpp>
#include <list>

Plane::Plane():
    A(-240,  240, 0),
    B( 240,  240, 0),
    C( 240, -240, 0),
    D(-240, -240, 0),
    AB(B-A),
    AD(D-A),
    cross(glm::cross(AB, AD)),
    Dee(glm::dot(cross, A))
{

}

bool Plane::contains(const glm::vec3 point) const
{
    return std::abs(glm::dot(point, cross) - Dee) < 100000.f;
}


void Plane::update(const glm::mat4& matrix)
{
    A = glm::vec3(matrix * glm::vec4(A, 1.f));
    B = glm::vec3(matrix * glm::vec4(B, 1.f));
    C = glm::vec3(matrix * glm::vec4(C, 1.f));
    D = glm::vec3(matrix * glm::vec4(D, 1.f));

    AB = B-A;
    AD = D-A;
    cross = glm::cross(AB, AD);
    Dee = glm::dot(cross, A);

    namespace karma = boost::spirit::karma;
    namespace ascii = boost::spirit::ascii;
    using karma::float_;
    using karma::generate_delimited;
    using ascii::space;

    std::list<float> list = {cross.x, cross.y, cross.z, Dee};

    equation.clear();
    std::back_insert_iterator<std::string> sink(equation);
    generate_delimited(sink,
                       float_ << *(',' << float_),
                       space, list);

    //equation = generated;

    //equation = formatted.str();

//    equation = std::to_string(cross.x) + "x + "
//             + std::to_string(cross.y) + "y + "
//             + std::to_string(cross.z) + "z = "
//             + std::to_string(Dee);
}

void Plane::draw() const
{
    glBegin(GL_LINE_LOOP);

    glColor3f(255,0,0);

    glVertex3f(A.x, A.y, A.z);
    glVertex3f(B.x, B.y, B.z);
    glVertex3f(C.x, C.y, C.z);
    glVertex3f(D.x, D.y, D.z);

    glEnd();
}

const std::string &Plane::getEquation() const
{
    return equation;
}

