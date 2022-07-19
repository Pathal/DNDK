#pragma once

#include <string>
#include <stdexcept>

#include "../resources.hpp"

struct unit {
	std::string name;
	int resource[resource_types::NUM_RESOURCE_TYPES];
	int stats[stat_types::NUM_STAT_TYPES];
	double resistances[damage_type::NUM_DAMAGE_TYPES];
	ai_type ai_mode;
	std::pair<int, int> location;

	double get_resistance(damage_type t) {
		if(t == damage_type::PURE) return 0.0;
		if(t == damage_type::RANDOM) {t = static_cast<damage_type>(arc4random() % damage_type::NUM_DAMAGE_TYPES);}
		if(damage_type::NUM_DAMAGE_TYPES <= t) throw std::runtime_error("Invalid damage_type given.");

		return resistances[t];
	}
};
