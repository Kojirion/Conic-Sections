project(ConicSections)
cmake_minimum_required(VERSION 2.8)

find_package(SFML 2 REQUIRED graphics window system)
find_package(Thor 2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SFGUI REQUIRED)
find_package(GLM REQUIRED)

set(HDRS
    Conic.hpp
    PlaneControls.hpp
    Plane.hpp
    Surface.hpp
    Cylinder.hpp
    Application.hpp
    Cone.hpp
    Paraboloid.hpp
    Camera.hpp
)

set(SRCS
    Cone.cpp
    Plane.cpp
    Conic.cpp
    Surface.cpp
    Camera.cpp
    Cylinder.cpp
    Paraboloid.cpp
    PlaneControls.cpp
    Application.cpp
    main.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
add_executable(${PROJECT_NAME} ${HDRS} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${OPENGL_LIBRARIES}
                                      ${THOR_LIBRARY}   ${SFGUI_LIBRARY})
