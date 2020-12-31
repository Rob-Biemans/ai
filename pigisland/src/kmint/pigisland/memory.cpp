#include "kmint/pigisland/memory.h"

namespace kmint
{
	namespace pigisland
	{
		int Memory::getRound() {
			return round_;
		}

		void Memory::increaseRound() {
			round_++;
			resetSaved();
		}

		int Memory::getSaved() {
			return saved_;
		}

		void Memory::increaseSaved() {
			saved_++;
		}

		void Memory::resetSaved() {
			saved_ = 0;
		}

		int Memory::getMaintenancePlaceChance(int dockNumber) {
			return maintenances_places_chance_[dockNumber];
		}

		void Memory::setMaintenancePlaceChance(int chance) {
			maintenances_places_chance_.push_back(chance);
		}

		void Memory::savePigChromosomes(Chromosomes chromosomes) {
			pig_chromosomes_.push_back(chromosomes);
			increaseSaved();
		}

		std::vector<Chromosomes> Memory::getSavedPigChromosomes() {
			return pig_chromosomes_;
		}
	}
}