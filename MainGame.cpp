#include "MainGame.h"
#include <cstdlib>
#include <cassert>
#include <numeric>

const int g_iGridSizePlusOne = 51;

Game::Game()
	:m_iScore(0)
	,m_eDirection(DIRECTION::UNDEFINED)
{

}

Game::~Game()
{

}

void Game::Play()
{
	InitialiseGame();
	bool bGameOver = false;
	while (!bGameOver)
	{
		// *************************************************
		// Play game:
		// 1: read direction
		// TODO
		// Work with another enum, add to direction only if possible...

		// HACK
		m_eDirection = DIRECTION::RIGHT;

		// 2: move snake in direction
		GridElement NewSnakeHead = *(m_vSnake.cbegin());
		switch (m_eDirection)
		{
		case DIRECTION::RIGHT:
		{
			NewSnakeHead.AddX(1);
			break;
		}
		case DIRECTION::LEFT:
		{
			NewSnakeHead.AddX(-1);
			break;
		}
		case DIRECTION::UP:
		{
			NewSnakeHead.AddY(1);
			break;
		}
		case DIRECTION::DOWN:
		{
			NewSnakeHead.AddX(-1);
			break;
		}
		default:
			// Somehow error something
			assert(false && "Direction is not found!");
			break;
		};

		// 3: check gameover (snakehead touching snake)
		if (TestElementInSnake(NewSnakeHead))
		{
			// Game Over
			bGameOver = true;
			// TODO
			//GameOver();
		}
		
		// Add new snakehead to the start of the vector
		m_vSnake.insert(m_vSnake.begin(), NewSnakeHead);

		// 4: check whether food is eaten
		if (NewSnakeHead == m_Food)
		{
			// Food eaten
			// 6: if eaten, increase score
			m_Food.SetActive(false);
			m_iScore++;
		}
		else
		{
			// 5: if not eaten, pop
			m_vSnake.pop_back();
		}
		// 7: Set new food if food is eaten
		if (!m_Food.GetActive())
		{
			m_Food = GenerateFood();
		}
		// continues
	}
}

void Game::InitialiseGame()
{
	// *************************************************
	// Init:
	// 1: init snake at some point
	const int iMiddle = (g_iGridSizePlusOne - 1) / 2;
	const GridElement SnakeBeginPoint(iMiddle, iMiddle);
	m_vSnake.push_back(SnakeBeginPoint);

	// 2: init food at random point, not snake point!
	m_Food = GenerateFood();
	// 3: init score = 0
	// Already done by constructor!

	// 4: wait for direction to start...
	while (m_eDirection == DIRECTION::UNDEFINED)
	{
		// Get key
		// set direction according to arrow keys

		// HACK
		break;
	}
	return;
}

GridElement Game::GenerateFood()
{
	// Generate a food item somewhere
	// It cannot be in the snake set!
	// TODO set random seed
	bool bFoodLocationVerified = false;
	int iTries = 0;
	while (!bFoodLocationVerified && iTries < 50)
	{
		const int iFoodX = std::rand() % g_iGridSizePlusOne;
		const int iFoodY = std::rand() % g_iGridSizePlusOne;
		GridElement NewFood(iFoodX, iFoodY);
		// Check validity of the newfood location, it cannot be inside the snake
		bFoodLocationVerified = !TestElementInSnake(NewFood);
		if (bFoodLocationVerified)
		{
			NewFood.SetActive(true);
			return NewFood;
		}
		iTries++;
	}
	return GridElement(0,0);
}

bool Game::TestElementInSnake(const GridElement& ToTest)
{
	const bool bFound = std::accumulate(m_vSnake.cbegin(), m_vSnake.cend(), false, [&ToTest](bool bEqual, const GridElement SnakeElement)->bool
		{
			if (bEqual)
			{
				return bEqual;
			}
			bEqual = SnakeElement == ToTest;
			return bEqual;
		});
	return bFound;
}
