#pragma once

#include <string>

#include <crow/json.h>

#include "../resources.hpp"

struct spell_data {
public:
	std::string name;
	double scaling[NUM_STAT_TYPES];
	int base_damage;
	resource_amount cost;
	double range;

	int calculate_damage(float stats[]) {
		int sum = base_damage;
		for (int i = 0; i < NUM_STAT_TYPES; i++) {
			sum += scaling[i] * stats[i];
		}
		return sum;
	}

	void build_resource_cost(const crow::json::rvalue& data) {
		cost.type = data.has("type") ? static_cast<resource_types>(data["type"].i()) : resource_types::PRIMARY;
		cost.amount = data.has("amount") ? data["amount"].i() : 0;
	}

	spell_data(const crow::json::rvalue& data) {
		try {
			name = data["name"].s();
			base_damage = data.has("base_damage") ? data["base_damage"].i() : 0;
			range = data.has("range") ? data["range"].d() : 1;

			if( data.has("cost") ) build_resource_cost(data["cost"]);
			if( data.has("scaling") ) {
				for (int i = 0; i < data["scaling"].size(); i++) {
					scaling[i] = data["scaling"][i].d();
				}
			}
		} catch (const std::exception& e) {
			std::cout << "Error loading spell data for " + std::string(data["name"].s()) + "\n";
			name = "CORRUPTED";
		}
	}

	spell_data() = delete;
};
