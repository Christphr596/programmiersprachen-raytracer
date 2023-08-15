// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include <map>
#include <memory>
#include <utility>
#include <cmath>
#include <algorithm>
#include "renderer.hpp"
#include "sphere.hpp"


Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
  , scene_(scene)
{}


void Renderer::rapid_prototyping() {
    for (auto& s : scene_.camera_container) {
        float distance = s->dis(width_, height_);
        float haight = s->height(width_, height_);
        for (unsigned int i = -(width_ % 2);i <= width_ / 2; i++) {
            for (unsigned int j = -(height_ % 2); j <= height_ % 2; j++) {
                Ray ray = s->ray_gen(j, distance, haight, width_);
            }
            Ray ray = s->ray_gen(i, distance, haight, width_);
        }
    }
}


Color Renderer::shade(Ray const& r, std::shared_ptr<Shape> const& s, HitPoint const& h) {

    glm::vec3 normale = s->normale(h.point);
    glm::vec3 point = h.point + 0.1f * normale;

    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;

    red += h.material->ka.r * 0.5f;
    green += h.material->ka.g * 0.5f;
    blue += h.material->ka.b * 0.5f;

    std::map<std::shared_ptr<Light>, glm::vec3> spotlights_vec{};

    for (auto l : scene_.light_container) {
        glm::vec3 light_vec = glm::normalize((l->position) - h.point);

        bool visible = true;
        for (auto i : scene_.shape_container) {
                HitPoint barrier = i->intersect(Ray{ point, light_vec });

                if (barrier.cut && barrier.distance < glm::distance(l->position, h.point) && barrier.distance > 0) {
                    visible = false;
                    break;
                }
            
        }

        if (visible) {
            spotlights_vec.insert(std::make_pair(l, light_vec));
        }
    }

    

    for (auto [l, l_vec] : spotlights_vec) {
        float skalar_n_l_vec = std::max( glm::dot(normale, l_vec), 0.0f);

        glm::vec3 r = glm::normalize(2 * skalar_n_l_vec * normale - l_vec);
        glm::vec3 v = glm::normalize(glm::vec3{ 0.0f, 0.0f, 0.0f } - h.point);
        float skalar_r_v = glm::dot(r, v);

        red += l->color.r * l->brightness * (h.material->kd.r * skalar_n_l_vec + h.material->ks.r * std::pow(skalar_r_v, h.material->m));
        green += l->color.g * l->brightness * (h.material->kd.g * skalar_n_l_vec + h.material->ks.g * std::pow(skalar_r_v, h.material->m));
        blue += l->color.b * l->brightness * (h.material->kd.b * skalar_n_l_vec + h.material->ks.b * std::pow(skalar_r_v, h.material->m));
    }

    

    return Color{red, green, blue};

}

Color Renderer::trace(Ray const& r) {

    HitPoint closest_hp{};
    std::shared_ptr<Shape> closest_s{};

    for (auto s : scene_.shape_container) {
        HitPoint hp = s->intersect(r);
        if (hp.cut) {
            if (hp.distance < closest_hp.distance) {
                closest_hp = hp;
                closest_s = s;
            }
        }
        
    }

    if (closest_hp.cut) {
        return shade(r, closest_s, closest_hp);
    }
    else {
        return Color{ 0.5f, 0.5f, 0.5f };
    }

    
}

void Renderer::render() {

    for (unsigned y = 0; y < height_; ++y) {
        for (unsigned x = 0; x < width_; ++x) {
            Pixel p{ x,y };
            Ray r{ glm::vec3{0.0f, 0.0f, 0.0f}, glm::normalize( glm::vec3{(-200.0f + float(x* 1.0f)), (-200.0f + float(y * 1.0f)), -400.0f})};
            Color c = trace(r);
            p.color = Color{ c.r / (c.r + 1), c.g / (c.g + 1), c.b / (c.b + 1) };

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
