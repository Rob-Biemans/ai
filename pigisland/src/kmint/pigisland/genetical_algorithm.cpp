#include "kmint/pigisland/genetical_algorithm.h"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/pig.hpp"

namespace kmint {
namespace pigisland {

	void GeneticalAlgorithm::createFirstGeneration(boat & boat, shark & shark) {

		  auto locs = pigisland::random_pig_locations(100);
		  for (auto loc : locs) {
			  stage_->build_actor<pigisland::pig>(loc, Chromosomes{}, shark, boat);
		  }
	}

	void GeneticalAlgorithm::createNewGeneration(boat & boat, shark & shark) {

		int totalLeftoverPigs = boat.getMemory()->getSavedPigChromosomes().size();

		if (totalLeftoverPigs == 0) {
			createFirstGeneration(boat, shark);
			return;
		}

		// week4 sheet 14
		// The higher the overall fitness of a pig, the higher chance to be picked as parent
		std::vector<float> overallFitnessOfEachPig;
		float averageFitness = 0;

		for (Chromosomes x : boat.getMemory()->getSavedPigChromosomes())
		{
			// https://en.wikipedia.org/wiki/Fitness_proportionate_selection
			float score = x.calculateFitness();
			overallFitnessOfEachPig.push_back(score);
			averageFitness += score;
		}

		// required for parent pairs and determine worst Chromosomes
		averageFitness = averageFitness / overallFitnessOfEachPig.size();

		// Crossover

		// Mutation

		// Uitdunnen

	}

}
}