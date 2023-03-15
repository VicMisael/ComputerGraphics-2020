cmake_minimum_required(VERSION 3.22)
project(ComputerGraphics_2020)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/objects)
include_directories(src/util)

add_executable(ComputerGraphics_2020
        src/objects/AABB.cpp
        src/objects/AABB.h
        src/objects/BaseObject.cpp
        src/objects/BaseObject.hpp
        src/objects/Camera.cpp
        src/objects/Camera.hpp
        src/objects/Circle.cpp
        src/objects/Circle.hpp
        src/objects/Cone.cpp
        src/objects/Cone.hpp
        src/objects/Cube.cpp
        src/objects/Cube.hpp
        src/objects/Cylinder.cpp
        src/objects/Cylinder.hpp
        src/objects/Plane.cpp
        src/objects/Plane.hpp
        src/objects/Triangle.cpp
        src/objects/Triangle.hpp
        src/objects/World.cpp
        src/objects/World.hpp
        src/util/Color.cpp
        src/util/Color.hpp
        src/util/definitions.hpp
        src/util/Light.cpp
        src/util/Light.hpp
        src/util/Matrix3x3.cpp
        src/util/Matrix3x3.hpp
        src/util/Matrix4x4.cpp
        src/util/Matrix4x4.hpp
        src/util/Ray.cpp
        src/util/Ray.hpp
        src/util/ThreadPool.h
        src/util/Vector3f.cpp
        src/util/Vector3f.hpp
        src/util/Vector4f.cpp
        src/util/Vector4f.hpp
        src/util/VectorUtilities.cpp
        src/util/VectorUtilities.hpp
        src/main_threaded.cpp)
