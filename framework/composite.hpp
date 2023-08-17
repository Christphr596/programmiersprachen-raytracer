
#include <glm/vec3.hpp>
#include <string>
#include "shape.hpp"
#include "color.hpp"
#include "Ray.hpp"
#include "hitpoint.hpp"
#include <vector>

/*
class Composite : public Shape {
public:
	Composite(std::string const& name);

	//void draw() const;
	void add_shape(std::shared_ptr<Shape> shape);
	void remove_shape(std::string const& name);
	std::vector<std::shared_ptr<Shape>> get_children()const;

	float area() const override;
	float volume() const override;
	HitPoint intersect(Ray const& r) override;

private: 
	std::string name_ = "";
	std::vector<std::shared_ptr<Shape>> container;
};

*/
