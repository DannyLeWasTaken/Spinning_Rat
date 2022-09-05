//
// Created by Danny Le on 2022-08-27.
//
#pragma once

#include "camera.hpp"

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch): Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(16.f), MouseSensitivity(45.f)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw) * cos(glm::radians(Pitch)));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw) * cos(glm::radians(Pitch)));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right,Front));
}