#include <renderer.hpp>
#include <window.hpp>
#include <fstream>
#include <ostream>
#include <iostream>
#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "scene.hpp"



int main(int argc, char* argv[])
{
    unsigned const image_width =  800;
    unsigned const image_height = 600;


    std::ifstream main_source("../../video.sdf");//Quelldatei in Binär öffnen

    for (int i = 105; i <= 135; i++) {
        std::string const filename = "./image" + std::to_string(i) + ".ppm";
        main_source.seekg(0);
        std::ofstream image_source("../image" + std::to_string(i) + ".sdf", std::ios::trunc); //neue Datei auch im binären Modus(für Zeilenumbrüche)

        image_source << main_source.rdbuf();

        image_source << "\n" << "define transform c translate 0 0 " << (0.5 * i);
        image_source << "\n" << "define transform c rotate " << (i) << " 0 0 1";

        if(i >110 && i <= 130){
            image_source << "\n" << "define transform bullett translate " << (i -110)*0.25 << " " << (i-110)*0.25 << " 0";
        }

        if (i > 130 && i <= 140) {
            image_source << "\n" << "define transform bullett translate 5 5 0";
        }

        if (i > 140 && i <= 160) {
            image_source << "\n" << "define transform bullett translate " << 5- (i - 140) * 0.25 << " " << 5- (i - 140) * 0.25 << " 0";
        }

        image_source.close();

        Scene s = parse_sdf("../image" + std::to_string(i) + ".sdf");

        Renderer renderer{image_width, image_height, filename,s};

       renderer.render();
    }

    main_source.close();

    return 0;
}

/*
//now single th
int main(int argc, char* argv[])
{
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./image.ppm";
  

  Scene s = parse_sdf("../../video.sdf");
  Renderer renderer{image_width, image_height, filename,s };
  renderer.render();


 


  
  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }

    window.show(renderer.color_buffer());
  }

  return 0;
}*/

