#ifndef KMINT_PIGISLAND_STEERING_BEHAVIORS_HPP
#define KMINT_PIGISLAND_STEERING_BEHAVIORS_HPP

#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"
#include <random>
#include <vector>

#include "./pig.hpp"

namespace kmint {
	namespace pigisland {

		class SteeringBehaviors {
		public:
			SteeringBehaviors(pig & pig) : m_pig_(pig) {};

			kmint::math::vector2d seek(kmint::math::vector2d target);
			//kmint::math::vector2d flee(kmint::math::vector2d target);
			//kmint::math::vector2d cohesion(const std::vector<pig *>& neighbors);
			//kmint::math::vector2d separation(std::vector<pig *>& neighbors);
			//kmint::math::vector2d alignment(std::vector<pig *>& neighbors);

			//kmint::math::vector2d wallavoidance(const std::vector<Wall2D>& walls);

			//kmint::math::vector2d normalize(kmint::math::vector2d target);
			//double calcVectorLength(kmint::math::vector2d target);

			float randomFloat(float min, float max);
			//void calculate();
		protected:
			pig & m_pig_;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_STEERING_BEHAVIORS_HPP */
