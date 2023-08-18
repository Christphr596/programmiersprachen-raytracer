#include <glm/vec3.hpp>
#include "shape.hpp"
#include "triangle.hpp"
#include "color.hpp"
#include "material.hpp"
#include <string>
#include <utility>
#include <cmath>

#define OWN_PI 3.14159265359


Triangle::Triangle(std::string const& name, glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, std::shared_ptr<Material> const& material) :
	Shape{ name, material }, p1_{ p1 }, p2_{ p2 }, p3_{ p3 } {};

float Triangle::area() const{
	return 0;
}

float Triangle::volume() const {
	return 0;
}

glm::vec3 Triangle::normale(glm::vec3 const& point) {
	
	glm::vec3 a = p2_ - p1_;
	glm::vec3 b = p3_ - p1_;

	glm::vec3 k = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.y, a.x * b.y - a.y * b.x };

	return k;
}

HitPoint Triangle::intersect(Ray const& r) {
	HitPoint hitpoint;

	glm::vec3 a = p2_ - p1_;
	glm::vec3 b = p3_ - p1_;

	glm::vec3 k = { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.y, a.x * b.y - a.y * b.x };
	float p = k.x*r.direction.x+ k.y * r.direction.y + k.z * r.direction.z ;

	float n = (k.x * p1_.x) + (k.y * p1_.y) + (k.z * p1_.z);

	if(p != 0){

		float d = 0;

		glm::vec3 s = { r.origin.x + d * r.direction.x, r.origin.y + d * r.direction.y, r.origin.z + d * r.direction.z };

		float be_a = sqrt(a.x*a.x+ a.y * a.y+ a.z * a.z);
		float be_b = sqrt(b.x * b.x + b.y * b.y + b.z * b.z);

		glm::vec3 se = s - p1_;
		float be_se = sqrt(se.x * se.x + se.y * se.y + se.z * se.z);

		float h;
		float j;

		if (0 <= h || h <= 1 || 0 <= j || j <= 1 || 0 <= (j + h) || (j + h) <= 1) {


		}
	}

	return hitpoint;
}