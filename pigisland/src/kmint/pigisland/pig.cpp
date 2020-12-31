#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
	namespace pigisland {


	pig::pig(math::vector2d location, Chromosomes chromosomes, pigisland::shark& shark, pigisland::boat& boat)
			: play::free_roaming_actor{ location },
			drawable_{ *this, pig_image() }, chromosomes_{ chromosomes }, shark(shark), boat(boat) {

		SteeringBehaviors steeringBehaviors;
	}

void pig::act(delta_time dt) {
	SteeringBehaviors steeringBehaviors;
	kmint::math::vector2d steeringForce = steeringBehaviors.calculate(*this, boat.location(), shark.location());

	//calculate the combined force from each steering behavior in the pigs list
	kmint::math::vector2d acceleration = steeringForce / mass();

	//update velocity 
	v_ += acceleration * to_seconds(dt);

	//make sure pig does not exceed maximum velocity
	v_ = steeringBehaviors.truncate(v_, maxSpeed());

	//update the position
	move(v_ * to_seconds(dt));

	//update the heading if the pig has a velocity greater than a very small value
	// dot of product > 0.00000001
	if ((v_.x() * v_.x() + v_.y() * v_.y()) > 0.00000001) {
	 heading_ = steeringBehaviors.normalize(v_);
	 side_ = steeringBehaviors.perp(heading_);
	}
	
	// make the pigs not overlap eachother
	//steeringBehaviors.enforceNonPenetrationConstraint(*this);
}

} // namespace pigisland

} // namespace kmint
