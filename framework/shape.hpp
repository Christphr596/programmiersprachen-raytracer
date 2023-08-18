#pragma once

#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
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

	void scale(glm::vec3 const& scale_vec);
	void rotate(float degree, glm::vec3  const& rotation_axis);
	void translte(glm::vec3 const& translation_vec);

	//virtual ~Shape();

private:
	std::string name_ = "no_name";
	std::shared_ptr<Material> material_ = nullptr;
	glm::mat4 world_transformation_ = glm::mat4{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	glm::mat4 world_transformation_inv_ = glm::mat4{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
};

std::ostream& operator<<(std::ostream& os, Shape const& s);
