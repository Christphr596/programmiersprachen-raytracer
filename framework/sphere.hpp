#pragma once

#include <glm/vec3.hpp>
#include "shape.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"

class Sphere : public Shape {
public:
	Sphere()= default;
	Sphere(glm::vec3 const& mid_point, float radius);
	Sphere(std::string const& name, glm::vec3 const& mid_point, float radius, std::shared_ptr<Material> const& material);

	float area() const override;
	float volume() const override;
	HitPoint intersect(Ray const& ray) override;
	std::ostream& print(std::ostream& os) const override;

	glm::vec3 normale(glm::vec3 const& point) override;

	//~Sphere();

private:
	glm::vec3 center_ = { 0,0,0 };
	float radius_ = 0;
};

