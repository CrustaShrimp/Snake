#pragma once

#include "SnakeBehaviour.h"
#include "GridElement.h"
#include <set>

extern const int g_iGridSizePlusOne;

class Game
{
public:
	enum class DIRECTION
	{
		UNDEFINED = -1,
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	Game();
	~Game();
	void Play();
private:
	GridElement GenerateFood();

	int							m_iScore;
	std::set<GridElement>		m_sSnake;
	GridElement					m_Food;
	DIRECTION					m_eDirection;
};