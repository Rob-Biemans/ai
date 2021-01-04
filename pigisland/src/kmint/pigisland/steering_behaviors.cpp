#include "kmint/pigisland/steering_behaviors.h"
#include "kmint/pigisland/C2DMatrix.h"

namespace kmint {
namespace pigisland {

	SteeringBehaviors::SteeringBehaviors() {
		calcWalls();
	}

	float SteeringBehaviors::randomFloat(float min, float max) {
		return random_scalar(min, max);
	}

	kmint::math::vector2d SteeringBehaviors::wander(pig& m_pig_) {

		float r = random_scalar(0, RAND_MAX);
		//first, add a small random vector to the target’s position (RandomClamped
		//returns a value between -1 and 1)
		wanderTarget += kmint::math::vector2d(r * wanderJitter, r * wanderJitter);

		//reproject this new vector back on to a unit circle
		wanderTarget = normalize(wanderTarget);

		//increase the length of the vector to the same as the radius
		//of the wander circle
		wanderTarget *= wanderRadius;

		//move the target into a position WanderDist in front of the agent
		kmint::math::vector2d target = wanderTarget + kmint::math::vector2d(wanderDistance, 0);

		//project the target into world space
		kmint::math::vector2d Target = pointToWorldSpace(target, m_pig_.heading(), m_pig_.side(), m_pig_.location());

		//and steer towards it
		return Target - m_pig_.location();
	}

	kmint::math::vector2d SteeringBehaviors::pointToWorldSpace(const kmint::math::vector2d& point,
		const kmint::math::vector2d& heading,
		const kmint::math::vector2d& side,
		const kmint::math::vector2d& position) {

		//make a copy of the point
		kmint::math::vector2d TransPoint = point;

		//create a transformation matrix
		C2DMatrix matTransform;

		//rotate
		matTransform.Rotate(heading, side);

		//and translate
		matTransform.Translate(position.x(), position.y());

		//now transform the vertices
		matTransform.TransformVector2Ds(TransPoint);

		return TransPoint;
	}

	kmint::math::vector2d SteeringBehaviors::seek(kmint::math::vector2d target, pig& m_pig_) {
		kmint::math::vector2d desiredVelocity = normalize(target - m_pig_.location()) * m_pig_.maxSpeed();

		return (desiredVelocity - m_pig_.velocity());
	}
	
	
	kmint::math::vector2d SteeringBehaviors::normalize(kmint::math::vector2d target)
	{
		float vector_length = calcVectorLength(target);

		if (vector_length > std::numeric_limits<double>::epsilon())
		{
			target.x(target.x() / vector_length);
			target.y(target.y() / vector_length);
		}
		return target;
	}

	kmint::math::vector2d SteeringBehaviors::perp(kmint::math::vector2d target) {
		return kmint::math::vector2d(-target.y(), target.x());
	}

	float SteeringBehaviors::calcVectorLength(kmint::math::vector2d target) {
		return std::sqrt(std::pow(target.x(), 2) + std::pow(target.y(), 2));
	}

	kmint::math::vector2d SteeringBehaviors::flee(kmint::math::vector2d target, pig& m_pig_) {

		//only flee if the target is within 'panic distance'
		const double panicDistanceSq = 100.0 * 100.0;
		if (vec2DDistanceSq(m_pig_.location(), target) > panicDistanceSq) {
			return kmint::math::vector2d(0, 0);
		}

		kmint::math::vector2d desiredVelocity = normalize(m_pig_.location() - target) * m_pig_.maxSpeed();
		return (desiredVelocity - m_pig_.velocity());
	}
	
	kmint::math::vector2d SteeringBehaviors::cohesion(std::vector<pig *>& neighbors, pig& m_pig_) {
		kmint::math::vector2d SteeringForce;

		for (int a = 0; a < neighbors.size(); ++a) {
			auto &other = *neighbors[a];
			//make sure this agent isn't included in the calculations and that
			//the agent being examined is close enough. 
			if ((dynamic_cast<pig *>(&other)) && other.isTagged()) {
				kmint::math::vector2d ToAgent = m_pig_.location() - other.location();
			
				//scale the force inversely proportional to the agent's distance 
				//from its neighbor.
				SteeringForce += normalize(ToAgent) / (ToAgent.x(), ToAgent.y());
			}
		}

		return SteeringForce;
	}

