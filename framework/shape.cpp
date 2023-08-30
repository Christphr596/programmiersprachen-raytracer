#include "shape.hpp"
#include <string>
#define OWN_PI 3.14159265359f


Shape::Shape(std::string const& name, std::shared_ptr<Material> const& material) : name_{ name }, material_{ material } {
};

std::ostream& Shape::print(std::ostream& os)const {
	os << "\n " << "Name: " << name_ <<  "Material: " << material_;
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	s.print(os);
	return os;
}

std::pair<std::string, std::shared_ptr<Material>> Shape::get_n_c() {
	return std::pair<std::string, std::shared_ptr<Material>> {name_, material_};
}

std::string Shape::get_name() const {
	return name_;
}

std::shared_ptr<Material> Shape::get_material() const {
	return material_;
}


glm::mat4 Shape::get_w_t_mat() const {
	return world_transformation_;
}

glm::mat4 Shape::get_w_t_inv_mat() const{
	return world_transformation_inv_;
}

void Shape::scale(glm::vec3 const& scale_vec) {
	glm::mat4 scale_mat{};
	scale_mat[0] = glm::vec4{scale_vec.x, 0.0f, 0.0f, 0.0f};
	scale_mat[1] = glm::vec4{ 0.0f, scale_vec.y, 0.0f, 0.0f };
	scale_mat[2] = glm::vec4{ 0.0f, 0.0f, scale_vec.z, 0.0f };
	scale_mat[3] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };

	Shape::scale_mat_ = scale_mat * Shape::scale_mat_;

}

void Shape::rotate(float degree, glm::vec3 const& rotation_axis) {
	float radian = degree * OWN_PI / 180.0f;

	glm::mat4 rotation_mat{};
	rotation_mat[3] = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };

	if (rotation_axis == glm::vec3{1.0f, 0.0f, 0.0f}) {
		rotation_mat[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
		rotation_mat[1] = glm::vec4{0.0f, std::cos(radian), std::sin(radian), 0.0f};
		rotation_mat[2] = glm::vec4{ 0.0f, -1.0f* std::sin(radian), std::cos(radian), 0.0f };
	}
	else if (rotation_axis == glm::vec3{ 0.0f, 1.0f, 0.0f }) {
		rotation_mat[0] = glm::vec4{ std::cos(radian), 0.0f, std::sin(radian), 0.0f };
		rotation_mat[1] = glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f };
		rotation_mat[2] = glm::vec4{ -1.0f * std::sin(radian), 0.0f, std::cos(radian), 0.0f };
	}
	else if (rotation_axis == glm::vec3{ 0.0f, 0.0f, 1.0f }) {
		rotation_mat[0] = glm::vec4{ std::cos(radian), std::sin(radian), 0.0f, 0.0f };
		rotation_mat[1] = glm::vec4{ -1.0f * std::sin(radian), std::cos(radian), 0.0, 0.0f };
		rotation_mat[2] = glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f };
	}

	Shape::rotation_mat_ = rotation_mat * Shape::rotation_mat_;

}


void Shape::translate(glm::vec3 const& translation_vec) {

	glm::mat4 translation_mat{};

	translation_mat[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
	translation_mat[1] = glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f };
	translation_mat[2] = glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f };
	translation_mat[3] = glm::vec4{ translation_vec, 1.0f };

	Shape::translation_mat_ =  translation_mat * Shape::translation_mat_;
}


void Shape::update_w_t_mat() {
	world_transformation_ = translation_mat_ * rotation_mat_ * scale_mat_;
	world_transformation_inv_ = glm::inverse(world_transformation_);
}
