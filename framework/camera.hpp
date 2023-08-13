#pragma once

#include <glm/vec3.hpp>
#include <string>
#include "Color.hpp"

struct Camera {
	std::string name = "";
	float fov_x = 0.0f;
	glm::vec3 eye = { 0,0,0 };
	glm::vec3 dir = { 0,0,0 };
	glm::vec3 up = { 0,0,0 };
};