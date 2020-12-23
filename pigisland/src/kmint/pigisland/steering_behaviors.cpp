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

		//only flee if the target is within 'panic distance'
		//const double panicDistanceSq = 100.0 * 100.0;
		//if (Vec2DDistanceSq(m_pig_.location(), target) > panicDistanceSq) {
		//	return kmint::math::vector2d(0, 0);
		//}

		kmint::math::vector2d desiredVelocity = normalize(m_pig_.location() - target) * m_pig_.maxSpeed();
		return (desiredVelocity - m_pig_.velocity());
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

	kmint::math::vector2d SteeringBehaviors::separation(std::vector<pig *>& neighbors) {
		kmint::math::vector2d SteeringForce;

		for (int a = 0; a < neighbors.size(); ++a) {

			//make sure this agent isn't included in the calculations and that 
			//the agent being examined is close enough.
			if ((neighbors[a] != &m_pig_) && neighbors[a]->isTagged()) 
			{
				kmint::math::vector2d ToAgent = m_pig_.location() - neighbors[a]->location();
			
				//scale the force inversely proportional to the agent's distance from its neighbor
				SteeringForce += normalize(ToAgent) / (ToAgent.x(), ToAgent.y());
			}
		}

		return SteeringForce;
	}
	
	kmint::math::vector2d SteeringBehaviors::alignment(std::vector<pig *>& neighbors) {
		kmint::math::vector2d averageHeading;

		int NeighborCount = 0;

		for (int a = 0; a < neighbors.size(); ++a) {
			//make sure *this* agent isn't included in the calculations and that 
			//the agent being examined is close enough 
			if ((neighbors[a] != &m_pig_) && neighbors[a]->isTagged()) {
				averageHeading += neighbors[a]->heading();
				++NeighborCount;
			}
		}

		//if the neighborhood contained one or more pigs, average their 
		//heading vectors.
		if (NeighborCount > 0)
		{
			averageHeading /= (double)NeighborCount;
			averageHeading -= m_pig_.heading();
		}

		return averageHeading;
	}
	
	void SteeringBehaviors::calculate() {
		kmint::math::vector2d SteeringForce;

		//SteeringForce += wander() * dWanderAmount;
		//SteeringForce += obstacleAvoidance() * dObstacleAvoidanceAmount;
		//SteeringForce += separation() * dSeparationAmount;

		//return SteeringForce.Truncate(MAX_STEERING_FORCE);
	}

	kmint::math::vector2d SteeringBehaviors::wallAvoidance(const std::vector<Wall2D>& walls) {
		CreateFeelers();

		double DistToThisIP = 0.0;
		//TODO
		double DistToClosestIP = 0;// MaxDouble;

		int ClosestWall = -1;

		kmint::math::vector2d steeringForce, 
			point, //used for storing temporary info 
			ClosestPoint;  //holds the closest intersection poin

		for (int flr = 0; flr < m_Feelers.size(); ++flr) {
			//run through each wall checking for any intersection points
			for (int w = 0; w < walls.size(); ++w) {
				//TODO
				//if (LineIntersection2D(m_pig_->Pos(), m_Feelers[flr], walls[w].From(), walls[w].To(), DistToThisIP, point))
				//{
				//	//is this the closest found so far? If so keep a record 
				//	if (DistToThisIP < DistToClosestIP) 
				//	{
				//		DistToClosestIP = DistToThisIP;
				//		ClosestWall = w;
				//		ClosestPoint = point;
				//	}
				//}
			}
		}

		//if an intersection point has been detected, calculate a force that will direct the pig away
		if (ClosestWall >= 0)
		{
			//calculate by what distance the projected position of the pig will overshoot the wall
			//TODO
			//kmint::math::vector2d overShoot = m_Feelers[flr] - ClosestPoint;

			//create a force in the direction of the wall normal, with a magnitude of the overshoot 
			//TODO
			//steeringForce = walls[ClosestWall].Normal() * overShoot.Length();
		}

		return steeringForce;
	}

	void SteeringBehaviors::CreateFeelers()
	{
		const double   HalfPi = 3.14159 / 2;
		//may be needed to tweak
		float wallDetectionLength = 100;
		//feeler pointing straight in front
		m_Feelers[0] = m_pig_.location() + wallDetectionLength * m_pig_.heading();

		//feeler to left
		math::vector2d temp = m_pig_.heading();
		//TODO
		//vec2D_rotate_around_origin(temp, HalfPi * 3.5f);
		m_Feelers[1] = m_pig_.location() + wallDetectionLength / 2.0f * temp;

		//feeler to right
		temp = m_pig_.heading();
		//TODO
		//vec2D_rotate_around_origin(temp, HalfPi * 0.5f);
		m_Feelers[2] = m_pig_.location() + wallDetectionLength / 2.0f * temp;
	}
}
}