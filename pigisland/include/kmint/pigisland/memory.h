#pragma once
#include <vector>
#include "kmint/pigisland/chromosomes.hpp"

namespace kmint
{
	namespace pigisland
	{
		class Memory {
		public:
			int getRound();
			void increaseRound();
			int getSaved();
			void increaseSaved();
			void resetSaved();

			int getMaintenancePlaceChance(int dockNumber);
			void setMaintenancePlaceChance(int chance);

			void savePigChromosomes(Chromosomes chromosomes);
			std::vector<Chromosomes> getSavedPigChromosomes();
		private:
			int round_ = 0;
			std::vector<int> maintenances_places_chance_{};
			std::vector<Chromosomes> pig_chromosomes_{};
			int saved_ = 0;
		};
	}
}