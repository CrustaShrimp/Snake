#include "MainGame.h"
#include "Snake.h"
#include <cstdlib>
#include <cassert>
#include <numeric>

Game::Game()
	:m_iScore(0)
	,m_eDirection(DIRECTION::UNDEFINED)
	,m_bInitialized(false)
	,m_bGameRunning(false)
	,m_bGameOver(false)
	,m_bNewDirectionSet(false)
{

}

Game::~Game()
{

}

void Game::Play()
{
	assert(m_bInitialized);
	if (!m_bInitialized)
	{
		return;
	}
	if (!m_bGameRunning)
	{
		return;
	}
	// *************************************************
	// Play game:
	// 1: read direction (done in SetDirection())
	m_bNewDirectionSet = false;
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
		NewSnakeHead.AddY(-1);
		break;
	}
	case DIRECTION::DOWN:
	{
		NewSnakeHead.AddY(1);
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
		m_bGameRunning = false;
		m_bGameOver = true;
		return;
	}

	// Add new snakehead to the start of the vector
	m_vSnake.insert(m_vSnake.begin(), NewSnakeHead);

	// 4: check whether food is eaten
	if (NewSnakeHead == m_Food)
	{
		// Food eaten
		// 6: if eaten, increase score
		m_Food.SetActive(false);
		m_iScore+= 5;
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

void Game::SetDirection(const DIRECTION eDirection)
{
	m_bGameRunning = true;
	// Only set new direction if the direction has not already been changed without the game being called
	if (!m_bNewDirectionSet)
	{
		m_bNewDirectionSet = true;
		assert(eDirection != DIRECTION::UNDEFINED);
		switch (eDirection)
		{
		case DIRECTION::LEFT: // Fall through
		case DIRECTION::RIGHT:
			if (m_eDirection == DIRECTION::UNDEFINED || m_eDirection == DIRECTION::UP || m_eDirection == DIRECTION::DOWN)
			{
				m_eDirection = eDirection;
			}
			break;
		case DIRECTION::UP: // Fall through
		case DIRECTION::DOWN:
			if (m_eDirection == DIRECTION::UNDEFINED || m_eDirection == DIRECTION::LEFT || m_eDirection == DIRECTION::RIGHT)
			{
				m_eDirection = eDirection;
			}
			break;
		default:
			assert(false);
			break;
		}
	}
}

void Game::InitialiseGame()
{
	// *************************************************
	// Init:
	// 1: init snake at some point
	m_vSnake.clear();
	const int iMiddle = (GRIDSIZE - 1) / 2;
	const GridElement SnakeBeginPoint(iMiddle, iMiddle);
	m_vSnake.push_back(SnakeBeginPoint);

	// 2: init food at random point, not snake point!
	m_Food = GenerateFood();
	// 3: (re)init score, game over and gamerunning
	m_iScore = 0;
	m_bGameRunning = false;
	m_bGameOver = false;
	// 4: set initialized to true to let the rest know we are ready

	m_bInitialized = true;
}

GridElement Game::GenerateFood() const
{
	// Generate a food item somewhere
	// It cannot be in the snake set!
	// TODO set random seed
	bool bFoodLocationVerified = false;
	int iTries = 0;
	while (!bFoodLocationVerified && iTries < 50)
	{
		const int iFoodX = std::rand() % GRIDSIZE;
		const int iFoodY = std::rand() % GRIDSIZE;
		GridElement NewFood(iFoodX, iFoodY);
		// Check validity of the NewFood location, it cannot be inside the snake
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

bool Game::TestElementInSnake(const GridElement& ToTest) const
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
