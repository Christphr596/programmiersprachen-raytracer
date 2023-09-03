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
#include <glm/gtc/matrix_access.hpp>
#include "renderer.hpp"
#include "sphere.hpp"
#define OWN_PI 3.14159265359f


Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
  , scene_(scene)
{}

Color Renderer::shade(Ray const& ray,  HitPoint const& h) const { //Berechnet die Farbe die ein Material an einem Punkt hat

    glm::vec3 normale = h.normale;
    glm::vec3 point = h.point + 0.1f * normale; // Schiebt Schnittpunkt etwas von der Oberfläche des Objektes weg, um Shadow Acne zu vermeiden

    float red = 0.0f;
    float green = 0.0f;
    float blue = 0.0f;

    //ambiente Beleuchtung
    red += h.material->ka.r * 0.5f;
    green += h.material->ka.g * 0.5f;
    blue += h.material->ka.b * 0.5f;

    //diffuse und spekulare Beleuchtung
    for (auto l : scene_.light_container) {
        glm::vec3 light_vec = glm::normalize((l->position) - h.point); //Vektor der vom Hitpoint zur Lichtquelle geht

        //Prüfung ob ein anderes Objekt zwischen dem Hitpoint und der Lichtquelle liegt
        bool visible = true; //Lichtquelle ist vom Hitpoint aus sichtbar
        HitPoint barrier = scene_.root->intersect(Ray{ point, light_vec });

        if (barrier.cut && barrier.distance < glm::distance(l->position, h.point) && barrier.distance > 0) { //Prüfung ob es eine Intersection gibt und ob diese im Bereich zwischen Hitpoint und Lichtquelle liegt (oder eben davor oder dahinter)
            visible = false;
        }

        if (visible) {
            //Berechnung der diffusen und spekularen Werte
            float skalar_n_l_vec = std::max(glm::dot(normale, light_vec), 0.0f);

            glm::vec3 r = glm::normalize(2 * skalar_n_l_vec * normale - light_vec);
            glm::vec3 v = glm::normalize(ray.origin - h.point);
            float skalar_r_v = std::max(glm::dot(r, v), 0.0f);

            red += l->color.r * l->brightness * (h.material->kd.r * skalar_n_l_vec + h.material->ks.r * std::pow(skalar_r_v, h.material->m));
            green += l->color.g * l->brightness * (h.material->kd.g * skalar_n_l_vec + h.material->ks.g * std::pow(skalar_r_v, h.material->m));
            blue += l->color.b * l->brightness * (h.material->kd.b * skalar_n_l_vec + h.material->ks.b * std::pow(skalar_r_v, h.material->m));
        }
    }
    
    return Color{red, green, blue};

}

Color Renderer::trace(Ray const& r) const{ //Berechnet welches Material(bzw kein Material) mit dem Strahl eines Pixels getroffen wird
    
    HitPoint hp = scene_.root->intersect(r);//Welches Objekt (Material) wird mit dem übergebenen Strahl getroffen

    if (hp.cut) { //Wenn ein Objekt getroffen wird, wird die Farbe des Materials an der Stelle berechnet und zurückgegeben
        return shade(r,hp);
    }
    else {//Wenn kein Objekt getroffen wurde, wird die Hintergrundfarbe zurückgegeben
        return Color{ 0.5f, 0.5f, 0.5f };
    }

    
}

void Renderer::render() { //Schießt Strahlen für jedes einzelne Pixel in die Scene und ordnet so jedem Pixel des Bildes eine Farbe zu

    std::shared_ptr<Camera> c = scene_.camera;

    float d = (width_ / 2.0f) / std::tan((c->fov_x / 2) / 180 * OWN_PI);//Entfernung des Kameraursprungs zur Bildfläche

    //Berechnung der Kameratransformationsmatrix
    glm::mat4 camera_mat{};
    camera_mat[0] = glm::vec4(glm::cross(c->dir, c->up), 0);
    camera_mat[1] = glm::vec4(glm::cross(glm::cross(c->dir, c->up), c->dir), 0);
    camera_mat[2] = glm::vec4(-1.0f * (c->dir), 0);
    camera_mat[3] = glm::vec4(c->eye, 1);
    

    for (unsigned y = 0; y < height_; ++y) {
        for (unsigned x = 0; x < width_; ++x) {
            Pixel p{ x,y };

            glm::vec4 ray_direction{ glm::normalize(glm::vec3{(-(width_ / 2.0f) + float(x * 1.0f)), (-(height_ / 2.0f) + float(y * 1.0f)), -d}), 0 };// Berechnung der Strahlenrichtung

            ray_direction = glm::normalize(camera_mat * ray_direction);//Transformation der Strahlenrichtung (Kameratransformation)

            Ray r{ c->eye, glm::vec3{ray_direction.x, ray_direction.y, ray_direction.z} };//Erstellen des Strahls
            Color c = trace(r);//Gibt die Farbe des Pixels zurück
            p.color = Color{ c.r / (c.r + 1), c.g / (c.g + 1), c.b / (c.b + 1) };

            write(p);//Pixel mit jetzt neuer Farbe wird in Color Buffer geschrieben
        }
    }
    ppm_.save(filename_);

}


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
