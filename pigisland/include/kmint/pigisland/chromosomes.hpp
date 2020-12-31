#ifndef PIGISLAND_CHROMOSOMES_HPP
#define PIGISLAND_CHROMOSOMES_HPP
#include <array>
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {

class Chromosomes {
public:
	Chromosomes()
  {
	  // Attraction shark
	  chromosomesArray[0] = random_scalar(-1.0f, 1.0f);
	  // Attraction boat
	  chromosomesArray[1] = random_scalar(-1.0f, 1.0f);
	  // Cohesion
	  chromosomesArray[2] = random_scalar(0.0f, 1.0f);
	  // Separation
	  chromosomesArray[3] = random_scalar(0.0f, 1.0f);
	  // Alignment
	  chromosomesArray[4] = random_scalar(0.0f, 1.0f);
  }

  std::array<float, 5>& getValues() { return chromosomesArray; }
  float calculateFitness() {
	  float fitness = 0;

	  // Add the three most important attributes in the fitness score mix
	  fitness += chromosomesArray[1];
	  fitness += chromosomesArray[2];
	  fitness += chromosomesArray[4];

	  fitness = fitness / 3;

	  return fitness;
  }

 private:
  std::array<float, 5> chromosomesArray{};
};

}
}

#endif  /* PIGISLAND_CHROMOSOMES_HPP */
