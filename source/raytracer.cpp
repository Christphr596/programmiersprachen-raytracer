#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "scene.hpp"

//now single th
int main(int argc, char* argv[])
{
  unsigned const image_width = /*401*/800;
  unsigned const image_height = /*401*/600;
  std::string const filename = "./checkerboard.ppm";
  
  Scene s = parse_sdf("../../test_1.sdf");

  
  for (auto i: s.shape_container) {
      std::cout << i->get_name() << "\n";

      std::cout << i->get_w_t_mat()[0][0] << " " << i->get_w_t_mat()[0][1] << " " << i->get_w_t_mat()[0][2] << " " << i->get_w_t_mat()[0][3] << "\n" ;
      std::cout << i->get_w_t_mat()[1][0] << " " << i->get_w_t_mat()[1][1] << " " << i->get_w_t_mat()[1][2] << " " << i->get_w_t_mat()[1][3] << "\n";
      std::cout << i->get_w_t_mat()[2][0] << " " << i->get_w_t_mat()[2][1] << " " << i->get_w_t_mat()[2][2] << " " << i->get_w_t_mat()[2][3] << "\n";
      std::cout << i->get_w_t_mat()[3][0] << " " << i->get_w_t_mat()[3][1] << " " << i->get_w_t_mat()[3][2] << " " << i->get_w_t_mat()[3][3] << "\n";
  }
  
  Renderer renderer{image_width, image_height, filename, parse_sdf("C:\\Users\\Annika\\00UNI\\SE1\\07Raytracer\\programmiersprachen-raytracer\\test_1.sdf")};

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
