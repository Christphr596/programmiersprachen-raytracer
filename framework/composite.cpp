#pragma once

#include <glm/vec3.hpp>
#include "shape.hpp"
#include "composite.hpp"
#include "color.hpp"
#include "material.hpp"
#include "hitpoint.hpp"
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>

#include <array>

#define OWN_PI 3.14159265359

Composite::Composite(std::string const& name) : Shape{ name, nullptr } {
};

glm::vec3 Composite::normale(glm::vec3 const& point) {
	glm::vec3 vec{ 0,0,0 };
	return vec;
}

HitPoint Composite::intersect(Ray const& ray) {
	HitPoint hitpoint;
	return hitpoint;
}

void Composite::add_shape(std::shared_ptr<Shape> shape) {
	container.push_back(shape);
};

std::vector<std::shared_ptr<Shape>> Composite::get_children()const {

	return container;
};