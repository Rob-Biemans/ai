#include <array>
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {

class Attributes {
public:
  Attributes()
  {
	  // Attraction shark
	  attributesArray[0] = random_scalar(-1.0f, 1.0f);
	  // Attraction boat
	  attributesArray[1] = random_scalar(-1.0f, 1.0f);
	  // Cohesion
	  attributesArray[2] = random_scalar(0.0f, 1.0f);
	  // Separation
	  attributesArray[3] = random_scalar(0.0f, 1.0f);
	  // Alignment
	  attributesArray[4] = random_scalar(0.0f, 1.0f);
  }

  std::array<float, 5>& getValues() { return attributesArray; }

 private:
  std::array<float, 5> attributesArray{};
};

}
}
