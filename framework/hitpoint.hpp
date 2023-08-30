#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <limits>
#include <memory>
#include "material.hpp"

#ifndef HITPOINT_HPP
#define HITPOINT_HPP

struct HitPoint
{
	bool cut = false;
	float distance = INFINITY;
	std::string name = "";
	std::shared_ptr<Material> material = std::make_shared<Material>();
	glm::vec3 point = { 0.0f, 0.0f, 0.0f };
	glm::vec3 direction = { 0.0, 0.0, 0.0 };
	glm::vec3 normale = { 0.0, 0.0, 0.0 };
};

HitPoint transform(glm::mat4 const& mat, HitPoint const& hp);

#endif