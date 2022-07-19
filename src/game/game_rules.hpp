#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <map>

//#include <nlohmann/json.hpp>
#include <crow.h>

#include "structs/game_board.hpp"
#include "structs/spell.hpp"
#include "structs/item.hpp"

class game_rules {
protected:
	const std::string SPELLS_FILE_NAME = "spells.json";
	const std::string ITEMS_FILE_NAME = "items.json";
	std::map<int, spell_data> spells_map;
	std::map<int, item> item_map;

	std::vector<int> actor_sequence;
	int current_actor_sequence_index;

	game_board board;

	bool load_json(const std::string& filename, crow::json::rvalue& dest);
	void generate_spells_from_json();
	void generate_items_from_json();

	void extend_chunk(std::pair<int, int> source);
	void generate_game_board();
	void load_game_board(const std::string& filename);
	void destroy_game_board();

	bool cast_spell_on(int unit_id, int spell_id);

	void next_actors_turn() {
		current_actor_sequence_index++;
		current_actor_sequence_index = current_actor_sequence_index % actor_sequence.size();
	}

public:
	game_rules() {
		generate_spells_from_json();
		generate_items_from_json();
	}
};
