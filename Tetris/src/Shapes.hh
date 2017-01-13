#pragma once
#include <vector>

static std::vector<std::vector<unsigned>> OBlock = {
	{ {1, 1}
	, {1, 1} }
};

static std::vector<std::vector<unsigned>> IBlock = {
	{ {1, 1, 1, 1} }
};

static std::vector<std::vector<unsigned>> JBlock = {
	{ {1, 1, 1}
	, {0, 0, 1}}
};

static std::vector<std::vector<unsigned>> LBlock = {
	{ { 1, 1, 1 }
	, { 1, 0, 0 } }
};

static std::vector<std::vector<unsigned>> SBlock = {
	{ { 0, 1, 1 }
	, { 1, 1, 0}}
};

static std::vector<std::vector<unsigned>> TBlock = {
	{ { 1, 1, 1 }
	, { 0, 1, 0 } }
};

static std::vector<std::vector<unsigned>> ZBlock = {
	{ { 1, 1, 0 }
	, { 0, 1, 1 } }
};

static std::vector<std::vector<std::vector<unsigned>>*> shapeList
	{ &OBlock, &IBlock, &JBlock, &LBlock, &SBlock, &TBlock, &ZBlock };