	kmint::math::vector2d SteeringBehaviors::separation(std::vector<pig *>& neighbors, pig& m_pig_) {
		kmint::math::vector2d SteeringForce;

		for (int a = 0; a < neighbors.size(); ++a) {
			auto &other = *neighbors[a];
			//make sure this agent isn't included in the calculations and that 
			//the agent being examined is close enough.
			if ((dynamic_cast<pig *>(&other)) && other.isTagged())
			{
				kmint::math::vector2d ToAgent = m_pig_.location() - other.location();
			
				//scale the force inversely proportional to the agent's distance from its neighbor
				SteeringForce += normalize(ToAgent) / (ToAgent.x(), ToAgent.y());
			}
		}

		return SteeringForce;
	}
	
	kmint::math::vector2d SteeringBehaviors::alignment(std::vector<pig *> &neighbors, pig& m_pig_) {
		kmint::math::vector2d averageHeading;

		int NeighborCount = 0;

		for (int a = 0; a < neighbors.size(); ++a) {
			auto &other = *neighbors[a];
			//make sure *this* agent isn't included in the calculations and that 
			//the agent being examined is close enough 
			if ((dynamic_cast<pig *>(&other)) && other.isTagged()) {
				averageHeading += other.heading();
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
	
	kmint::math::vector2d SteeringBehaviors::calculate(pig& m_pig_, kmint::math::vector2d boatLocation, kmint::math::vector2d sharkLocation) {
		kmint::math::vector2d force;
		kmint::math::vector2d steeringForce;
		std::vector<pig *> neighbors;

		for (auto i = m_pig_.begin_perceived(); i != m_pig_.end_perceived(); ++i) {
			auto &a = *i;

			if (dynamic_cast<pig *>(&a))
			{
				pig* p = static_cast<pig*>(&a);
				neighbors.push_back(p);
			}
		}

		steeringForce += wander(m_pig_) * 8;

		force = separation(neighbors, m_pig_) * 0.65 *m_pig_.getChromosomes().getValues()[3];
		accumulateForce(m_pig_, steeringForce, force);
		force = alignment(neighbors, m_pig_) * 0.5 * m_pig_.getChromosomes().getValues()[4];
		accumulateForce(m_pig_, steeringForce, force);
		force = cohesion(neighbors, m_pig_) * 0.4 * m_pig_.getChromosomes().getValues()[2];
		accumulateForce(m_pig_, steeringForce, force);

		force = wallAvoidance(m_pig_) * 1000;
		accumulateForce(m_pig_, steeringForce, force);
		force = seek(boatLocation, m_pig_) * 0.15 * m_pig_.getChromosomes().getValues()[1];
		accumulateForce(m_pig_, steeringForce, force);
		force = flee(sharkLocation, m_pig_) * 0.9 * m_pig_.getChromosomes().getValues()[0];
		accumulateForce(m_pig_, steeringForce, force);

		return steeringForce;
	}

	void SteeringBehaviors::enforceNonPenetrationConstraint(pig& m_pig_)
	{
		std::vector<pig *> neighbors;
		for (auto i = m_pig_.begin_perceived(); i != m_pig_.end_perceived(); ++i) {
			auto &a = *i;

			if (dynamic_cast<pig *>(&a))
			{
				pig* p = static_cast<pig*>(&a);
				neighbors.push_back(p);
			}
		}

		//iterate through all entities checking for any overlap of bounding radii
		for (auto i = neighbors.begin(); i != neighbors.end(); ++i)
		{
			auto &a = *i;

			//make sure we don't check against the individual
			if (&m_pig_ == *i) continue;

			//calculate the distance between the positions of the entities
			kmint::math::vector2d ToEntity = m_pig_.location() - (a)->location();

			float ToEntityLength = sqrt(ToEntity.x() * ToEntity.x() + ToEntity.y() * ToEntity.y());
			double DistFromEachOther = ToEntityLength;

			//if this distance is smaller than the sum of their radii then this
			//entity must be moved away in the direction parallel to the
			//ToEntity vector   
			double AmountOfOverLap = 8 + 8 - DistFromEachOther;

			if (AmountOfOverLap >= 0)
			{
				//move the entity a distance away equivalent to the amount of overlap.
				m_pig_.move(m_pig_.location() + (ToEntity / DistFromEachOther) * AmountOfOverLap);
			}
		}//next entity
	}

	bool SteeringBehaviors::accumulateForce(pig& m_pig_, kmint::math::vector2d &RunningTot,
		kmint::math::vector2d ForceToAdd)
	{

		//calculate how much steering force the vehicle has used so far
		float RunningTotLength = sqrt(RunningTot.x() * RunningTot.x() + RunningTot.y() * RunningTot.y());
		double MagnitudeSoFar = RunningTotLength;

		//calculate how much steering force remains to be used by this vehicle
		double MagnitudeRemaining = m_pig_.maxForce() - MagnitudeSoFar;

		//return false if there is no more force left to use
		if (MagnitudeRemaining <= 0.0) return false;

		//calculate the magnitude of the force we want to add
		float ForceToAddLength = sqrt(ForceToAdd.x() * ForceToAdd.x() + ForceToAdd.y() * ForceToAdd.y());
		double MagnitudeToAdd = ForceToAddLength;

		//if the magnitude of the sum of ForceToAdd and the running total
		//does not exceed the maximum force available to this vehicle, just
		//add together. Otherwise add as much of the ForceToAdd vector is
		//possible without going over the max.
		if (MagnitudeToAdd < MagnitudeRemaining)
		{
			RunningTot += ForceToAdd;
		}

		else
		{
			//add it to the steering force
			RunningTot += (normalize(ForceToAdd) * MagnitudeRemaining);
		}

		return true;
	}

	void SteeringBehaviors::calcWalls() {
		// 1024, 768
		std::vector<Wall2D> walls;
		math::vector2d A = math::vector2d(0, 0);
		math::vector2d B = math::vector2d(0, 0);

		// Edges of screen
		A = math::vector2d(768, 768);
		B = math::vector2d(256, 768);
		Wall2D north = Wall2D(A, B);
		walls.push_back(north);

		A = math::vector2d(1024, 220);
		B = math::vector2d(1024, 548);
		Wall2D east = Wall2D(A, B);
		walls.push_back(east);

		A = math::vector2d(256, 0);
		B = math::vector2d(768, 0);
		Wall2D south = Wall2D(A, B);
		walls.push_back(south);

		A = math::vector2d(0, 548);
		B = math::vector2d(0, 220);
		Wall2D west = Wall2D(A, B);
		walls.push_back(west);

		// Islands
		// NW
		A = math::vector2d(255, 549);
		B = math::vector2d(0, 514);
		Wall2D nwS = Wall2D(A, B);
		walls.push_back(nwS);

		A = math::vector2d(255, 768);
		B = math::vector2d(255, 549);
		Wall2D nwE = Wall2D(A, B);
		walls.push_back(nwE);

		// NE
		A = math::vector2d(1024, 549);
		B = math::vector2d(769, 549);
		Wall2D neS = Wall2D(A, B);
		walls.push_back(neS);

		A = math::vector2d(769, 549);
		B = math::vector2d(769, 768);
		Wall2D neW = Wall2D(A, B);
		walls.push_back(neW);

		// SE
		A = math::vector2d(769, 219);
		B = math::vector2d(1024, 219);
		Wall2D seN = Wall2D(A, B);
		walls.push_back(seN);

		A = math::vector2d(769, 0);
		B = math::vector2d(769, 219);
		Wall2D seW = Wall2D(A, B);
		walls.push_back(seW);

		// SW
		A = math::vector2d(0, 219);
		B = math::vector2d(305, 219);
		Wall2D swN = Wall2D(A, B);
		walls.push_back(swN);

		A = math::vector2d(305, 219);
		B = math::vector2d(305, 0);
		Wall2D swE = Wall2D(A, B);
		walls.push_back(swE);

		walls_ = walls;
	}

	kmint::math::vector2d SteeringBehaviors::wallAvoidance(pig& m_pig_) {
		createFeelers(m_pig_);

		double DistToThisIP = 0.0;
		double DistToClosestIP = DBL_MAX;

		int ClosestWall = -1;

		kmint::math::vector2d steeringForce, 
			point, //used for storing temporary info 
			ClosestPoint;  //holds the closest intersection poin

		for (int flr = 0; flr < m_Feelers.size(); ++flr) {
			//run through each wall checking for any intersection points
			for (int w = 0; w < walls_.size(); ++w) {
				if (lineIntersection2D(m_pig_.location(), m_Feelers[flr], walls_[w].From(), walls_[w].To(), DistToThisIP, point))
				{
					//is this the closest found so far? If so keep a record 
					if (DistToThisIP < DistToClosestIP) 
					{
						DistToClosestIP = DistToThisIP;
						ClosestWall = w;
						ClosestPoint = point;
					}
				}
			}

			//if an intersection point has been detected, calculate a force that will direct the pig away
			if (ClosestWall >= 0)
			{
				//calculate by what distance the projected position of the pig will overshoot the wall
				kmint::math::vector2d overShoot = m_Feelers[flr] - ClosestPoint;

				//create a force in the direction of the wall normal, with a magnitude of the overshoot 
				float length = sqrt(overShoot.x() * overShoot.x() + overShoot.y() * overShoot.y());
				steeringForce = walls_[ClosestWall].Normal() * length;
			}
		}

		return steeringForce;
	}

	bool SteeringBehaviors::lineIntersection2D(kmint::math::vector2d A,
		kmint::math::vector2d B,
		kmint::math::vector2d C,
		kmint::math::vector2d D,
		double& dist,
		kmint::math::vector2d& point)
	{

		double rTop = (A.y() - C.y())*(D.x() - C.x()) - (A.x() - C.x())*(D.y() - C.y());
		double rBot = (B.x() - A.x())*(D.y() - C.y()) - (B.y() - A.y())*(D.x() - C.x());

		double sTop = (A.y() - C.y())*(B.x() - A.x()) - (A.x() - C.x())*(B.y() - A.y());
		double sBot = (B.x() - A.x())*(D.y() - C.y()) - (B.y() - A.y())*(D.x() - C.x());

		if ((rBot == 0) || (sBot == 0))
		{
			//lines are parallel
			return false;
		}

		double r = rTop / rBot;
		double s = sTop / sBot;

		if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
		{
			dist = vec2DDistance(A, B) * r;

			point = A + r * (B - A);

			return true;
		}

		else
		{
			dist = 0;

			return false;
		}
	}

	void SteeringBehaviors::createFeelers(pig& m_pig_)
	{
		const double HalfPi = 3.14159 / 2;
		float wallDetectionLength = 100;
		//feeler pointing straight in front
		m_Feelers[0] = m_pig_.location() + wallDetectionLength * m_pig_.heading();

		//feeler to left
		math::vector2d temp = m_pig_.heading();
		vec2DRotateAroundOrigin(temp, HalfPi * 3.5f);
		m_Feelers[1] = m_pig_.location() + wallDetectionLength / 2.0f * temp;

		//feeler to right
		temp = m_pig_.heading();
		vec2DRotateAroundOrigin(temp, HalfPi * 0.5f);
		m_Feelers[2] = m_pig_.location() + wallDetectionLength / 2.0f * temp;
	}

	void SteeringBehaviors::vec2DRotateAroundOrigin(kmint::math::vector2d& v, double ang)
	{
		//create a transformation matrix
		C2DMatrix mat;

		//rotate
		mat.Rotate(ang);

		//now transform the object's vertices
		mat.TransformVector2Ds(v);
	}

	double SteeringBehaviors::vec2DDistance(const kmint::math::vector2d &v1, const kmint::math::vector2d &v2)
	{

		double ySeparation = v2.y() - v1.y();
		double xSeparation = v2.x() - v1.x();

		return sqrt(ySeparation*ySeparation + xSeparation * xSeparation);
	}

	double SteeringBehaviors::vec2DDistanceSq(const kmint::math::vector2d &v1, const kmint::math::vector2d &v2)
	{

		double ySeparation = v2.y() - v1.y();
		double xSeparation = v2.x() - v1.x();

		return ySeparation * ySeparation + xSeparation * xSeparation;
	}

	kmint::math::vector2d SteeringBehaviors::truncate(kmint::math::vector2d target, double max)
	{
		if (this->calcVectorLength(target) > max)
		{
			kmint::math::vector2d value = this->normalize(target);

			return value *= max;
		}

		return target;
	}
}
}