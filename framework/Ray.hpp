#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#ifndef RAY_HPP
#define RAY_HPP

struct Ray
{
	glm::vec3 origin = { 0.0f, 0.0f, 0.0f };
	glm::vec3 direction = { 0.0f, 0.0f, -1.0f };
};

Ray transform(glm::mat4 const& mat, Ray const& r);


#endif