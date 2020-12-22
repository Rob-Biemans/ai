#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {


pig::pig(math::vector2d location)
  : play::free_roaming_actor{location},
    drawable_{*this, pig_image()} {

	//v_ = math::vector2d(steeringBehaviors_.randomFloat(-0.0008, 0.0008), steeringBehaviors_.randomFloat(-0.0008, 0.00080));
}

void pig::act(delta_time dt) {
	//kmint::math::vector2d force;
	//math::vector2d steeringForce;

	////calculate the combined force from each steering behavior in the pigs list
	//math::vector2d SteeringForce = steeringForce->calculate();
	////Acceleration = Force/Mass
	//SVector2D acceleration = SteeringForce / m_dMass;

	////update velocity 
	//v_ += acceleration * to_seconds(dt);

	////make sure pig does not exceed maximum velocity
	//m_vVelocity.Truncate(m_dMaxSpeed);

	//update the position
	move(v_ * to_seconds(dt));

	//update the heading if the pig  has a velocity greater than a very small value
	//if (v_.LengthSq() > 0.00000001) {
	// heading_ = Vec2DNormalize(v_);
	// side_ = heading_.Perp();
	//}
}

} // namespace pigisland

} // namespace kmint
