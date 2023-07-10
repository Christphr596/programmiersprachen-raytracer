#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <glm/vec3.hpp>
#include <Box.hpp>
#include <shape.hpp>
//#include <sphere.hpp>
//#include <glm/glm.hpp>
//#include <glm/gtx/intersect.hpp>
#include <iostream>
#include "scene.hpp"

/*
TEST_CASE("intersect_ray_sphere", "[intersect]") {
	// Ray
	glm::vec3 ray_origin{ 0.0f, 0.0f, 0.0f };
	// ray direction has to be normalized !
	// you can use :
	// v = glm :: normalize ( some_vector )
	glm::vec3 ray_direction{ 0.0f, 0.0f, 1.0f };
	// Sphere
	glm::vec3 sphere_center{ 0.0f, 0.0f, 5.0f };
	float sphere_radius{ 1.0f };
	float distance = 0.0f;
	auto result = glm::intersectRaySphere(
		ray_origin, ray_direction, 
		sphere_center, 
		sphere_radius * sphere_radius, 
		distance);

	REQUIRE(distance == Approx(4.0f));
}


TEST_CASE("test_intersect", "[intersect]") {

	
	Sphere r1{ std::string {"red1"}, glm::vec3 {0.0f,8.0f,0.0f}, float {4.0f}, Color {255,0,0} };
	Sphere y1{ std::string {"yellow1"}, glm::vec3 {0.0f,0.0f,7.0f}, float {1.0f}, Color {255,255,0} };
	Ray x{ glm::vec3{0,0,0} , glm::vec3{1,0,0} };
	Ray y{ glm::vec3{0,0,0} , glm::vec3{0,1,0} };
	Ray z{ glm::vec3{0,0,0} , glm::vec3{0,0,1} };
	float r1_x_dis = 0.0f;
	float r1_y_dis = 0.0f;
	float r1_z_dis = 0.0f;

	float y1_x_dis = 0.0f;
	float y1_y_dis = 0.0f;
	float y1_z_dis = 0.0f;
	HitPoint r1_x = r1.intersect(x, r1_x_dis);
	HitPoint r1_y = r1.intersect(y, r1_y_dis);
	HitPoint r1_z = r1.intersect(z, r1_z_dis);

	HitPoint y1_x = y1.intersect(x, y1_x_dis);
	HitPoint y1_y = y1.intersect(y, y1_y_dis);
	HitPoint y1_z = y1.intersect(z, y1_z_dis);

	REQUIRE(r1_x.cut == false);
	REQUIRE(r1_z.cut == false);
	REQUIRE(y1_x.cut == false);
	REQUIRE(y1_y.cut == false);

	REQUIRE(r1_y.cut == true);
	REQUIRE(r1_y.distance == 4.0f);
	REQUIRE(r1_y.color.r == 255);
	REQUIRE(r1_y.color.g == 0);
	REQUIRE(r1_y.color.b == 0);
	REQUIRE(r1_y.direction == glm::vec3{ 0,1,0 });
	REQUIRE(r1_y.name == std::string{ "red1" });
	REQUIRE(r1_y.point == glm::vec3{ 0,4,0 });


	REQUIRE(y1_z.cut == true);
	REQUIRE(y1_z.distance == 6.0f);
	REQUIRE(y1_z.color.r == 255);
	REQUIRE(y1_z.color.g == 255);
	REQUIRE(y1_z.color.b == 0);
	REQUIRE(y1_z.direction == glm::vec3{ 0,0,1 });
	REQUIRE(y1_z.name == std::string{ "yellow1" });
	REQUIRE(y1_z.point == glm::vec3{ 0,0,6 });
}




TEST_CASE("area_sphere") {
	
	Sphere sphere1 (glm::vec3{ 0,0,0 }, 3);
	Sphere sphere2 (glm::vec3{ 0,0,0 }, 5);
		
	float area1 = sphere1.area();
	float area2 = sphere2.area();
	REQUIRE(area1 == Approx(113.097f));
	REQUIRE(area2 == Approx(314.159f));
}


TEST_CASE("volume_sphere") {

	Sphere sphere1(glm::vec3{ 0,0,0 }, 3);
	Sphere sphere2(glm::vec3{ 0,0,0 }, 5);

	float volume1 = sphere1.volume();
	float volume2 = sphere2.volume();
	REQUIRE(volume1 == Approx(113.097f));
	REQUIRE(volume2 == Approx(523.599f));
}

TEST_CASE("area_box") {

	Box box1(glm::vec3{ 0,0,0 }, glm::vec3{ 3,4,5 });
	Box box2(glm::vec3{ 1,2,3 }, glm::vec3{ 4,4,4 });

	float area1 = box1.area();
	float area2 = box2.area();
	REQUIRE(area1 == Approx(94.0f));
	REQUIRE(area2 == Approx(22.0f));
}


TEST_CASE("volume_box") {

	Box box1(glm::vec3{ 0,0,0 }, glm::vec3{ 3,4,5 });
	Box box2(glm::vec3{ 1,2,3 }, glm::vec3{ 4,4,4 });

	float volume1 = box1.volume();
	float volume2 = box2.volume();
	REQUIRE(volume1 == Approx(60.0f));
	REQUIRE(volume2 == Approx(6.0f));
}



TEST_CASE("destruktor", "[virtual]") {
	Color red{ 255,0,0 };
	glm::vec3 position{ 0.0f,0.0f,0.0f };

	Sphere* s1 = new Sphere(std::string{ "sphere0" }, position, float{ 1.2f }, red);
	Shape* s2 = new Sphere(std::string{ "sphere1" }, position, float{ 1.2f }, red);

	s1->print(std::cout);
	s2->print(std::cout);

	delete s1;
	delete s2;
}













TEST_CASE("volume_box") {
	Color red{ 255,0,0 };
	glm::vec3 position{ 0.0f,0.0f,0.0f };

	std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>("sphere0", position, 1.2f, red);
	std::shared_ptr<Shape> s2 = std::make_shared<Sphere>("sphere1", position, 1.2f, red);

	s1->print(std::cout);
	s2->print(std::cout);
}
*/


