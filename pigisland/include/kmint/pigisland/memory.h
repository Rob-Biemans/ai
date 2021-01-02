#pragma once
#include <vector>
#include "kmint/pigisland/chromosomes.hpp"

namespace kmint
{
	namespace pigisland
	{
		struct RepairHistory {
			int id;
			int repaired_for;
		};

		class Memory {
		public:
			int getRound();
			void increaseRound();
			int getSaved();
			void increaseSaved();
			void resetSaved();

			int getMaintenancePlaceChance(int dockNumber);
			void setMaintenancePlaceChance(int chance);
			void updateMaintenancePlaceChance(int dockNumber, int chance);

			void savePigChromosomes(Chromosomes chromosomes);
			std::vector<Chromosomes> getSavedPigChromosomes();

			void saveBoatRepairHistory(RepairHistory chromosomes);
			std::vector<RepairHistory> getAllBoatRepairHistory();
		private:
			int round_ = 0;
			std::vector<int> maintenances_places_chance_{};
			std::vector<Chromosomes> pig_chromosomes_{};
			std::vector<RepairHistory> boat_repair_history_{};
			int saved_ = 0;
		};
	}
}