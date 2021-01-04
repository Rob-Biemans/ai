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

		int totalSavedPigs = boat.getMemory()->getSavedPigChromosomes().size();

		if (totalSavedPigs == 0) {
			createFirstGeneration(boat, shark);
			return;
		}

		if (totalSavedPigs % 2 == 0) {
			boat.getMemory()->getSavedPigChromosomes().pop_back();
			totalSavedPigs--;
		}

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

		// required for parent pair and determine average Chromosomes
		averageFitness = averageFitness / overallFitnessOfEachPig.size();

		std::vector<Chromosomes> belowAverageSelection{};
		std::vector<Chromosomes> parentSelection{};
		std::vector<Chromosomes> finalSelection{};

		float chance = 0;

		// Truncation Selection
		for (size_t i = 0; i < overallFitnessOfEachPig.size(); i++)
		{
			float fitness = overallFitnessOfEachPig.at(i);
			if (fitness >= averageFitness) {
				parentSelection.push_back(boat.getMemory()->getSavedPigChromosomes().at(i));
			}
			/*
			else {
				// (sum of fitness / fitness) / random_int(5, 10) weight of 0.5 <> 0.1
				chance += (fitness / 1) / random_int(5, 10);
				
				float random = random_scalar(0, 1);
				if (random < chance) {
					chance = 0;
					parentSelection.push_back(boat.getMemory()->getSavedPigChromosomes().at(i));
				}

				belowAverageSelection.push_back(boat.getMemory()->getSavedPigChromosomes().at(i));
			}
			*/
		}

		int parentSelectionSize = parentSelection.size();
		if (parentSelectionSize % 2 == 0 && parentSelectionSize != 0) {
			parentSelection.push_back(Chromosomes{});
		}

		// Crossover
		std::vector<Chromosomes> children{};
		for (size_t c = 0; c < 100; c++)
		{
			int split = random_int(1, 5);
			Chromosomes child{};

			for (size_t i = 0; i < split; i++) {
				child.getValues().at(i) = parentSelection.at(random_int(0, parentSelection.size())).getValues().at(i);
			}

			// Split point
			for (size_t sp = split; sp < 5; sp++) {
				child.getValues().at(sp) = parentSelection.at(random_int(0, parentSelection.size())).getValues().at(sp);
			}

			children.push_back(child);
		}


		// Mutation
		int randomChildIndex = random_int(1, children.size());
		int randomChromosome = random_int(3, 4);

		// 1 out of 100
		if (random_scalar(0.0f, 1.0f) == 0.01f) {
			children.at(randomChildIndex).getValues().at(randomChromosome) = random_scalar(0.0f, 1.0f);
		}

		// Uitdunnen (children by parents only)
		for (Chromosomes child : children) {
			finalSelection.push_back(child);
		}

		for (auto i = stage_->begin(); i != stage_->end(); ++i) {
			auto &a = *i;

			if (dynamic_cast<pig *>(&a))
			{
				pig* p = static_cast<pig*>(&a);
				p->remove();
			}
		}

		int amountOfFinalSelection = finalSelection.size();
		auto locs = pigisland::random_pig_locations(amountOfFinalSelection);
		int buildActorIndex = 0;
		for (auto loc : locs) {
			stage_->build_actor<pigisland::pig>(loc, finalSelection.at(buildActorIndex), shark, boat);
			buildActorIndex++;
		}

		// Clear
		boat.getMemory()->getSavedPigChromosomes().clear();
	}

}
}