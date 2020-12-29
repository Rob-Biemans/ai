#ifndef KMINT_PIGISLAND_STEERINGBEHAVIORS_H
#define KMINT_PIGISLAND_STEERINGBEHAVIORS_H
#include "kmint/math/vector2d.hpp"
#include "kmint/random.hpp"
#include <vector>

#include "./pig.hpp"
#include "wall2D.h"

namespace kmint {
	namespace pigisland {
		class pig;
	}
}

namespace kmint {
namespace pigisland {

	class SteeringBehaviors {
		private:
			std::vector<math::vector2d> m_Feelers = std::vector<math::vector2d>(3);
			kmint::math::vector2d wanderTarget;
			double wanderRadius = 0.35;
			double wanderDistance = 0.25;
			double wanderJitter = 1.0;
			std::vector<Wall2D> walls_;
		public:
			SteeringBehaviors();

			kmint::math::vector2d wander(pig& m_pig_);
			kmint::math::vector2d seek(kmint::math::vector2d target, pig& m_pig_);
			kmint::math::vector2d flee(kmint::math::vector2d target, pig& m_pig_);
			kmint::math::vector2d cohesion(std::vector<pig *>& neighbors, pig& m_pig_);
			kmint::math::vector2d separation(std::vector<pig *>& neighbors, pig& m_pig_);
			kmint::math::vector2d alignment(std::vector<pig *>& neighbors, pig& m_pig_);

			void calcWalls();
			kmint::math::vector2d wallAvoidance(pig& m_pig_);
			void createFeelers(pig& m_pig_);
			void vec2DRotateAroundOrigin(kmint::math::vector2d& v, double ang);
			bool lineIntersection2D(kmint::math::vector2d A,
				kmint::math::vector2d B,
				kmint::math::vector2d C,
				kmint::math::vector2d D,
				double& dist,
				kmint::math::vector2d& point);
			double vec2DDistance(const kmint::math::vector2d &v1, const kmint::math::vector2d &v2);
			double vec2DDistanceSq(const kmint::math::vector2d &v1, const kmint::math::vector2d &v2);

			kmint::math::vector2d normalize(kmint::math::vector2d target);
			float calcVectorLength(kmint::math::vector2d target);

			kmint::math::vector2d truncate(kmint::math::vector2d target, double max);
			kmint::math::vector2d perp(kmint::math::vector2d target);

			kmint::math::vector2d pointToWorldSpace(const kmint::math::vector2d& point,
				const kmint::math::vector2d& heading,
				const kmint::math::vector2d& side,
				const kmint::math::vector2d& position);

			float randomFloat(float min, float max);
			kmint::math::vector2d calculate(pig& m_pig_);
	};
} // namespace pigisland
} // namespace kmint

#endif
