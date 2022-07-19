#pragma once

#include <memory>
#include <vector>
#include <set>

#include "board_tile.hpp"
#include "item.hpp"
#include "../resources.hpp"

struct tile_surface {
public:
	damage_type type;
	int amount;

	tile_surface(damage_type t, int a) {
		type = t;
		amount = a;
	}
};

struct board_tile {
public:
	int occupier_id;
	bool traversable;
	std::unique_ptr<tile_surface> surface_type;
	std::vector<std::unique_ptr<item>> items;

	board_tile() {
		traversable = false;
		occupier_id = -1;
		surface_type = nullptr;
	}

	board_tile(const board_tile& other) {
		traversable = other.traversable;
		occupier_id = other.occupier_id;
		if(other.surface_type) {
			surface_type = std::make_unique<tile_surface>(other.surface_type->type, other.surface_type->amount);
		}
	}
};

struct chunk {
public:
	std::pair<int, int> section_id;
	board_tile section[CHUNK_LENGTH][CHUNK_LENGTH];

	chunk(int r, int c) {
		section_id = std::pair{r,c};
	}
	chunk(std::pair<int, int>& p) {
		section_id = p;
	}
	chunk() = delete;
};

struct game_board {
public:
	std::pair<int, int> default_spawn_location{0,0};
	std::map<std::pair<int, int>, chunk> chunk_map;
	std::pair<int, int> view_corner{0,0};
	std::pair<int, int> view_size{10,10};

	game_board() {
		chunk_map.insert({default_spawn_location, chunk(default_spawn_location)});
	}

	~game_board() {
		//
	}

	board_tile& get_tile_from_coord(const std::pair<int, int>& loc) {
		std::pair<int, int> chunk_id = {loc.first / CHUNK_LENGTH, loc.second / CHUNK_LENGTH};
		auto& containing_chunk = chunk_map.at(chunk_id);
		return containing_chunk.section[loc.first % CHUNK_LENGTH][loc.second % CHUNK_LENGTH];
	}

	void load_view( std::vector<std::vector<board_tile>>& view ) {
		view.clear();
		for(int i=0; i < view_size.first; i++) {
			view.push_back(std::vector<board_tile>());
			for(int j=0; j < view_size.second; j++) {
				view.at(i).push_back( get_tile_from_coord({view_corner.first+i, view_corner.second+j}) );
			}
		}
	}
};
