//
// Created by Danny Le on 2022-08-27.
//
#ifndef SPINNING_RAT_CAMERA_HPP
#define SPINNING_RAT_CAMERA_HPP
#pragma once

#include <glm/glm.hpp>


class Camera
{
public:
    Camera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = -90.0f,
            float pitch = 0.0f);
private:
    glm::vec3 Position, Front, Up, Right, WorldUp;
    float Yaw, Pitch, Roll, MovementSpeed, MouseSensitivity, FOV;
};

#endif //SPINNING_RAT_CAMERA_HPP
