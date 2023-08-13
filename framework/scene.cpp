
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>


#include "scene.hpp"


Scene parse_sdf(std::string const& sdf_path) {
	

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
				//std::cout << name;

				float value = 0.0f;

				std::array<float, 3> ka{};
				for (int i = 0; i < ka.size(); ++i) {
					string_stream >> value;
					ka[i] = value;
					//std::cout << ka[i];
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
					scene.shape_container.push_back(std::make_shared<Box>(box));

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
					scene.shape_container.push_back(std::make_shared<Sphere>(sphere));
				}

				
				
				if (token == "cylinder") {

					std::string name;
					string_stream >> name;

					std::array<float, 3> midpoint{};
					for (int i = 0; i < midpoint.size(); ++i) {
						string_stream >> value;
						midpoint[i] = value;
					}

					float radius = 0.0f;
					string_stream >> radius;

					float height = 0.0f;
					string_stream >> height;

					std::string name_mat;
					string_stream >> name_mat;

					auto it = scene.material_container.find(name_mat);
					std::shared_ptr<Material> mat = scene.material_container[name_mat];

					Cylinder cylinder{ name,  glm::vec3{midpoint[0], midpoint[1], midpoint[2]}, radius, height, mat };
					scene.shape_container.push_back(std::make_shared<Cylinder>(cylinder));
				}
				
				if (token == "cone") {

					std::string name;
					string_stream >> name;

					std::array<float, 3> vec{};
					for (int i = 0; i < vec.size(); ++i) {
						string_stream >> value;
						vec[i] = value;
					}

					float radius = 0.0f;
					string_stream >> radius;

					float height = 0.0f;
					string_stream >> height;

					std::string name_mat;
					string_stream >> name_mat;

					auto it = scene.material_container.find(name_mat);
					std::shared_ptr<Material> mat = scene.material_container[name_mat];

					Cone cone{ name,  glm::vec3{vec[0], vec[1], vec[2]}, radius, height, mat };
					scene.shape_container.push_back(std::make_shared<Cone>(cone));
				}
				
				if (token == "triangle") {

					std::string name;
					string_stream >> name;

					float value = 0.0f;

					std::array<float, 3> first{};
					for (int i = 0; i < first.size(); ++i) {
						string_stream >> value;
						first[i] = value;
					}

					std::array<float, 3> second{};
					for (int i = 0; i < second.size(); ++i) {
						string_stream >> value;
						second[i] = value;
					}

					std::array<float, 3> third{};
					for (int i = 0; i < third.size(); ++i) {
						string_stream >> value;
						third[i] = value;
					}

					std::string name_mat;
					string_stream >> name_mat;

					auto it = scene.material_container.find(name_mat);
					std::shared_ptr<Material> mat = scene.material_container[name_mat];

					Triangle triangle{ name, glm::vec3{first[0], first[1], first[2]}, glm::vec3{second[0], second[1], second[2]}, glm::vec3{third[0], third[1], third[2]}, mat };
					scene.shape_container.push_back(std::make_shared<Triangle>(triangle));
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

				Camera camera{ name, fov_x, glm::vec3{eye[0], eye[1], eye[2]},  glm::vec3{dir[0], dir[1], dir[2]}, glm::vec3{up[0], up[1], up[2]}};
				scene.camera_container.push_back(std::make_shared<Camera>(camera));
			}
			

		}

	}
	return scene;
}