TEST_CASE(" parse sdf file to scene object", "[parse_sdf]") {

	Scene scene{};
	Scene s = parse_sdf("C:\\Users\\Annika\\00UNI\\SE1\\06Aufgabe\\programmiersprachen-raytracer\\scene_1.sdf");

	for (auto i : s.material_container) {
		std::cout << i->name << "\n";
	}

}


TEST_CASE("test_intersect", "[intersect]") {

	Material ma{ "material", Color{ 1.0f, 0.0f, 0.0f }, Color{ 0.0f, 1.0f, 0.0f }, Color{ 0.0f, 0.0f, 1.0f }, float{ 4.5f } };
	std::shared_ptr<Material> mat = std::make_shared<Material>(ma);

	Box r1{ "red1", glm::vec3 {-1.0f,-1.0f,6.0f}, glm::vec3 {1.0f,1.0f,7.0f}, 	mat };
	Box y1{ "yellow1", glm::vec3 {0.0f,4.0f,0.0f}, glm::vec3 {1.0f,5.0f,1.0f}, 	mat };
	Box g1{ "green1", glm::vec3 {4.0f,-1.0f,0.0f}, glm::vec3 {5.0f,1.0f,1.0f}, 	mat };

	Ray x{ glm::vec3{0,0,0} , glm::vec3{1,0,0} };
	Ray y{ glm::vec3{0,0,0} , glm::vec3{0,1,0} };
	Ray z{ glm::vec3{0,0,0} , glm::vec3{0,0,1} };
	Ray mz{ glm::vec3{0,0,0} , glm::vec3{0,0,-1} };
	
	HitPoint r1_mz = r1.intersect(mz);
	HitPoint r1_x = r1.intersect(x);
	HitPoint r1_y = r1.intersect(y);
	HitPoint r1_z = r1.intersect(z);
	

	HitPoint y1_x = y1.intersect(x);
	HitPoint y1_y = y1.intersect(y);
	HitPoint y1_z = y1.intersect(z);
	HitPoint y1_mz = y1.intersect(mz);

	HitPoint g1_x = g1.intersect(x);
	HitPoint g1_y = g1.intersect(y);
	HitPoint g1_z = g1.intersect(z);
	HitPoint g1_mz = g1.intersect(mz);
	
	REQUIRE(r1_x.cut == false);
	REQUIRE(r1_y.cut == false);
	REQUIRE(r1_mz.cut == false);
	REQUIRE(y1_x.cut == false);
	REQUIRE(y1_z.cut == false);
	REQUIRE(y1_mz.cut == false);
	REQUIRE(g1_z.cut == false);
	REQUIRE(g1_y.cut == false);
	REQUIRE(g1_mz.cut == false);

	REQUIRE(r1_z.cut == true);
	REQUIRE(r1_z.distance == 6.0f);
	REQUIRE(r1_z.material == mat);
	REQUIRE(r1_z.direction == glm::vec3{ 0,0,1 });
	REQUIRE(r1_z.name == std::string{ "red1" });
	REQUIRE(r1_z.point == glm::vec3{ 0,0,6 });

	REQUIRE(y1_y.cut == true);
	REQUIRE(y1_y.distance == 4.0f);
	REQUIRE(y1_y.material == mat);
	REQUIRE(y1_y.direction == glm::vec3{ 0,1,0 });
	REQUIRE(y1_y.name == std::string{ "yellow1" });
	REQUIRE(y1_y.point == glm::vec3{ 0,4,0 });

	REQUIRE(g1_x.cut == true);
	REQUIRE(g1_x.distance == 4.0f);
	REQUIRE(g1_x.material == mat);
	REQUIRE(g1_x.direction == glm::vec3{ 1,0,0 });
	REQUIRE(g1_x.name == std::string{ "green1" });
	REQUIRE(g1_x.point == glm::vec3{ 4,0,0 });


}



int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
