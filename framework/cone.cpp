
#pragma once

#include <glm/vec3.hpp>
#include "shape.hpp"
#include "cone.hpp"
#include "material.hpp"
#include <string>
#include <utility>

#define OWN_PI 3.14159265359


Cone::Cone(glm::vec3 const& midpoint, float radius, float height) : Shape{}, midpoint_{ midpoint }, radius_{ abs(radius) }, height_{ abs(height) } {
};

Cone::Cone(std::string const& name, glm::vec3 const& midpoint, float radius, float height, std::shared_ptr<Material> const& material) :
	Shape{ name, material }, midpoint_{ midpoint }, radius_{abs( radius) }, height_{ abs(height) } {
};

float Cone::area() const {
	float area = OWN_PI * radius_ * radius_ + height_ * radius_ * (sqrt(height_*height_+radius_*radius_));
	return area;
}

float Cone::volume() const {
	float v = 1 / 3 * OWN_PI * radius_ * radius_ * height_;
	return v;
}

HitPoint Cone::intersect(Ray const& ray) {
	HitPoint hitpoint{};
	return hitpoint;
}