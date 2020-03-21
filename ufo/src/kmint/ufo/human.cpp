#include "kmint/ufo/human.hpp"
#include "kmint/random.hpp"
#include <string>
#include <iostream>

namespace kmint::ufo {

namespace {
constexpr char const *image_path = "resources/human.png";

graphics::image human_image() { return graphics::image{image_path}; }

math::vector2d random_location() {

  //prevent from spawning in/ontop buildings
	float random_x = random_scalar(60, 900);//900
	float random_y = random_scalar(60, 700);//700

	if (random_x >= 575 && random_x <= 735 | random_y >= 60 && random_y <= 137) {
		random_x = random_scalar(745, 900);
		random_y = random_scalar(137, 700);
	}

	if (random_x >= 575 && random_x <= 665 | random_y >= 200 && random_y <= 310) {
		random_x = random_scalar(60, 570);
		random_y = random_scalar(310, 700);
	}

	if (random_x >= 575 && random_x <= 685 | random_y >= 400 && random_y <= 490) {
		random_x = random_scalar(60, 570);
		random_y = random_scalar(490, 700);
	}

	if (random_x >= 320 && random_x <= 440 | random_y >= 500 && random_y <= 630) {
		random_x = random_scalar(440, 900);
		random_y = random_scalar(130, 700);
	}

	if (random_x >= 430 && random_x <= 510 | random_y >= 460 && random_y <= 610) {
		random_x = random_scalar(500, 900);
		random_y = random_scalar(620, 700);
	}

  return { random_x, random_y };
}

} // namespace
human::human()
	: play::free_roaming_actor{ random_location() },
	drawable_{ *this, human_image() } {
}

void human::act(delta_time dt) {
	move(v_ * to_seconds(dt));
}

} // namespace kmint::ufo
