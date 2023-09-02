#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <utility>
#include "composite.hpp"
#include "shape.hpp"

#include "scene.hpp"


Scene parse_sdf(std::string const& sdf_path) {
	
	std::map<std::string, std::shared_ptr<Shape>> open_shapes;
	std::map<std::string, std::shared_ptr<Shape>> all_shapes;
	int size = open_shapes.size();

	Scene scene{};

	std::ifstream f_stream{sdf_path};

	if (!f_stream.is_open()) {
		std::cout << "Cannot open file\n";
		return scene;
	}
	
	std::string line_buffer;
	while (std::getline(f_stream, line_buffer)) {
		std::istringstream string_stream{ line_buffer };

		std::string token;

		string_stream >> token;
		if (token == "define") {
			string_stream >> token;

			//parse material
			if (token == "material") {
				std::string name;
				string_stream >> name;

				float value = 0.0f;

				std::array<float, 3> ka{};
				for (int i = 0; i < ka.size(); ++i) {
					string_stream >> value;
					ka[i] = value;
				}

				std::array<float, 3> kd{};
				for (int i = 0; i < ka.size(); ++i) {
					string_stream >> value;
					kd[i] = value;
				}

				std::array<float, 3> ks{};
				for (int i = 0; i < ka.size(); ++i) {
					string_stream >> value;
					ks[i] = value;
				}

				float m = 0.0f;
				string_stream >> m;


				Material mat{ name, Color{ka[0], ka[1], ka[2]}, Color{kd[0], kd[1], kd[2]}, Color{ks[0], ks[1], ks[2]}, m };

				scene.material_container.insert(std::make_pair(name, std::make_shared<Material>(mat)));
			}

			//parse geometric objects
			if (token == "shape") {
				
				float value = 0.0f;
				string_stream >> token;

				if (token == "box") {
					std::string name;
					string_stream >> name;

					std::array<float, 3> vec1{};
					for (int i = 0; i < vec1.size(); ++i) {
						string_stream >> value;
						vec1[i] = value;
					}

					std::array<float, 3> vec2{};
					for (int i = 0; i < vec2.size(); ++i) {
						string_stream >> value;
						vec2[i] = value;
					}

					std::string name_mat;
					string_stream >> name_mat;

					auto it = scene.material_container.find(name_mat);
					std::shared_ptr<Material> mat = scene.material_container[name_mat];

					Box box{ name, glm::vec3{vec1[0], vec1[1], vec1[2]},  glm::vec3{vec2[0], vec2[1], vec2[2]}, mat };
					auto box_ptr = std::make_shared<Box>(box);

					all_shapes.insert(std::make_pair(name, box_ptr));
					open_shapes.insert(std::make_pair(name, box_ptr));

				}
				if (token == "sphere") {

					std::string name;
					string_stream >> name;

					std::array<float, 3> vec{};
					for (int i = 0; i < vec.size(); ++i) {
						string_stream >> value;
						vec[i] = value;
					}

					float radius = 0.0f;
					string_stream >> radius;

					std::string name_mat;
					string_stream >> name_mat;

					auto it = scene.material_container.find(name_mat);
					std::shared_ptr<Material> mat = scene.material_container[name_mat];

					Sphere sphere{ name,  glm::vec3{vec[0], vec[1], vec[2]}, radius, mat };
					auto sphere_ptr = std::make_shared<Sphere>(sphere);

					all_shapes.insert(std::make_pair(name, sphere_ptr));
					open_shapes.insert(std::make_pair(name, sphere_ptr));
				}
				
				if (token == "composite") {

					std::string name;
					string_stream >> name;

					Composite composite{ name };

					std::string new_word{};
					
					while (!string_stream.eof()) {
						string_stream >> new_word;
						composite.add_shape(open_shapes.at(new_word));
						std::cout << name << "*\n";
						open_shapes.erase(new_word);

					}
						
					auto composite_ptr = std::make_shared<Composite>(composite);

					all_shapes.insert(std::make_pair(name, composite_ptr));
					open_shapes.insert(std::make_pair(name, composite_ptr));
					
				}

			}

			//parse light
			if (token == "light") {
				std::string name;
				string_stream >> name;

				float value = 0.0f;

				std::array<float, 3> position{};
				for (int i = 0; i < position.size(); ++i) {
					string_stream >> value;
					position[i] = value;
				}

				std::array<float, 3> color{};
				for (int i = 0; i < position.size(); ++i) {
					string_stream >> value;
					color[i] = value;
				}

				float brightness = 0.0f;
				string_stream >> brightness;

				Light light{ name, glm::vec3{position[0], position[1], position[2]}, Color{color[0], color[1], color[2]}, brightness };
				scene.light_container.push_back(std::make_shared<Light>(light));
			}

			if (token == "camera") {
				std::string name;
				string_stream >> name;

				float fov_x = 0.0f;
				string_stream >> fov_x;

				float value = 0.0f;
				std::array<float, 3> eye{};
				for (int i = 0; i < eye.size(); ++i) {
					string_stream >> value;
					eye[i] = value;
				}

				std::array<float, 3> dir{};
				for (int i = 0; i < dir.size(); ++i) {
					string_stream >> value;
					dir[i] = value;
				}

				std::array<float, 3> up{};
				for (int i = 0; i < up.size(); ++i) {
					string_stream >> value;
					up[i] = value;
				}

				Camera camera{ name, fov_x, glm::vec3{eye[0], eye[1], eye[2]},  glm::vec3{dir[0], dir[1], dir[2]}, glm::vec3{up[0], up[1], up[2]} };
				scene.camera_container.push_back(std::make_shared<Camera>(camera));
			}

			
			if (token == "transform") {


				float value;
				std::string name;
				string_stream >> name;

				string_stream >> token;

				if (token == "scale") {

					std::array<float, 3> scale{};
					for (int i = 0; i < scale.size(); ++i) {
						string_stream >> value;
						scale[i] = value;
					}
					all_shapes.at(name)->scale(glm::vec3{scale[0], scale[1], scale[2]});
				}

				if (token == "translate") {

					std::array<float, 3> trans{};
					for (int i = 0; i < trans.size(); ++i) {
						string_stream >> value;
						trans[i] = value;
					}
					all_shapes.at(name)->translate(glm::vec3{trans[0], trans[1], trans[2]});
				}

				if (token == "rotate") {

					float degree = 0.0f;
					string_stream >> degree;

					std::array<float, 3> rot{};
					for (int i = 0; i < rot.size(); ++i) {
						string_stream >> value;
						rot[i] = value;
					}
					all_shapes.at(name)->rotate(degree, glm::vec3{rot[0], rot[1], rot[2]});
				}

				all_shapes.at(name)->update_w_t_mat();

			}
		}
	}

	for (auto [name, ptr] : open_shapes) {
		scene.root->add_shape(ptr);
		std::cout << name;
	}

	return scene;
}

