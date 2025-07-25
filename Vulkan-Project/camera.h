#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>



struct Camera {

	float zNear = 0.01f;
	float zFar = 1000.0f;

	float fov = 45.0f; // degrees

	glm::vec3 position = { 0.0f, 2.0f, 2.0f };
	glm::vec3 rotation = { 120.0f, 0.0f, 0.0f }; // degrees
	glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

	glm::mat4 getTransformationMatrix() {
		return glm::translate(glm::mat4(1.0f), position)
			* glm::mat4_cast(glm::quat(glm::radians(rotation)))
			* glm::scale(glm::mat4(1.0f), scale);
	}

	glm::mat4 getViewMatrix() {
		glm::mat4 cameraMatrix = getTransformationMatrix();
		return glm::lookAt(position, position + glm::vec3(cameraMatrix[2]), glm::vec3(cameraMatrix[1]));
	}
};