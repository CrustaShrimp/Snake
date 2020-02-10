#pragma once

#include "SnakeBehaviour.h"
#include "GridElement.h"
#include <set>

extern const int g_iGridSizePlusOne;

class GridElement;
struct GridNumberComparison;

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

	void InitialiseGame();

private:
	//************************************
	// Method:    GenerateFood
	// FullName:  Game::GenerateFood
	// Access:    private 
	// Returns:   GridElement
	// Qualifier:
	//************************************
	GridElement GenerateFood();

	bool TestElementInSnake(const GridElement& ToTest);

	int												m_iScore;
	std::vector<GridElement>						m_vSnake;
	GridElement										m_Food;
	DIRECTION										m_eDirection;
};