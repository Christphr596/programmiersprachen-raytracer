#pragma once

#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"
#include "material.hpp"
#include "hitpoint.hpp"
#include "Ray.hpp"

class Shape {
public:
	
	Shape() = default;
	Shape(std::string const& name_, std::shared_ptr<Material> const& material);

	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const;
	std::pair<std::string, std::shared_ptr<Material>> get_n_c();
	std::string get_name() const;
	std::shared_ptr<Material> get_material() const;

	virtual HitPoint intersect(Ray const& r) = 0;
	virtual glm::vec3 normale(glm::vec3 const& point) = 0;

	//virtual ~Shape();

private:
	std::string name_ = "no_name";
	std::shared_ptr<Material> material_ = nullptr;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);
