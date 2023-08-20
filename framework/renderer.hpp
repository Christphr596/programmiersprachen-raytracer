// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include "Ray.hpp"
#include "shape.hpp"
#include "hitpoint.hpp"
#include "scene.hpp"
#include <string>
#include <glm/glm.hpp>
#include <memory>

class Renderer
{
public:
    Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene);

  void rapid_prototyping();
  void render();
  Color trace(Ray const& r);
  Color shade(Ray const& r, std::shared_ptr<Shape> const& s, HitPoint const& h);
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
  Scene scene_;
};

#endif // #ifndef BUW_RENDERER_HPP
