#pragma once

const double EPSILON = 0.000001;
const int CHUNK_LENGTH = 10;

enum stat_types {
	STR,
	AGI,
	INT,
	WIS,
	CON,
	NUM_STAT_TYPES
};

enum resource_types {
	HEALTH,
	PRIMARY,
	SECONDARY,
	NUM_RESOURCE_TYPES
};

enum damage_type {
	PHYSICAL,
	ACID,
	BLUNT,
	ICE,
	FIRE,
	STORM,
	NECRO,
	PIERCE,
	POISON,
	PSYCHIC,
	SLASH,
	NUM_DAMAGE_TYPES,
	PURE,	// always 100% damage
	RANDOM  // picks any of the 11 types of damage
};

enum item_type {
	DOOR,
	KEY,
	SCROLL,
	NUM_ITEM_TYPES
};

enum class ai_type {
	PLAYER,
	GENERIC,
	DEFENSIVE,
	AGGRESSIVE,
	RANDOM
};

struct resource_amount {
public:
	resource_types type;
	int amount;

	resource_amount() { type = resource_types::PRIMARY; amount = 0; }
	resource_amount(int i) { type = resource_types::PRIMARY; amount = i; }
	resource_amount(int i, resource_types t) { type = t; amount = i; }
};
