#include "kmint/pigisland/steering_behaviors.h"

namespace kmint {
namespace pigisland {

	float SteeringBehaviors::randomFloat(float min, float max) {
		static std::default_random_engine e;
		static std::uniform_real_distribution<float> dis(min, max);
		return dis(e);
	}

	kmint::math::vector2d SteeringBehaviors::seek(kmint::math::vector2d target) {
		kmint::math::vector2d desiredVelocity = normalize(target - m_pig_.location()) * m_pig_.maxSpeed();

		return (desiredVelocity - m_pig_.velocity());
	}
	
	
	kmint::math::vector2d SteeringBehaviors::normalize(kmint::math::vector2d target)
	{
		double vector_length = calcVectorLength(target);

		if (vector_length > std::numeric_limits<double>::epsilon())
		{
			target.x(target.x() / vector_length);
			target.y(target.y() / vector_length);
		}
		return target;
	}

	double SteeringBehaviors::calcVectorLength(kmint::math::vector2d target) {
		return std::sqrt(std::pow(target.x(), 2) + std::pow(target.y(), 2));
	}

	kmint::math::vector2d SteeringBehaviors::flee(kmint::math::vector2d target) {

	}
	
	kmint::math::vector2d SteeringBehaviors::cohesion(std::vector<pig *>& neighbors) {

		kmint::math::vector2d SteeringForce;

		for (int a = 0; a < neighbors.size(); ++a) {
			//make sure this agent isn't included in the calculations and that
			//the agent being examined is close enough. 
			if ((neighbors[a] != &m_pig_) && neighbors[a]->isTagged()) {
				kmint::math::vector2d ToAgent = m_pig_.location() - neighbors[a]->location();

				//scale the force inversely proportional to the agent's distance 
				//from its neighbor.
				SteeringForce += normalize(ToAgent) / (ToAgent.x(), ToAgent.y());
			}
		}

		return SteeringForce;
	}

	//kmint::math::vector2d SteeringBehaviors::separation(std::vector<pig *>& neighbors) {

	//}
	/*
	kmint::math::vector2d SteeringBehaviors::alignment(std::vector<pig *>& neighbors) {
		kmint::math::vector2d averageHeading;

		int NeighborCount = 0;

		for (int a = 0; a < neighbors.size(); ++a) {
			//make sure *this* agent isn't included in the calculations and that 
			//the agent being examined is close enough 
			if ((neighbors[a] != m_pig_) && neighbors[a]->isTagged()) {
				averageHeading += neighbors[a]->heading();
				++NeighborCount;
			}
		}

		//if the neighborhood contained one or more pigs, average their 
		//heading vectors.
		if (NeighborCount > 0)
		{
			averageHeading /= (double)NeighborCount;
			averageHeading -= m_pig_->heading();
		}

		return averageHeading;
	}*/
	
	void SteeringBehaviors::calculate() {

	}
}
}