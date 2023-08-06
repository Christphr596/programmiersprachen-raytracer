// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include "sphere.hpp"


Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
{}

Color Renderer::shade(Ray const& r, Shape const& s) {
    return Color{1.0f, 0.0f, 0.0f};

}

Color Renderer::trace(Ray const& r) {

    Sphere s{ glm::vec3{0.0f, 0.0f, -600.0f}, 100.0f };

    if (s.intersect(r).cut) {
        return shade(r, s);
    }
    else {
        return Color{ 1.0f, 1.0f, 1.0f };
    }

}

void Renderer::render() {

    for (unsigned y = 0; y < height_; ++y) {
        for (unsigned x = 0; x < width_; ++x) {
            Pixel p{ x,y };
            Ray r{ glm::vec3{0.0f, 0.0f, 0.0f}, glm::normalize( glm::vec3{(-200.0f + float(x* 1.0f)), (-200.0f + float(y * 1.0f)), -400.0f})};
            p.color = trace(r);

            write(p);
        }
    }
    ppm_.save(filename_);

}

/*void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}*/

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
