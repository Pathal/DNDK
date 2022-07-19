#pragma once

#include <string>
#include <iostream>

#include <crow.h>

#include "../resources.hpp"

struct item {
public:
	std::string name;
	// defines the behavior tree of the item
	item_type type;
	// so items like a scroll can reference a spell_id
	std::optional<int> associated_item_id;

	item(const item& other) {
		name = other.name;
		type = other.type;
		associated_item_id = other.associated_item_id;
	}

	item(crow::json::rvalue& data) {
		try {
			name = data["name"].s();

			if (data.has("type")) {
				std::string typ = data["type"].s();
				if( typ == "door") type = item_type::DOOR;
				else if( typ == "key") type = item_type::KEY;
				else if( typ == "scroll") type = item_type::SCROLL;
			}

		} catch (const std::exception& e) {
			std::cout << "Error loading spell data for " + std::string(data["name"].s()) + "\n";
			name = "CORRUPTED";
		}
	}

	item() = delete;
};
