#include "kmint/pigisland/genetical_algorithm.h"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/pig.hpp"

namespace kmint {
namespace pigisland {

	void GeneticalAlgorithm::createFirstGeneration(boat & boat, shark & shark) {

		  auto locs = pigisland::random_pig_locations(100);
		  for (auto loc : locs) {
			  stage_->build_actor<pigisland::pig>(loc, Attributes{}, shark, boat);
		  }
	}

	void GeneticalAlgorithm::createNewGeneration(boat & boat, shark & shark) {
		//TODO

		// get surviving pigs
		// use suriving pigs to collection and create new to reach 100

		// use boat and shark to create new both from previous experience
	}

}
}