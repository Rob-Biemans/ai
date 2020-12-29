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
	}

}
}