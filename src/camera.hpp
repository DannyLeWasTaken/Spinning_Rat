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

    glm::mat4 GetViewMatrix();

    void UpdateCameraVectors();

    // Getters and setters
    glm::vec3 GetPosition() const { return Position; }
    glm::vec3 GetFrontVector() const { return Front; }
    glm::vec3 GetUpVector() const { return Up; }
    glm::vec3 GetRightVector() const { return Right; }
    glm::vec3 GetWorldUpVector() const { return WorldUp; }

    float GetYaw() const { return Yaw; }
    float GetPitch() const { return Pitch; }
    float GetRoll() const { return Roll; }
    float GetMovementSpeed() const { return MovementSpeed; }
    float GetMouseSensitivity() const { return MouseSensitivity; }
    float GetFOV() const { return FOV; }

private:
    glm::vec3 Position, Front, Up, Right, WorldUp;
    float Yaw, Pitch, Roll, MovementSpeed, MouseSensitivity, FOV;
};

#endif //SPINNING_RAT_CAMERA_HPP
