#pragma once
#include "kmint/math/vector2d.hpp"
#include "kmint/play/stage.hpp"
#include "shark.hpp"
#include "boat.hpp"
#include "pig.hpp"

namespace kmint
{
	namespace pigisland
	{
		class GeneticalAlgorithm
		{
		public:
			GeneticalAlgorithm(play::stage & s) : stage_(&s) {}

			void createFirstGeneration(boat & boat, shark & shark);
			void createNewGeneration(boat & boat, shark & shark);
		private:
			play::stage * stage_;
			std::vector<pig *> pigs = std::vector<pig *>();
		};
	}
}
