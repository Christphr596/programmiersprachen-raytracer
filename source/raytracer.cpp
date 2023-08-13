#pragma once

#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "scene.hpp"

//now single threaded again
int main(int argc, char* argv[])
{
  unsigned const image_width = 401/*800*/;
  unsigned const image_height = 401/*600*/;
  std::string const filename = "./checkerboard.ppm";
  
  Scene s = parse_sdf("C:\\Users\\Hauptnutzer\\Uni\\Programmierung\\test_parser1.sdf");

  for (auto i: s.shape_container) {
      std::cout << i->get_name();
  }
  
  Renderer renderer{image_width, image_height, filename, parse_sdf("C:\\Users\\Hauptnutzer\\Uni\\Programmierung\\test_parser1.sdf")};

  renderer.render();

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  return 0;
}
