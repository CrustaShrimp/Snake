#include "MainGame.h"
#include <cstdlib>

const int g_iGridSizePlusOne = 51;

Game::Game()
	:m_iScore(0)
	,m_sSnake()
	,m_Food()
	,m_eDirection(DIRECTION::UNDEFINED)
{

}

Game::~Game()
{

}

void Game::Play()
{
	// *************************************************
	// Init:
	// 1: init snake at some point
	const int iMiddle = (g_iGridSizePlusOne - 1) / 2;
	m_sSnake.insert(GridElement(iMiddle, iMiddle));

	// 2: init food at random point, not snake point!

	// 3: init score = 0
	// 4: wait for direction to start...


	// *************************************************
	// Play game:
	// 1: read direction
	// 1: move snake in direction
	// 2: check gameover (snakehead touching snake)
	// 3: check whether food is eaten
	// 4: if eaten, enlarge snake (otherwise pop)
	// 5: if eaten, increase score
	// continues
}

GridElement GenerateFood()
{
	// Generate a food item somewhere
	// It cannot be in the snake set yet!
	bool bValidFood = false;
	while (!bValidFood)
	{
		const int iFoodX = std::rand() % g_iGridSizePlusOne;
		const int iFoodY = std::rand() % g_iGridSizePlusOne;
		GridElement NewFood(iFoodX, iFoodY);
	}
}