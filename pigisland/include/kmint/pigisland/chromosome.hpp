#pragma once
#include <array>
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {

class chromosome {
public:
  chromosome()
  {
	// Attraction shark
	chromosome_array_[0] = random_scalar(-1.0f, 1.0f);
	// Attraction boat
	chromosome_array_[1] = random_scalar(-1.0f, 1.0f);
	// Cohesion
	chromosome_array_[2] = random_scalar(0.0f, 1.0f);
	// Separation
	chromosome_array_[3] = random_scalar(0.0f, 1.0f);
	// Alignment
	chromosome_array_[4] = random_scalar(0.0f, 1.0f);
  }

  std::array<float, 5>& get() const { return chromosome_array_; }

 private:
  std::array<float, 5> chromosome_array_{};
};

}
}
