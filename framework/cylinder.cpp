
#pragma once

#include <glm/vec3.hpp>
#include "shape.hpp"
#include "cylinder.hpp"
#include "material.hpp"
#include <string>
#include <utility>
#include <cmath>

#define OWN_PI 3.14159265359


Cylinder::Cylinder(glm::vec3 const& midpoint, float radius, float height) : Shape{}, midpoint_{ midpoint },radius_{ abs(radius) }, height_{ abs(height) } {
};

Cylinder::Cylinder(std::string const& name, glm::vec3 const& midpoint, float radius, float height, std::shared_ptr<Material> const& material) :
	Shape{ name, material }, midpoint_{ midpoint }, radius_{ abs(radius) }, height_{ abs(height) } {
};

float Cylinder::area() const {
	float area = 2 * OWN_PI * radius_ * (radius_ + height_);
	return area;
}

float Cylinder::volume() const {
	float v = radius_ * radius_ * OWN_PI * height_;
	return v;
}

/*
HitPoint Cylinder::intersect(Ray const& ray) {
	HitPoint hitpoint{};
	return hitpoint;
}*/

HitPoint Cylinder::intersect(Ray const& r) {

	HitPoint hitpoint{};

	float dist = 0.0f;
	float a = r.direction.y / r.direction.x; //Anstieg
	float b = r.origin.y - a * r.origin.x; //Verschiebung y

	if (1 - a * a != 0) {
		float x1 = -(2 * a * b - 2 * a * midpoint_.y - 2 * midpoint_.x) +
			sqrt((2 * a * b - 2 * a * midpoint_.y - 2 * midpoint_.x) * (2 * a * b - 2 * a * midpoint_.y - 2 * midpoint_.x) - 4 * (1 - a * a) * (b * b + midpoint_.x * midpoint_.x + midpoint_.y * midpoint_.y - radius_ * radius_ - 2 * b * midpoint_.y))
			/ 2 * (1 - a * a);

		float x2 = -(2 * a * b - 2 * a * midpoint_.y - 2 * midpoint_.x) -
			sqrt((2 * a * b - 2 * a * midpoint_.y - 2 * midpoint_.x) * (2 * a * b - 2 * a * midpoint_.y - 2 * midpoint_.x) - 4 * (1 - a * a) * (b * b + midpoint_.x * midpoint_.x + midpoint_.y * midpoint_.y - radius_ * radius_ - 2 * b * midpoint_.y))
			/ 2 * (1 - a * a);

		float y1 = a * x1 + b;
		float y2 = a * x2 + b;
		
		float a2 = r.direction.z / r.direction.y; //Anstieg 2
		float b2 = r.origin.z - a2 * r.origin.y; //Verschiebung z

		float z1 = a2 * y1 + b2;
		float z2 = a2 * y2 + b2;

		glm::vec3 cut = { x1,y1,z1 };

		dist = sqrt((cut.x - r.origin.x) * (cut.x - r.origin.x) + (cut.y - r.origin.y) * (cut.y - r.origin.y) + (cut.z - r.origin.z) * (cut.z - r.origin.z));

		hitpoint = HitPoint{ true, dist, Shape::get_name(), Shape::get_material(), cut, r.direction};
	}
	
	return hitpoint;

}