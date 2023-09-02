//#pragma once

#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <map>
#include "light.hpp"
#include "camera.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "composite.hpp"

struct Scene {

	std::map<std::string, std::shared_ptr<Material>> material_container{};
	std::shared_ptr<Composite> root = std::make_shared<Composite>(Composite{ "composite_" });
	std::vector<std::shared_ptr<Camera>> camera_container;
	std::vector<std::shared_ptr<Light>> light_container;

};

Scene parse_sdf(std::string const& sdf_path);

#endif 