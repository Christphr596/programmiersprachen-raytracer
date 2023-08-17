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

float Composite::area() const {
	return 0;
}

float Composite::volume() const {
	return 0;
}

HitPoint Composite::intersect(Ray const& ray) {
	HitPoint hitpoint;
	return hitpoint;
}

void Composite::add_shape(std::shared_ptr<Shape> shape) {
	container.push_back(shape);
};

void Composite::remove_shape(std::string const& name) {
	for (auto it : container) {
		if (it->get_name() == name) {
			//container.erase(it);
		}
	}
};

std::vector<std::shared_ptr<Shape>> Composite::get_children()const {

	return container;
};