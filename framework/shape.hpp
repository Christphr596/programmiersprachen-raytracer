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

	virtual std::ostream& print(std::ostream& os) const;
	std::pair<std::string, std::shared_ptr<Material>> get_n_c();
	std::string get_name() const;
	std::shared_ptr<Material> get_material() const;

	virtual HitPoint intersect(Ray const& r) = 0;
	virtual glm::vec3 normale(glm::vec3 const& point) = 0;
	//Mathoden die die Einzelmatrizen ver�ndern
	void scale(glm::vec3 const& scale_vec);
	void rotate(float degree, glm::vec3  const& rotation_axis);
	void translate(glm::vec3 const& translation_vec);
	//Methode, die die world_transformation Matrix (und ihre Inverse) richtig (dh. die drei Einzelmatrizen in der richtigen Reihenfolge) berechnen
	void update_w_t_mat();
	glm::mat4 get_w_t_mat() const;
	glm::mat4 get_w_t_inv_mat() const;


	//virtual ~Shape();

private:
	std::string name_ = "no_name";
	std::shared_ptr<Material> material_ = nullptr;
	glm::mat4 scale_mat_{};
	glm::mat4 rotation_mat_{};
	glm::mat4 translation_mat_{};
	glm::mat4 world_transformation_ = glm::mat4{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	glm::mat4 world_transformation_inv_ = glm::mat4{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
};

std::ostream& operator<<(std::ostream& os, Shape const& s);


