#include "game_rules.hpp"

bool game_rules::load_json(const std::string& filename, crow::json::rvalue& dest) {
	if (!std::filesystem::exists(filename)) return false;

	bool res = true;
	try {
		std::ifstream fin(filename);
		std::string loaded_json((std::istreambuf_iterator<char>(fin)),
								std::istreambuf_iterator<char>());

		dest = crow::json::load(loaded_json);
	} catch (const std::exception& e) {
		std::cout << "Exception occured while loading the " + filename + " file.";
		res = false;
	}

	return res;
}

void game_rules::generate_spells_from_json() {
	crow::json::rvalue spells_data;
	unsigned int spells_loaded = 0;
	if( load_json(SPELLS_FILE_NAME, spells_data) ) {
		for (auto& s : spells_data) {
			spells_map.insert({ spells_map.size(), spell_data(s) });
			spells_loaded++;
		}
	} else {
		std::cout << "Unable to load file " << SPELLS_FILE_NAME << "\n";
		return;
	}
	std::cout << "Loaded " << spells_loaded << " spells\n";
}

void game_rules::generate_items_from_json() {
	crow::json::rvalue items_data;
	unsigned int items_loaded = 0;
	if( load_json(ITEMS_FILE_NAME, items_data) ) {
		for (auto s : items_data) {
			item_map.insert({ item_map.size(), item(s) });
			items_loaded++;
		}
	} else {
		std::cout << "Unable to load file " << ITEMS_FILE_NAME << "\n";
		return;
	}
	std::cout << "Loaded " << items_loaded << " items\n";

}

void game_rules::extend_chunk(std::pair<int, int> source) {
	source.first++;
	if( !board.chunk_map.contains(source) ) board.chunk_map.insert({source, chunk(source)});
	source.first -= 2;
	if( !board.chunk_map.contains(source) ) board.chunk_map.insert({source, chunk(source)});
	source.first++;
	source.second++;
	if( !board.chunk_map.contains(source) ) board.chunk_map.insert({source, chunk(source)});
	source.second -= 2;
	if( !board.chunk_map.contains(source) ) board.chunk_map.insert({source, chunk(source)});
}

void game_rules::generate_game_board() {
	std::pair root{0,0};
	if( !board.chunk_map.contains(root) ) {
		board.chunk_map.insert({ root, chunk(root) });
	}
	extend_chunk(root);
}

bool game_rules::cast_spell_on(int unit_id, int spell_id) {
	if( !spells_map.contains(spell_id) ) return false;
	spell_data& spell = spells_map.at(spell_id);

	// do the range math

	return true;
}

void game_rules::load_game_board(const std::string& filename) {
	// UNIMPLEMENTED
}

void game_rules::destroy_game_board() {
	// UNIMPLEMENTED
}

