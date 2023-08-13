

#pragma once

#include <glm/vec3.hpp>
#include <string>
#include "shape.hpp"
#include "Ray.hpp"
#include "hitpoint.hpp"



class Cylinder : public Shape {
public:
	Cylinder() = default;
	Cylinder(glm::vec3 const& midpoint_, float radius_, float height_);
	Cylinder(std::string const& name, glm::vec3 const& midpoint_, float radius_, float height_, std::shared_ptr<Material> const& material);

	float area() const override;
	float volume() const override;
	HitPoint intersect(Ray const& r) override;

private:
	glm::vec3 midpoint_ = { 0,0,0 };
	float radius_ = 0;
	float height_ = 0;
};