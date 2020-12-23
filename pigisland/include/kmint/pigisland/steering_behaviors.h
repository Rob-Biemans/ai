#pragma once
#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"
#include <random>
#include <vector>

#include "kmint/pigisland/pig.hpp"
#include "wall2D.h"

namespace kmint {
namespace pigisland {

	class SteeringBehaviors {
		public:
			SteeringBehaviors(pig & pig) : m_pig_(pig) {}

			kmint::math::vector2d seek(kmint::math::vector2d target);
			kmint::math::vector2d flee(kmint::math::vector2d target);
			kmint::math::vector2d cohesion(std::vector<pig *>& neighbors);
			kmint::math::vector2d separation(std::vector<pig *>& neighbors);
			kmint::math::vector2d alignment(std::vector<pig *>& neighbors);

			kmint::math::vector2d wallAvoidance(const std::vector<Wall2D>& walls);
			void SteeringBehaviors::CreateFeelers();

			kmint::math::vector2d normalize(kmint::math::vector2d target);
			double calcVectorLength(kmint::math::vector2d target);

			float randomFloat(float min, float max);
			void calculate();
		protected:
			pig & m_pig_;
			std::vector<math::vector2d> m_Feelers = std::vector<math::vector2d>(3);
	};
} // namespace pigisland
} // namespace kmint
